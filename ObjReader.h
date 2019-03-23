//
// Created by Brett on 4/1/2018.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <array>
#include <deque>

#include "Vertex.h"


#ifndef PROGRAM2_OBJREADER_H
#define PROGRAM2_OBJREADER_H


class ObjReader{


public:
    static int faceNum;
    static int vertNum;
    // color of object can be set
    static float r;
    static float g;
    static float b;

    static void setRGB(float _r, float _g, float _b){
        r = _r;
        g = _g;
        b = _b;
    }

    // break string into deque (so we can remove first) of words
    static deque<string> tokenize(string str){
        deque<string> arr;
        stringstream ss(str);

        for (int i = 0; ss.good() && i < 4;++i){
            string temp;
            ss >> temp;
            arr.push_back(temp);
            // set number of faces and vertices using file data
            if(i == 1){
                if(arr[i] == "Faces:"){
                    ss >> faceNum;
                }
                else if( arr[i] == "Vertices:"){
                    ss >> vertNum;
                }
            }
        }
        return arr;
    }

// use face normals and arrange data so that it's ready for model class
    static vector<float> parseFlat(vector <vector<float>> vertexArr,vector <vector<int>>  faceArr) {
        vector<float> finalData; // data to be send to Model

        Vertex* verts = new Vertex[vertNum]; // array of Vertex objects to store data about that vertex
        // for every vertex
        for (int i = 0; i < vertNum; ++i) {
            // set x,y,z values for Vertex obj
            float x = vertexArr[i][0];
            float y = vertexArr[i][1];
            float z = vertexArr[i][2];
            verts[i].setXYZ(x, y, z);
        }

        // for every face
        for (vector<int> face: faceArr){
            // get face normal
            vector<float> v1 = vertexArr[face[0]-1];
            vector<float> v2 = vertexArr[face[1]-1];
            vector<float> v3 = vertexArr[face[2]-1];
            Face currFace = Face(v1,v2,v3);
            // for every vertex in the face
            for (int vertIndex : face){
                // set normal, then get data
                verts[vertIndex-1].setNormal(currFace.calcNormal());
                verts[vertIndex-1].setColor(r,g,b);
                vector<float> data = verts[vertIndex-1].getData();
                // add data to final data
                finalData.insert(finalData.end(),data.begin(),data.end());
            }
        }
        return finalData;
    }

// calculate average normals and arrange data so that it's ready for model class
    static vector<float> parseSmooth(vector <vector<float>> vertexArr,vector <vector<int>>  faceArr){
        vector<float> finalData; // data to be send to Model

        Vertex* verts = new Vertex[vertNum]; // array of Vertex objects to store data about that vertex
        // for every vertex
        for (int i = 0; i < vertNum; ++i) {
            // set x,y,z values for Vertex obj
            float x = vertexArr[i][0];
            float y = vertexArr[i][1];
            float z = vertexArr[i][2];
            verts[i].setXYZ(x,y,z);
            // for every face
            for (int j = 0; j < faceNum; ++j) {
                // for every vertex in that face
                for (int k = 0; k < 3; ++k) {
                    // if the vertex matches the current vertex in vertArr
                    if(faceArr[j][k] - 1 == i){
                        // add that face to the vertex's faces
                        vector<float> v1 = vertexArr[faceArr[j][0]-1];
                        vector<float> v2 = vertexArr[faceArr[j][1]-1];
                        vector<float> v3 = vertexArr[faceArr[j][2]-1];
                        Face f = Face(v1,v2,v3);
                        verts[i].addFace(f);
                    }
                }
            }
            // calculate normal based on faces just added
            verts[i].calcNormal();
        }
        // for every face given by obj file
        for (vector<int> face: faceArr){
            // add the vertex data of the vertices in that face
            for (int index : face){
                verts[index-1].setColor(r,g,b);
                vector<float> data = verts[index-1].getData();
                finalData.insert(finalData.end(),data.begin(),data.end());
            }
        }
        return finalData;
    }

// read in obj file, parse lines, pass data for further parsing before returning result
    static vector<float> readInObj(bool smooth, string& fileName){
        // read duck obj file
        ifstream file;
        file.open(fileName);
        if(file){
            string str;
            vector <vector<float>> vertexArr;
            vector <vector<int>>  faceArr;
            // for each line in file
            while (getline(file, str))
            {
                // store words in line
                deque<string> words = tokenize(str);
                // if first word is "v", parse and rest of line to vertexArr
                if(words.front() == "v" ){
                    words.pop_front();
                    vector<float> floats;
                    for(string word : words){
                        float f = stof(word);
                        floats.push_back(f);
                    }
                    vertexArr.push_back(floats);
                }
                    // if first word is "f", parse and rest of line to faceArr
                else if (words.front() == "f" ){
                    words.pop_front();
                    vector<int> ints;
                    for(string word : words){
                        int integer = stoi(word);
                        ints.push_back(integer);
                    }
                    faceArr.push_back(ints);
                }
            }
            // if smooth vertices requested, pass arrays to parseSmooth to get final result
            if(smooth){
                return parseSmooth(vertexArr, faceArr);
            }
                // otherwise pass to parseFlat
            else{
                return parseFlat(vertexArr,faceArr);
            }
        }
            // else error reading file
        else
        {
            cout << "object file read in error" << endl;
            vector<float> empty;
            return empty;
        }
    }
};

float ObjReader::r = 0;
float ObjReader::g = 0;
float ObjReader::b = 0;
int ObjReader::faceNum = 0;
int ObjReader::vertNum = 0;


#endif //PROGRAM2_OBJREADER_H
