#pragma once

#include <cmath>
#define PI 3.14159265358979323846

namespace RosTypes {

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
}
