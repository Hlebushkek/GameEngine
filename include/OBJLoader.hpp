
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

//GLAD
#include<glad/glad.h>

//Own Libs
#include"Vertex.hpp"

//GLEW
#include<SDL3/SDL.h>

//// GLFW
// #include <GLFW/glfw3.h>

//OpenGL Math libs
#include<glm/glm.hpp>
// #include<vec3.hpp>
// #include<vec4.hpp>
// #include<mat4x4.hpp>
// #include<gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

namespace Engine
{
static std::vector<Vertex> loadOBJ(const char* file_name)
{
    //Vertex portions
    vector<fvec3> vertex_positions;
    vector<fvec2> vertex_texcoords;
    vector<fvec3> vertex_normals;

    //Face vectors
    vector<GLint> vertex_positions_incdicies;
    vector<GLint> vertex_texcoords_incdicies;
    vector<GLint> vertex_normals_incdicies;

    //Vertex array
    vector<Vertex> verticies;
    
    stringstream ss;
    ifstream in_file(file_name);
    string line = "";
    string prefix = "";
    vec3 temp_vec3;
    vec2 temp_vec2;
    GLint temp_glint = 0;

    //File open erroe check
    if (!in_file.is_open())
    {
        throw "ERROR::OBKLOADER::Could not open a file.";
    }

    //Read one line at a time
    while (getline(in_file, line))
    {
       //Get the prefix of the line
       ss.clear();
       ss.str(line);
       ss >> prefix;

       if(prefix == "#")
       {

       }

       else if(prefix == "o")
       {

       }

       else if(prefix == "s")
       {

       }

       else if (prefix == "use mtl")
       {

       }

       else if(prefix == "v") //Vertex position
       {
            ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z; 
            vertex_positions.push_back(temp_vec3);
       }

       else if(prefix == "vt")
       {
            ss >> temp_vec2.x >> temp_vec2.y;
            vertex_texcoords.push_back(temp_vec2);
       }

       else if(prefix == "vn")
       {
            ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
            vertex_normals.push_back(temp_vec3);
       }
       else if(prefix =="f")
       {

       }

       else
       {

       }
        //DEBUG
        cout << line << "\n";
        cout << "Nr of vertices:" << vertex_positions.size() << "\n";

    }


    //Loaded successful
    return verticies;
}
}