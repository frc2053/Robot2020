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
#include <frc_new/geometry/Pose2d.h>
#include <frc_new/geometry/Twist2d.h>


static std::shared_ptr<RosTypes::Twist> twist = std::make_shared<RosTypes::Twist>();

class RosBridge : public frc::Subsystem {
private:
  int seq = 0;
  RosBridgeWsClient rbc{};
public:
  RosBridge();
  void SendOdometry();
  void InitDefaultCommand() override;
  void Periodic() override;
  std::shared_ptr<RosTypes::Twist> GetTwist();
  RosTypes::Odometry ConstructOdom(const frc_new::Pose2d& currentPose, const frc_new::Twist2d& currentTwist);
};
