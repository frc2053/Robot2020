#pragma once

#include <cmath>
#include <cstdint>
#include <string>
#include <wpi/json.h>
#define PI 3.14159265358979323846

namespace RosTypes {

struct Time {
    uint32_t sec = 0;
    uint32_t nsec = 0;
};

struct Header {
    uint32_t seq;
    Time stamp = Time();
    std::string frame_id;
};

struct Point {
    double x = 0;
    double y = 0;
    double z = 0;
};

struct Quaternion {
    double x = 0;
    double y = 0;
    double z = 0;
    double w = 0;
};

struct EulerAngles {
    double roll = 0;
    double pitch = 0;
    double yaw = 0;
};

struct Vector3 {
    double x = 0;
    double y = 0;
    double z = 0;
};

struct Twist {
    Vector3 linear = Vector3();
    Vector3 angular = Vector3();
};

struct Pose {
    Point position = Point();
    Quaternion orientation = Quaternion();
};

struct PoseWithCovariance {
    Pose pose = Pose();
    double covariance[36] = {};
};

struct TwistWithCovariance {
    Twist twist = Twist();
    double covariance[36] = {};
};

struct Odometry {
    Header header = Header();
    std::string child_frame_id;
    PoseWithCovariance pose = PoseWithCovariance();
    TwistWithCovariance twist = TwistWithCovariance();
};

static EulerAngles QuaternionToEuler(Quaternion quaternion) {
    EulerAngles retVal = EulerAngles();
    double sqw = quaternion.w*quaternion.w;
    double sqx = quaternion.x*quaternion.x;
    double sqy = quaternion.y*quaternion.y;
    double sqz = quaternion.z*quaternion.z;
	double unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
	double test = quaternion.x*quaternion.y + quaternion.z*quaternion.w;
	if (test > 0.499*unit) { // singularity at north pole
		retVal.yaw = 2 * atan2(quaternion.x,quaternion.w);
		retVal.pitch = PI/2;
		retVal.roll = 0;
		return retVal;
	}
	if (test < -0.499*unit) { // singularity at south pole
		retVal.yaw = -2 * atan2(quaternion.x,quaternion.w);
		retVal.pitch = -PI/2;
		retVal.roll = 0;
		return retVal;
	}
    retVal.yaw  = atan2(2*quaternion.y*quaternion.w-2*quaternion.x*quaternion.z , sqx - sqy - sqz + sqw);
	retVal.pitch = asin(2*test/unit);
	retVal.roll = atan2(2*quaternion.x*quaternion.w-2*quaternion.y*quaternion.z , -sqx + sqy - sqz + sqw);
    return retVal;
}

static Quaternion EulerToQuaternion(EulerAngles angles)
{
    // Abbreviations for the various angular functions
    double cy = cos(angles.yaw * 0.5);
    double sy = sin(angles.yaw * 0.5);
    double cp = cos(angles.pitch * 0.5);
    double sp = sin(angles.pitch * 0.5);
    double cr = cos(angles.roll * 0.5);
    double sr = sin(angles.roll * 0.5);

    Quaternion q;
    q.w = cy * cp * cr + sy * sp * sr;
    q.x = cy * cp * sr - sy * sp * cr;
    q.y = sy * cp * sr + cy * sp * cr;
    q.z = sy * cp * cr - cy * sp * sr;

    return q;
}

static wpi::json OdomToJson(const Odometry& odom) {
    wpi::json retVal;

    retVal["header"] = {
        {"seq", odom.header.seq},
        {"stamp", {
            {"secs", odom.header.stamp.sec},
            {"nsecs", odom.header.stamp.nsec}
        }},
        {"frame_id", odom.header.frame_id}
    };

    retVal["child_frame_id"] = odom.child_frame_id;

    retVal["pose"] = {
        {"pose", {
            {"position", {
                {"x", odom.pose.pose.position.x},
                {"y", odom.pose.pose.position.y},
                {"z", odom.pose.pose.position.z}
            }},
            {"orientation", {
                {"x", odom.pose.pose.orientation.x},
                {"y", odom.pose.pose.orientation.y},
                {"z", odom.pose.pose.orientation.z},
                {"w", odom.pose.pose.orientation.w}
            }}
        }},
        {"covariance", odom.pose.covariance}
    };

    retVal["twist"] = {
        {"twist", {
            {"linear", {
                {"x", odom.twist.twist.linear.x},
                {"y", odom.twist.twist.linear.y},
                {"z", odom.twist.twist.linear.z}
            }},
            {"angular", {
                {"x", odom.twist.twist.angular.x},
                {"y", odom.twist.twist.angular.y},
                {"z", odom.twist.twist.angular.z}
            }}
        }},
        {"covariance", odom.twist.covariance}
    };

    return retVal;
}

//namespace RosTypes
}
