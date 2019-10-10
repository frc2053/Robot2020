namespace rostypes {
    typedef struct {
        double x = 0;
        double y = 0;
        double z = 0;
    } Point;

    typedef struct {
        double x = 0;
        double y = 0;
        double z = 0;
    } Vector3;

    typedef struct {
        double x;
        double y;
        double z;
        double w;
    } Quaternion;

    typedef struct {
        Point position;
        Quaternion orientation;
    } Pose;

    typedef struct {
        Vector3 linear;
        Vector3 angular;
    } Twist;
}