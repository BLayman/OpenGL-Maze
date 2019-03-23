#ifndef _CSCI441_SHAPE_H_
#define _CSCI441_SHAPE_H_

#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;

template <typename T, typename N, typename C>
void add_vertex(T& coords, const N& x, const N& y, const N& z,
        const C& r, const C& g, const C& b,
        const Vector& n=Vector(1,0,0), bool with_noise=false) {
    // adding color noise makes it easier to see before shading is implemented
    float noise = 1-with_noise*(rand()%150)/100.;
    coords.push_back(x);
    coords.push_back(y);
    coords.push_back(z);
    coords.push_back(r*noise);
    coords.push_back(g*noise);
    coords.push_back(b*noise);

    Vector normal = n.normalized();
    coords.push_back(normal.x());
    coords.push_back(normal.y());
    coords.push_back(normal.z());
}

// for calculating a normal of a face, given the three corners of the triangle
Vector calcFlatNormal(Vector pt1, Vector pt2, Vector pt3){
    Vector a = pt2 - pt1;
    Vector b = pt3 - pt1;
    Vector c = b.cross(a).normalized();
    return c;
}


class DiscoCube {
public:
    std::vector<float> coords;
    DiscoCube() : coords{
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0,

        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0,
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0,
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0,
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0,

        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0
    } {}

};

class Cylinder {
public:
    std::vector<float> coords;
    Cylinder(unsigned int n, float r, float g, float b) {
        double step_size = 2*M_PI / n;
        double c_x=0;
        double c_y=0;
        double h = .5;
        float radius = .5;

        for (int i = 0; i < n; ++i) {
            // vertex i
            double theta_i = i*step_size;
            double vi_x = radius*cos(theta_i);
            double vi_y = radius*sin(theta_i);

            // vertex i+1
            double theta_ip1 = ((i+1)%n)*step_size;
            double vip1_x = radius*cos(theta_ip1);
            double vip1_y = radius*sin(theta_ip1);

            add_vertex(coords, vi_x, -h, vi_y, r, g, b);
            add_vertex(coords, vi_x, h, vi_y, r, g, b);
            add_vertex(coords, vip1_x, -h, vip1_y, r, g, b);

            // add triangle vip1L, viH, vip1H
            add_vertex(coords, vip1_x, -h, vip1_y, r, g, b);
            add_vertex(coords, vi_x, h, vi_y, r, g, b);
            add_vertex(coords, vip1_x, h, vip1_y, r, g, b);

            // add high triangle vi, vip1, 0
            Vector nh(0, 1, 0);
            add_vertex(coords, vip1_x, h, vip1_y, r, g, b);
            add_vertex(coords, vi_x, h, vi_y, r, g, b);
            add_vertex(coords, c_x, h, c_y, r, g, b);

            // // add low triangle vi, vip1, 0
            Vector nl(0, -1, 0);
            add_vertex(coords, vip1_x, -h, vip1_y, r, g, b);
            add_vertex(coords, c_x, -h, c_y, r, g, b);
            add_vertex(coords, vi_x, -h, vi_y, r, g, b);
        }
    }
};


class Cone {
public:
    std::vector<float> coords;
    Cone(unsigned int n, float r, float g, float b) {

        double step_size = 2*M_PI / n;
        double c_x=0;
        double c_y=0;
        double h = .5;
        float radius = .5;

        for (int i = 0; i < n; ++i) {
            // vertex i
            double theta_i = i*step_size;
            double vi_x = radius*cos(theta_i);
            double vi_y = radius*sin(theta_i);

            // vertex i+1
            double theta_ip1 = ((i+1)%n)*step_size;
            double vip1_x = radius*cos(theta_ip1);
            double vip1_y = radius*sin(theta_ip1);

            // add triangle viL, viH, vip1L

            add_vertex(coords, vi_x, -h, vi_y, r, g, b);
            add_vertex(coords, c_x, h, c_y, r, g, b);
            add_vertex(coords, vip1_x, -h, vip1_y, r, g, b);

            // // add low triangle vi, vip1, 0
            add_vertex(coords, vip1_x, -h, vip1_y, r, g, b);
            add_vertex(coords, c_x, -h, c_y, r, g, b);
            add_vertex(coords, vi_x, -h, vi_y, r, g, b);
        }
    }
};

class Sphere {
    double x(float r, float phi, float theta){
        return r*cos(theta)*sin(phi);
    }

    double y(float r, float phi, float theta){
        return r*sin(theta)*sin(phi);
    }

