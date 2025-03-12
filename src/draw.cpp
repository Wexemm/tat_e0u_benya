#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/srv/teleport_absolute.hpp"
#include "turtlesim/srv/set_pen.hpp"
#include <chrono>

using namespace std::chrono_literals;

class CubeDrawer : public rclcpp::Node {
public:
    CubeDrawer() : Node("cube") {
        speed_publisher = create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        teleport_service = create_client<turtlesim::srv::TeleportAbsolute>("/turtle1/teleport_absolute");
        pen_service = create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");

        rclcpp::sleep_for(1s); 
        toggle_pen(false);
        teleport_to_position(4.0, 3.0, 0.0);
        rclcpp::sleep_for(1s);  
        toggle_pen(true);

        move_by_distance(3.0);
        rotate(M_PI_2);
        move_by_distance(3.0);
        rotate(M_PI_2);
        move_by_distance(3.0);
        rotate(M_PI_2);
        move_by_distance(3.0);

        toggle_pen(false);
        teleport_to_position(5.5, 4.5, 0.0);
        toggle_pen(true);

        move_by_distance(3.0);
        rotate(M_PI_2);
        move_by_distance(3.0);
        rotate(M_PI_2);
        move_by_distance(3.0);
        rotate(M_PI_2);
        move_by_distance(3.0);

        toggle_pen(false);
        teleport_to_position(4.0, 3.0, 0.0);
        toggle_pen(true);
        teleport_to_position(5.5, 4.5, 0.0);

        toggle_pen(false);
        teleport_to_position(7.0, 3.0, 0.0);
        toggle_pen(true);
        teleport_to_position(8.5, 4.5, 0.0);

        toggle_pen(false);
        teleport_to_position(7.0, 6.0, 0.0);
        toggle_pen(true);
        teleport_to_position(8.5, 7.5, 0.0);

        toggle_pen(false);
        teleport_to_position(4.0, 6.0, 0.0);
        toggle_pen(true);
        teleport_to_position(5.5, 7.5, 0.0);

        toggle_pen(false);
        RCLCPP_INFO(get_logger(), "Cube complete!!");
    }

private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr speed_publisher;
    rclcpp::Client<turtlesim::srv::TeleportAbsolute>::SharedPtr teleport_service;
    rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr pen_service;

    void teleport_to_position(double x, double y, double angle) {
        auto request = std::make_shared<turtlesim::srv::TeleportAbsolute::Request>();
        request->x = x;
        request->y = y;
        request->theta = angle;
        teleport_service->async_send_request(request);
        rclcpp::sleep_for(500ms);
    }

    void toggle_pen(bool state) {
        auto request = std::make_shared<turtlesim::srv::SetPen::Request>();
        request->r = 0;
        request->g = 0;
        request->b = 0;
        request->width = 3;
        request->off = !state;
        pen_service->async_send_request(request);
    }

    void move_by_distance(double length) {
        geometry_msgs::msg::Twist msg;
        msg.linear.x = 1;
        double target_time = length / msg.linear.x;
        rclcpp::Time start_time = now();
        
        while ((now() - start_time).seconds() < target_time) {
            speed_publisher->publish(msg);
            rclcpp::sleep_for(50ms);
        }
        
        speed_publisher->publish(geometry_msgs::msg::Twist());
    }

    void rotate(double rotation_angle) {
        geometry_msgs::msg::Twist msg;
        msg.angular.z = rotation_angle;
        rclcpp::Time start_time = now();
        double rotation_duration = 1.0;
        while ((now() - start_time).seconds() < rotation_duration) {
            speed_publisher->publish(msg);
            rclcpp::sleep_for(50ms);
        }
        speed_publisher->publish(geometry_msgs::msg::Twist());
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CubeDrawer>());
    rclcpp::shutdown();
    return 0;
}