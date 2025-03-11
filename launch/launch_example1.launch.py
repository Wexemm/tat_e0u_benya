from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        
        Node(
            package='turtlesim',
            namespace='turtlesim2',
            executable='turtlesim_node',
            name='turtlesimsim'
        ),
         Node(
            package='tat_e0u_benya',
            executable='draw',
            name='draw',
            output='screen'
        ),
        
        # Node(
        #     package='tat_e0u_benya',
        #     executable='simple_sub_node',
        #     output='screen',
        # ),

        # first comment
    ])