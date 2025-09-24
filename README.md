# Odom to Pose Converter

This ROS2 node converts odometry messages to path messages for visualizing robot motion trajectories.

## Features

- Subscribe to odometry topic
- Convert odometry messages to pose_stamped messages
- Maintain a fixed-size path buffer
- Publish path messages for visualization

## Parameters

- `input_topic` (string, default: "odom_in"): Input odometry topic name
- `output_topic` (string, default: "pose_out"): Output path topic name  
- `buffer_size` (int, default: 100): Path buffer size

## Usage

### 1. Launch with default parameters

```bash
ros2 launch odom_to_pose_converter odom_to_pose_converter.launch.py
```

### 2. Customize topic names

```bash
ros2 launch odom_to_pose_converter odom_to_pose_converter.launch.py \
    input_topic:=/robot/odom \
    output_topic:=/robot/path
```

### 3. Customize buffer size

```bash
ros2 launch odom_to_pose_converter odom_to_pose_converter.launch.py \
    buffer_size:=200
```

### 4. Run node directly

```bash
ros2 run odom_to_pose_converter odom_to_pose_converter_node \
    --ros-args -p input_topic:=/robot/odom -p output_topic:=/robot/path -p buffer_size:=200
```

## Topics

### Input
- `input_topic` (nav_msgs/msg/Odometry): Input odometry data

### Output  
- `output_topic` (nav_msgs/msg/Path): Output path data

## Dependencies

- rclcpp
- nav_msgs
- geometry_msgs
