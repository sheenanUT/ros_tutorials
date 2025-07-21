#include <rclcpp/rclcpp.hpp>
#include <turtlesim_ds/msg/pose.hpp>
#include <geometry_msgs/msg/twist.hpp>

class MimicNode : public rclcpp::Node
{
public:
  MimicNode() : rclcpp::Node("turtle_mimic")
  {
    twist_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("output/cmd_vel", 1);
    pose_sub_ = this->create_subscription<turtlesim_ds::msg::Pose>(
      "input/pose", 1, std::bind(&MimicNode::poseCallback, this, std::placeholders::_1));
  }

private:
  void poseCallback(const turtlesim_ds::msg::Pose::ConstSharedPtr pose)
  {
    geometry_msgs::msg::Twist twist;
    twist.angular.z = pose->angular_velocity;
    twist.linear.x = pose->linear_velocity;
    twist_pub_->publish(twist);
  }

  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_pub_;
  rclcpp::Subscription<turtlesim_ds::msg::Pose>::SharedPtr pose_sub_;
};

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MimicNode>());
}

