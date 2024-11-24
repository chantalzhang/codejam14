# Base image: ROS Noetic (for Ubuntu 20.04)
FROM ros:noetic-ros-core

# Set the default working directory
WORKDIR /catkin_ws

# Install necessary dependencies
RUN apt-get update && apt-get install -y \
    python3-pip \
    python3-catkin-tools \
    ros-noetic-rosserial-arduino \
    ros-noetic-rosserial \
    ros-noetic-rviz \
    ros-noetic-rosbridge-suite \
    python3-rosdep \
    build-essential \
    cmake \
    git \
    curl \
    && rm -rf /var/lib/apt/lists/*

# Copy your ROS workspace into the container
COPY ./catkin_ws /catkin_ws

# Set up ROS environment and dependencies
RUN /bin/bash -c "source /opt/ros/noetic/setup.bash && rosdep update && rosdep install --from-paths src --ignore-src -r -y && catkin_make"

# Expose ROS master port (default: 11311)
EXPOSE 11311

# Default command: launch ROS core
CMD ["roscore"]
