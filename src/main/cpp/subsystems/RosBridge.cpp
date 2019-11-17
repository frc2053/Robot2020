/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/RosBridge.h"
#include "tigertronics/RosBridge/RosBridgeWsClient.h"
#include <memory>

RosbridgeWsClient rbc();

void velocity_callback(client* c, websocketpp::connection_hdl hdl, client::message_ptr msg)
{
    wpi::json j = wpi::json::parse(msg->get_payload());
    twist->linear.x = j["msg"]["linear"]["x"].get<double>();
    twist->linear.y = j["msg"]["linear"]["y"].get<double>();
    twist->linear.z = j["msg"]["linear"]["z"].get<double>();
    twist->angular.x = j["msg"]["angular"]["x"].get<double>();
    twist->angular.y = j["msg"]["angular"]["y"].get<double>();
    twist->angular.z = j["msg"]["angular"]["z"].get<double>();
}

RosBridge::RosBridge() : frc::Subsystem("RosBridgeSubsystem") {
    rbc.SetConnectionUri("ws://localhost:9090");
    rbc.Subscribe("topic_subscriber", "/frc_diff_drive_controller/cmd_vel", velocity_callback);
}

std::shared_ptr<RosTypes::Twist> RosBridge::GetTwist() {
    return twist;
}

void RosBridge::InitDefaultCommand() {
}

