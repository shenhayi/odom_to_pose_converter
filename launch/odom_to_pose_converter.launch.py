#!/usr/bin/env python3

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    # Declare launch arguments
    input_topic_arg = DeclareLaunchArgument(
        'input_topic',
        default_value='Odometry',
        description='Input odometry topic name'
    )
    
    output_topic_arg = DeclareLaunchArgument(
        'output_topic',
        default_value='mavros/local_position/pose',
        description='Output path topic name'
    )
    
    buffer_size_arg = DeclareLaunchArgument(
        'buffer_size',
        default_value='100',
        description='Buffer size for path poses'
    )
    
    # Create the node
    odom_to_pose_node = Node(
        package='odom_to_pose_converter',
        executable='odom_to_pose_converter_node',
        name='odom_to_pose_converter',
        output='screen',
        parameters=[{
            'input_topic': LaunchConfiguration('input_topic'),
            'output_topic': LaunchConfiguration('output_topic'),
            'buffer_size': LaunchConfiguration('buffer_size'),
        }]
    )
    
    return LaunchDescription([
        input_topic_arg,
        output_topic_arg,
        buffer_size_arg,
        odom_to_pose_node,
    ])
