#include "subsystems/SwerveSubsystem.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "units/units.h"
#include "frc/geometry/Pose2d.h"
#include "frc/geometry/Twist2d.h"

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

SwerveSubsystem::SwerveSubsystem() {
    frc::SmartDashboard::PutString("Jetson IP", jetson_ip);
    rbc.SetConnectionUri("ws://" + jetson_ip + ":5800");
    rbc.Subscribe("topic_subscriber", "/drive_controller/cmd_vel", velocity_callback);
    rbc.Advertise("odom_sender", "/drive_controller/odom", "nav_msgs/Odometry");
    rbc.Advertise("imu_sender", "/imu", "sensor_msgs/Imu");
    m_swerve.LogModulesToDashboard();
}

std::shared_ptr<RosTypes::Twist> SwerveSubsystem::GetTwist() {
    return twist;
}

void SwerveSubsystem::DriveWithRos(units::meters_per_second_t xSpeed, units::meters_per_second_t ySpeed, units::radians_per_second_t rotSpeed) {
    frc::SmartDashboard::PutNumber("X Cmd", xSpeed.value());
    frc::SmartDashboard::PutNumber("Y Cmd", ySpeed.value());
    frc::SmartDashboard::PutNumber("Rot Cmd", rotSpeed.value());
    frc::SmartDashboard::PutString("Drive Mode", "ROS");
    m_swerve.Drive(xSpeed, ySpeed, rotSpeed, false, true);
}

units::degree_t SwerveSubsystem::GetImuYaw() {
    return m_swerve.GetAngle().Degrees();
}

void SwerveSubsystem::ManualWheelMove(std::string wheel, int abs_setpoint) {
    m_swerve.ManualMoveWheel(wheel, abs_setpoint);
}

void SwerveSubsystem::ManualWheelMove(std::string wheel, units::radian_t angle, units::meters_per_second_t speed) {
    m_swerve.ManualMoveWheel(wheel, angle, speed);
}

void SwerveSubsystem::DriveWithJoystick(double x, double y, double rot, bool fieldRelative) {
    //need to negative strafe because if you push right on the joystick it returns a + value
    //however, the kinematics expects that left is positive for the y axis
    //similar for rot axis because if you push right on the stick, it returns a positive value
    //however, the kinematics expects a "positive" rotation to be CCW
    double strafeAxis = -1 * x;
    double fowAxis = -1 * y;
    double rotAxis = -1 * rot;
    
    if(strafeAxis > -.2 && strafeAxis < .2) {
        strafeAxis = 0;
    }
    else {
        strafeAxis = strafeAxis * fabs(strafeAxis);
    }
    if(fowAxis > -.2 && fowAxis < .2) {
        fowAxis = 0;
    }
    else {
        fowAxis = fowAxis * fabs(fowAxis);
    }
    if(rotAxis > -.2 && rotAxis < .2) {
        rotAxis = 0;
    }
    else {
        rotAxis = rotAxis * fabs(rotAxis);
    }
    frc::SmartDashboard::PutNumber("X Joystick", strafeAxis);
    frc::SmartDashboard::PutNumber("Y Joystick", fowAxis);
    frc::SmartDashboard::PutNumber("Rot Joystick", rotAxis);
    frc::SmartDashboard::PutString("Drive Mode", "Joystick");
    //x + is forward
    //y + is left
    //rot + is CCW
    const auto xSpeed = fowAxis * m_swerve.kMaxSpeed;
    const auto ySpeed = strafeAxis * m_swerve.kMaxSpeed;
    const auto rotSpeed = rotAxis * m_swerve.kMaxAngularSpeed;
    m_swerve.Drive(xSpeed, ySpeed, rotSpeed, fieldRelative, false);
}

void SwerveSubsystem::AutoDrive(units::meters_per_second_t xSpeed, units::meters_per_second_t ySpeed, units::radians_per_second_t rotSpeed) {
    frc::SmartDashboard::PutString("Drive Mode", "Auto");
    m_swerve.Drive(xSpeed, ySpeed, rotSpeed, false, true);
}

