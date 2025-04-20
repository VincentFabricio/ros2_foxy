from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    ld = LaunchDescription()
    
    param_config = os.path.join(get_package_share_directory("my_robot_bringup"),
                                "confing", "number_app.yaml")
    
    number_publisher_py = Node(
        package="my_py_pkg",
        executable="number_publisher_py",
        namespace="/abc",
        name="my_number_publisher", 
        remappings=[("/number", "/my_number")],
        # parameters=[
        #     {"number": 12},
        #     {"timer_period": 1.3}
        # ]
        parameters=[param_config]
    )
    
    number_counter_cpp = Node(
        package="my_cpp_pkg",
        executable="number_counter_cpp",
        namespace="/abc",
        name="my_number_counter",
    )
    
    ld.add_action(number_publisher_py)
    ld.add_action(number_counter_cpp)
    
    return ld