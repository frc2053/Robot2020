/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/RosBridge.h"

void velocity_callback(std::shared_ptr<WsClient::Connection> /*connection*/, std::shared_ptr<WsClient::InMessage> in_message)
{
  //std::cout << "subscriberCallback(): Message Received: " << in_message->string() << std::endl;
  Document doc;
  if(doc.Parse<0>(in_message->string().c_str()).HasParseError()) {
    std::cout << "Parse Error!\n";
  }
  else {
    twist->linear.x = doc["msg"]["linear"]["x"].GetDouble();
    twist->linear.y = doc["msg"]["linear"]["y"].GetDouble();
    twist->linear.z = doc["msg"]["linear"]["z"].GetDouble();
    twist->angular.x = doc["msg"]["angular"]["x"].GetDouble();
    twist->angular.y = doc["msg"]["angular"]["y"].GetDouble();
    twist->angular.z = doc["msg"]["angular"]["z"].GetDouble();
  }
}

RosBridge::RosBridge() : Subsystem("RosBridgeSubsystem") {
    twist = make_shared<RosTypes::Twist>();
    rbc = RosbridgeWsClient("localhost:5800");
    rbc.addClient("topic_subscriber");
    rbc.subscribe("topic_subscriber", "/cmd_vel", velocity_callback);
}

RosBridge::~RosBridge() {
    rbc.removeClient("topic_subscriber");
}

std::shared_ptr<RosTypes::Twist> RosBridge::GetTwist() {
    return twist;
}

void RosBridge::InitDefaultCommand() {
}

