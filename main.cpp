/* Brett Layman
 * 3/26/2018
 * CSCI 441
*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <array>
#include <deque>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <csci441/shader.h>
#include <csci441/matrix.h>
#include <csci441/matrix3.h>
#include <csci441/vector.h>
#include <csci441/uniform.h>

#include "shape.h"
#include "model.h"
#include "camera.h"
#include "renderer.h"
#include "Vertex.h"
#include "ObjReader.h"
#include "CameraMover.h"

using namespace std;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;


bool cam1 = true;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

bool isPressed(GLFWwindow *window, int key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool isReleased(GLFWwindow *window, int key) {
    return glfwGetKey(window, key) == GLFW_RELEASE;
}

// process model matrix based on key input
Matrix processModel(const Matrix& model, GLFWwindow *window) {
    Matrix trans;

    const float TRANS = .01;

    // TRANSLATE
    if (isPressed(window, GLFW_KEY_UP)) { trans.translate(0, TRANS, 0); }
    if (isPressed(window, GLFW_KEY_DOWN)) { trans.translate(0, -TRANS, 0); }
    if (isPressed(window, GLFW_KEY_LEFT)) { trans.translate(-TRANS, 0, 0); }
    if (isPressed(window, GLFW_KEY_RIGHT)) { trans.translate(TRANS, 0, 0); }

    return trans * model;
}



void processInput(GLFWwindow *window) {
    if (isPressed(window, GLFW_KEY_ESCAPE) || isPressed(window, GLFW_KEY_Q)) {
        glfwSetWindowShouldClose(window, true);
    }
}

// for processing single key presses
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // if space is pressed, switch between smooth and flat normal models
    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS){
        if(cam1){
            cam1 = false;
        }
        else{
            cam1 = true;
        }
    }
}

void errorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error: %s\n", description);
}



int main(void) {

    GLFWwindow* window;
    // file names
    string charFile = "../models/bunny.obj";
    string mazeFile = "../models/maze.obj";

    // retrieve vertex array from character file with smooth surface normals
    ObjReader::setRGB(.8,.8,.8); // red character
    vector<float> smoothCharacter = ObjReader::readInObj(true, charFile);

    // retrieve vertex array from maze file with flat surface normals
    ObjReader::setRGB(.2,.6,.2); // green maze
    vector<float> mazeData = ObjReader::readInObj(false, mazeFile);

    glfwSetErrorCallback(errorCallback);

    /* Initialize the library */
    if (!glfwInit()) { return -1; }

    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CSCI441-lab", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // tell glfw what to do on resize
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // init glad
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return -1;
    }

    // create character model
    Model smoothObj(
            smoothCharacter,
            Shader("../vert.glsl", "../frag.glsl"));

    // scale, rotate, and translate model
    Matrix smoothObjScale, smoothObjRot, smoothObjTrans;
    smoothObjScale.scale(2, 2, 2);
    smoothObjRot.rotate_x(90);
    smoothObjTrans.translate(1.1,0,-1.5);
    smoothObj.model = smoothObjScale * smoothObjRot * smoothObjTrans;

    // make a maze
    Model maze(
            mazeData,
            Shader("../vert.glsl", "../frag.glsl"));

    // scale and rotate maze
    Matrix maze_scale, maze_rot;
    maze_rot.rotate_x(90);
    maze_scale.scale(.5, .5, .5);
    maze.model = maze_scale * maze_rot;

    // setup camera 1
    Matrix projection;
    projection.ortho(-2.2f,2.2f,-2.1f,2.3f,0,10); // orthographic
    Camera camera1;
    camera1.projection = projection;
    camera1.eye = Vector(0, 0, 3.0f); // above (z as up)
    camera1.target = Vector(0, 0, 0); // towards origin
    camera1.up = Vector(0, 1, 0); // looking down

    // setup camera 2
    Matrix projection2;
    projection2.perspective(45, 1, .05, 10); // perspective
    Camera camera2;
    camera2.projection = projection2;
    camera2.eye = Vector(2.3, 3, .3); // character start location
    camera2.target = camera2.eye + Vector(0,-1,0); // looking in -Y direction
    camera2.up = Vector(0, 0, 1); // upright

    // and use z-buffering
    glEnable(GL_DEPTH_TEST);

    // create a renderer
    Renderer renderer;

    // set the light position
    Vector lightPos(3.0f, 3.0f, 5.0f);

    // set callback for keyboard input
    glfwSetKeyCallback(window, key_callback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        // process input
        processInput(window);

        /* Render here */
        glClearColor(0.5f, 0.7f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // if viewing from camera 1
        if(cam1){
            // move model with arrow keys
            smoothObj.model = processModel(smoothObj.model, window);
            //render the object
            renderer.render(camera1, smoothObj, lightPos);
            // render the maze
            renderer.render(camera1, maze, lightPos);
        } else{ // from camera 2
            // process camera2 position/rotation, and model matrix
            smoothObj.model = CameraMover::processCamera(camera2,smoothObj.model, window);
            renderer.render(camera2, maze, lightPos); // render the maze
            //renderer.render(camera2, smoothObj, lightPos); // render the character
        }

        /* Swap front and back and poll for io events */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
