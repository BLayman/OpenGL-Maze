#ifndef _CSCI441_CAMERA_H_
#define _CSCI441_CAMERA_H_

#include <csci441/matrix.h>
#include <csci441/vector.h>

class Camera {
public:
    Matrix projection;
    Vector eye;
    Vector target;
    Vector up;
    float zRotAngle;

    Camera() : eye(0,0,0), target(0,0,0), up(0,0,0), zRotAngle(0) {}

    Matrix look_at() const {
        Matrix mat;
        mat.look_at(eye, target, up);
        return mat;
    }
};

#endif
