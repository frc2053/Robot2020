/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <tigertronics/RosBridge/RosBridgeWsClient.h>
#include <tigertronics/RosBridge/RosTypes.h>
#include <memory>

static std::shared_ptr<RosTypes::Twist> twist = std::make_shared<RosTypes::Twist>();

class RosBridge : public frc::Subsystem {
private:
  RosBridgeWsClient rbc{};
public:
  RosBridge();
  void InitDefaultCommand() override;
  std::shared_ptr<RosTypes::Twist> GetTwist();
};