    double z(float r, float phi, float theta){
        return r*cos(phi);
    }

public:
    std::vector<float> coords;
    bool flatShading = true;
    Sphere(unsigned int n, float radius, float r, float g, float b) {
        int n_steps = (n%2==0) ? n : n+1;
        double step_size = 2*M_PI / n_steps;

        for (int i = 0; i < n_steps/2.0; ++i) {
            for (int j = 0; j < n_steps; ++j) {
                double phi_i = i*step_size;
                double phi_ip1 = ((i+1)%n_steps)*step_size;
                double theta_j = j*step_size;
                double theta_jp1 = ((j+1)%n_steps)*step_size;

                // vertex i,j
                double vij_x = x(radius, phi_i, theta_j);
                double vij_y = y(radius, phi_i, theta_j);
                double vij_z = z(radius, phi_i, theta_j);

                // vertex i+1,j
                double vip1j_x = x(radius, phi_ip1, theta_j);
                double vip1j_y = y(radius, phi_ip1, theta_j);
                double vip1j_z = z(radius, phi_ip1, theta_j);

                // vertex i,j+1
                double vijp1_x = x(radius, phi_i, theta_jp1);
                double vijp1_y = y(radius, phi_i, theta_jp1);
                double vijp1_z = z(radius, phi_i, theta_jp1);

                // vertex i+1,j+1
                double vip1jp1_x = x(radius, phi_ip1, theta_jp1);
                double vip1jp1_y = y(radius, phi_ip1, theta_jp1);
                double vip1jp1_z = z(radius, phi_ip1, theta_jp1);

                // add triangle

                //cout << "1" << endl;
                Vector norm1 = calcFlatNormal(Vector(vij_x,vij_y,vij_z), Vector(vijp1_x,vijp1_y,vijp1_z), Vector(vip1j_x,vip1j_y,vip1j_z));
                add_vertex(coords, vij_x, vij_y, vij_z, r, g, b, norm1);
                add_vertex(coords, vijp1_x, vijp1_y, vijp1_z, r, g, b, norm1);
                add_vertex(coords, vip1j_x, vip1j_y, vip1j_z, r, g, b, norm1);

                // add triangle
                //cout << "2" << endl;
                Vector norm2 = calcFlatNormal(Vector(vijp1_x,vijp1_y,vijp1_z), Vector(vip1jp1_x,vip1jp1_y,vip1jp1_z), Vector(vip1j_x,vip1j_y,vip1j_z));
                add_vertex(coords, vijp1_x, vijp1_y, vijp1_z, r, g, b, norm2);
                add_vertex(coords, vip1jp1_x, vip1jp1_y, vip1jp1_z, r, g, b, norm2);
                add_vertex(coords, vip1j_x, vip1j_y, vip1j_z, r, g, b, norm2);

            }
        }
    }
};

class Torus {
    double x(float c, float a, float phi, float theta) {
        return (c+a*cos(theta))*cos(phi);
    }

    double y(float c, float a, float phi, float theta) {
        return (c+a*cos(theta))*sin(phi);
    }

    double z(float c, float a, float phi, float theta) {
        return a*sin(theta);
    }

public:
    std::vector<float> coords;
    Torus(unsigned int n, float c, float a, float r, float g, float b) {

        double step_size = 2*M_PI / n;
        double c_x=0;
        double c_y=0;
        double h = .5;
        float radius = .5;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                double phi_i = i*step_size;
                double phi_ip1 = ((i+1)%n)*step_size;
                double theta_j = j*step_size;
                double theta_jp1 = ((j+1)%n)*step_size;

                // vertex i,j
                double vij_x = x(c, a, phi_i, theta_j);
                double vij_y = y(c, a, phi_i, theta_j);
                double vij_z = z(c, a, phi_i, theta_j);

                // vertex i+1,j
                double vip1j_x = x(c, a, phi_ip1, theta_j);
                double vip1j_y = y(c, a, phi_ip1, theta_j);
                double vip1j_z = z(c, a, phi_ip1, theta_j);

                // vertex i,j+1
                double vijp1_x = x(c, a, phi_i, theta_jp1);
                double vijp1_y = y(c, a, phi_i, theta_jp1);
                double vijp1_z = z(c, a, phi_i, theta_jp1);

                // vertex i+1,j+1
                double vip1jp1_x = x(c, a, phi_ip1, theta_jp1);
                double vip1jp1_y = y(c, a, phi_ip1, theta_jp1);
                double vip1jp1_z = z(c, a, phi_ip1, theta_jp1);

                // add triangle
                Vector norm1 = calcFlatNormal(Vector(vij_x,vij_y,vij_z), Vector(vijp1_x,vijp1_y,vijp1_z), Vector(vip1j_x,vip1j_y,vip1j_z));
                add_vertex(coords, vij_x, vij_y, vij_z, r, g, b, norm1);
                add_vertex(coords, vip1j_x, vip1j_y, vip1j_z, r, g, b, norm1);
                add_vertex(coords, vijp1_x, vijp1_y, vijp1_z, r, g, b, norm1);

                // add triangle
                Vector norm2 = calcFlatNormal(Vector(vijp1_x,vijp1_y,vijp1_z), Vector(vip1jp1_x,vip1jp1_y,vip1jp1_z), Vector(vip1j_x,vip1j_y,vip1j_z));
                add_vertex(coords, vijp1_x, vijp1_y, vijp1_z, r, g, b, norm2);
                add_vertex(coords, vip1jp1_x, vip1jp1_y, vip1jp1_z, r, g, b, norm2);
                add_vertex(coords, vip1j_x, vip1j_y, vip1j_z, r, g, b, norm2);
            }
        }
    }

};

#endif