void SwerveSubsystem::Periodic() {
    SendOdometry();
    SendIMU();
    currentPose = m_swerve.UpdateOdometry();
    currentTwist = m_swerve.GetDrivetrainSpeedsWorld();
    currentIMUData = m_swerve.GetIMUData();
    frc::SmartDashboard::PutNumber("X Pose: ", currentPose.Translation().X().value());
    frc::SmartDashboard::PutNumber("Y Pose: ", currentPose.Translation().Y().value());
    frc::SmartDashboard::PutNumber("Yaw Pose: ", currentPose.Rotation().Degrees().value());
}

const frc::Pose2d& SwerveSubsystem::GetCurrentPose() {
    return currentPose;
}

const frc::Twist2d& SwerveSubsystem::GetCurrentTwist() {
    return currentTwist;
}

std::vector<double> SwerveSubsystem::GetIMUData() {
    return currentIMUData;
}

RosTypes::Odometry SwerveSubsystem::ConstructOdom(const frc::Pose2d& currentPose, const frc::Twist2d& currentTwist) {
    RosTypes::Odometry odom;

    odom.child_frame_id = "base_link";

    odom.header.frame_id = "odom";
    odom.header.seq = seqOdom;
    odom.header.stamp.sec = std::chrono::system_clock::now().time_since_epoch().count() * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;

    odom.pose.pose.position.x = currentPose.Translation().X().value();
    odom.pose.pose.position.y = currentPose.Translation().Y().value();

    RosTypes::EulerAngles orientation;
    orientation.yaw = currentPose.Rotation().Radians().value();

    odom.pose.pose.orientation = RosTypes::EulerToQuaternion(orientation);

    odom.twist.twist.linear.x = currentTwist.dx.value();
    odom.twist.twist.linear.y = currentTwist.dy.value();
    odom.twist.twist.angular.z = currentTwist.dtheta.value();
    seqOdom++;
    return odom;
}

RosTypes::IMU SwerveSubsystem::ConstructIMU(double roll, double pitch, double yaw, double velX, double velY, double velZ, double accelX, double accelY, double accelZ) {
    RosTypes::IMU imu;

    imu.header.frame_id = "imu";
    imu.header.seq = seqImu;
    imu.header.stamp.sec = std::chrono::system_clock::now().time_since_epoch().count() * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;

    RosTypes::EulerAngles orientation;
    orientation.roll = roll;
    orientation.pitch = pitch;
    orientation.yaw = yaw;

    imu.orientation = RosTypes::EulerToQuaternion(orientation);

    imu.angular_velocity.x = velX;
    imu.angular_velocity.y = velY;
    imu.angular_velocity.z = velZ;

    imu.linear_accel.x = accelX;
    imu.linear_accel.y = accelY;
    imu.linear_accel.z = accelZ;

    seqImu++;
    return imu;
}

void SwerveSubsystem::SendOdometry() {
    RosTypes::Odometry odom = ConstructOdom(GetCurrentPose(), GetCurrentTwist());
    rbc.Publish("odom_sender", "/drive_controller/odom", RosTypes::OdomToJson(odom));
}

void SwerveSubsystem::SendIMU() {
    std::vector<double> data = GetIMUData();
    RosTypes::IMU imu = ConstructIMU(0, 0, 0, 0, 0, 0, 0, 0, 0);
    rbc.Publish("imu_sender", "/imu", RosTypes::IMUToJson(imu));
}

void SwerveSubsystem::ChangeRosConnection(std::string uri) {
    rbc.Disconnect("topic_subscriber");
    rbc.Disconnect("odom_sender");
    rbc.Disconnect("imu_sender");
    rbc.SetConnectionUri("ws://" + uri + ":5800");
    rbc.Subscribe("topic_subscriber", "/drive_controller/cmd_vel", velocity_callback);
    rbc.Advertise("odom_sender", "/drive_controller/odom", "nav_msgs/Odometry");
    rbc.Advertise("imu_sender", "/imu", "sensor_msgs/Imu");
}