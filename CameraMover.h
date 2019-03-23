//
// Created by Brett on 4/3/2018.
//

#ifndef PROGRAM2_CAMERAMOVER_H
#define PROGRAM2_CAMERAMOVER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <csci441/matrix.h>
#include "camera.h"

class CameraMover{
public:

    // transform camera based on key inputs
    static Matrix processCamera(Camera& cam, const Matrix& model, GLFWwindow *window){

        Matrix trans; // character model transformation matrix

        // tilt up
        if (isPressed(window, GLFW_KEY_W)){
            Vector forward = cam.target - cam.eye;
            Matrix reAlign;
            reAlign.rotate_z(-cam.zRotAngle);
            Matrix unAlign;
            unAlign.rotate_z(cam.zRotAngle);
            Matrix rotateUp;
            rotateUp.rotate_x(-1);
            // align camera with Y axis, then rotate the target and up vectors,
            // then rotate back along the z axis
            cam.up = unAlign * rotateUp * reAlign * cam.up;
            forward = unAlign * rotateUp * reAlign * forward;
            cam.target = forward + cam.eye;
        }

        // tilt down
        if (isPressed(window, GLFW_KEY_S)){
            Vector forward = cam.target - cam.eye;
            Matrix reAlign;
            reAlign.rotate_z(-cam.zRotAngle);
            Matrix unAlign;
            unAlign.rotate_z(cam.zRotAngle);
            Matrix rotateDown;
            rotateDown.rotate_x(1);
            // align camera with Y axis, then rotate the target and up vectors,
            // then rotate back along the z axis
            cam.up = unAlign * rotateDown * reAlign * cam.up;
            forward = unAlign * rotateDown * reAlign * forward;
            cam.target = forward + cam.eye;
        }

        // move forward
        if (isPressed(window, GLFW_KEY_UP)) {
            // towards target but no tilt
            Vector flatTarget(cam.target.x(),cam.target.y(),.3);
            Vector forward = flatTarget - cam.eye;
            // move forwards 1/10th of the way towards the target
            Vector moveForward = forward.scale(.01);
            trans.translate(moveForward.x(),moveForward.y() , moveForward.z());
            cam.eye = cam.eye + moveForward;
            cam.target = cam.target + moveForward;
        }

        // move backwards
        if (isPressed(window, GLFW_KEY_DOWN)) {
            // away from the target but no tilt
            Vector flatTarget(cam.target.x(),cam.target.y(),.3);
            Vector backwards = cam.eye - flatTarget;
            // move backwards 1/10th of the way to the target
            Vector moveBackwards = backwards.scale(.01);
            trans.translate(moveBackwards.x(),moveBackwards.y() , moveBackwards.z());
            cam.eye = cam.eye + moveBackwards;
            cam.target = cam.target + moveBackwards;
        }

        // turn left
        if (isPressed(window, GLFW_KEY_LEFT)){
            Vector forward = cam.target - cam.eye;
            Matrix rotateLeft;
            rotateLeft.rotate_z(2);
            cam.zRotAngle += 2;
            // rotate forward vector around z axis to get new target vector
            forward = rotateLeft * forward;
            cam.up = rotateLeft * cam.up;
            cam.target = forward + cam.eye;
        }

        // turn right
        if (isPressed(window, GLFW_KEY_RIGHT)){
            Vector forward = cam.target - cam.eye;
            Matrix rotateRight;
            rotateRight.rotate_z(-2);
            cam.zRotAngle -= 2;
            // rotate forward vector around z axis to get new target vector
            forward = rotateRight * forward;
            cam.up = rotateRight * cam.up;
            cam.target = forward + cam.eye;
        }

        return trans * model; // also update model
    }

    static bool isPressed(GLFWwindow *window, int key) {
        return glfwGetKey(window, key) == GLFW_PRESS;
    }
};

#endif //PROGRAM2_CAMERAMOVER_H
