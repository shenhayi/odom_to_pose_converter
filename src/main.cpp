#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav_msgs/msg/path.hpp>

class OdomToPathNode : public rclcpp::Node
{
public:
    OdomToPathNode() :
        Node("odom_to_pose_node")
    {
        // Declare parameters with default values
        this->declare_parameter<int>("buffer_size", 100);
        this->declare_parameter<std::string>("input_topic", "odom_in");
        this->declare_parameter<std::string>("output_topic", "pose_out");
        
        // Get parameter values
        this->get_parameter("buffer_size", bufferSize);
        this->get_parameter("input_topic", inputTopic);
        this->get_parameter("output_topic", outputTopic);

        // Create subscription and publisher with configurable topics
        odomSubscription = this->create_subscription<nav_msgs::msg::Odometry>(inputTopic, 1000,
                                                                              std::bind(&OdomToPathNode::subscriptionCallback, this,
                                                                                        std::placeholders::_1));
        pathPublisher = this->create_publisher<nav_msgs::msg::Path>(outputTopic, 1000);
        
        RCLCPP_INFO(this->get_logger(), "OdomToPathNode started with input_topic: %s, output_topic: %s, buffer_size: %d", 
                    inputTopic.c_str(), outputTopic.c_str(), bufferSize);
    }

private:
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odomSubscription;
    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr pathPublisher;
    nav_msgs::msg::Path path;
    int bufferSize;
    std::string inputTopic;
    std::string outputTopic;

    void subscriptionCallback(const std::shared_ptr<const nav_msgs::msg::Odometry> odometryMsg)
    {
        geometry_msgs::msg::PoseStamped poseStamped;
        poseStamped.header.frame_id = odometryMsg->header.frame_id;
        poseStamped.header.stamp = odometryMsg->header.stamp;
        poseStamped.pose = odometryMsg->pose.pose;
        path.poses.push_back(poseStamped);
	path.header.frame_id = odometryMsg->header.frame_id;
	path.header.stamp = odometryMsg->header.stamp;
        if(path.poses.size() > bufferSize)
        {
            path.poses.erase(path.poses.begin());
        }
        pathPublisher->publish(path);
    }
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<OdomToPathNode>());
    rclcpp::shutdown();
    return 0;
}
