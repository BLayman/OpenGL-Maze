//
// Created by Brett on 3/25/2018.
//

#ifndef LAB6_FACE_H
#define LAB6_FACE_H

#include "Vertex.h"

// for storing triangular face data: vertices of face, normal of face
class Face{
public:
    // vertices
    vector<float> v1;
    vector<float> v2;
    vector<float> v3;
    // normal
    vector<float> normal;

    Face(vector<float> _v1, vector<float> _v2, vector<float> _v3): v1 (_v1), v2 (_v2), v3 (_v3){}

    // calculate normal by taking cross product of 2 edges of the triangle
    vector<float> calcNormal(){
        Vector vec1 = Vector(v1[0],v1[1],v1[2]);
        Vector vec2 = Vector(v2[0],v2[1],v2[2]);
        Vector vec3 = Vector(v3[0],v3[1],v3[2]);
        Vector a = vec2 - vec1;
        Vector b = vec3 - vec1;
        Vector c = a.cross(b).normalized();
        vector<float> norm = {c.x(),c.y(),c.z()};
        return norm;
    }
};

#endif //LAB6_FACE_H
