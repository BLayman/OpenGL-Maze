//
// Created by Brett on 3/25/2018.
//

#ifndef LAB6_VERTEX_H
#define LAB6_VERTEX_H

#include <iostream>
#include <vector>
#include "Face.h"

using namespace std;

// to store information about vertices in 3D model
class Vertex{
    vector<float> xyz; // coordinates
    vector<Face> faces; // adjacent faces
    vector<float> normal; // normal
    vector<float> color; // color


public:
    // set default color to red
    Vertex(): color ({0.0f,0.0f,0.0f}){}

    void setColor(float r, float g, float b){
        color[0] = r;
        color[1] = g;
        color[2] = b;
    }

    // set coordinates
    void setXYZ(float x, float y, float z){
        xyz.push_back(x);
        xyz.push_back(y);
        xyz.push_back(z);
    }
    // add adjacent face
    void addFace(Face f){
        faces.push_back(f);
    }

    void print(vector<float> arr, int len){
        for (int i = 0; i < len; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    // set normal directly
    void setNormal(vector<float> norm){
        normal = norm;
    }

    // calculate normal by averaging adjacent faces
    void calcNormal(){
        vector<float> average = {0,0,0};
        for(Face f : faces){
            vector<float> norm = f.calcNormal();
            for (int i = 0; i < 3; ++i) {
                average[i] += norm[i];
            }
        }
        for (int j = 0; j < 3; ++j) {
            average[j] /= 3;
        }
        Vector avgVec = Vector(average[0],average[1],average[2]);
        Vector avgNormalized = avgVec.normalized();
        average[0] = avgNormalized.x();
        average[1] = avgNormalized.y();
        average[2] = avgNormalized.z();
        normal = average;
    }

    // retrive data in vertex array format (coordinates, color, normal)
    vector<float> getData(){
        vector<float> data = xyz;
        data.insert(data.end(), color.begin(), color.end());
        data.insert(data.end(), normal.begin(), normal.end());
        //print(data, 9);
        return data;
    }
};


#endif //LAB6_VERTEX_H
