/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/RosBridge.h"
#include "tigertronics/RosBridge/RosBridgeWsClient.h"
#include <memory>
#include "frc/smartdashboard/SmartDashboard.h"
#include "Robot.h"


void velocity_callback(client* c, websocketpp::connection_hdl hdl, client::message_ptr msg)
{
    printf("got message!\n");
    wpi::json j = wpi::json::parse(msg->get_payload());
    twist->linear.x = j["msg"]["linear"]["x"].get<double>();
    twist->linear.y = j["msg"]["linear"]["y"].get<double>();
    twist->linear.z = j["msg"]["linear"]["z"].get<double>();
    twist->angular.x = j["msg"]["angular"]["x"].get<double>();
    twist->angular.y = j["msg"]["angular"]["y"].get<double>();
    twist->angular.z = j["msg"]["angular"]["z"].get<double>();
}

RosBridge::RosBridge() : frc::Subsystem("RosBridgeSubsystem") {
    rbc.SetConnectionUri("ws://192.168.1.110:5800");
    rbc.Subscribe("topic_subscriber", "/frc_diff_drive_controller/cmd_vel", velocity_callback);
    rbc.Advertise("odom_sender", "/odom", "nav_msgs/Odometry");
}

std::shared_ptr<RosTypes::Twist> RosBridge::GetTwist() {
    return twist;
}

void RosBridge::InitDefaultCommand() {
}

void RosBridge::Periodic() {
    SendOdometry();
}

RosTypes::Odometry RosBridge::ConstructOdom(const frc_new::Pose2d& currentPose, const frc_new::Twist2d& currentTwist) {
    RosTypes::Odometry odom;

    odom.child_frame_id = "base_link";

    odom.header.frame_id = "base_link";
    odom.header.seq = seq;
    odom.header.stamp.sec = std::chrono::system_clock::now().time_since_epoch().count() * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;

    odom.pose.pose.position.x = currentPose.Translation().X().value();
    odom.pose.pose.position.y = currentPose.Translation().Y().value();

    RosTypes::EulerAngles orientation;
    orientation.yaw = currentPose.Rotation().Radians().value();

    odom.pose.pose.orientation = RosTypes::EulerToQuaternion(orientation);

    odom.twist.twist.linear.x = currentTwist.dx.value();
    odom.twist.twist.linear.y = currentTwist.dy.value();
    odom.twist.twist.angular.z = currentTwist.dtheta.value();
    seq++;
    return odom;
}

void RosBridge::SendOdometry() {
    RosTypes::Odometry odom = ConstructOdom(Robot::swerveSubsystem->GetCurrentPose(), Robot::swerveSubsystem->GetCurrentTwist());
    rbc.Publish("odom_sender", "/odom", RosTypes::OdomToJson(odom));
}

