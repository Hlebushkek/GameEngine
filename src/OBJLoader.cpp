#include "../include/OBJLoader.hpp"
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/ext.hpp>
#include <glad/glad.h>

using namespace std;
using namespace glm;

namespace Engine
{
vector<Vertex> OBJClass::loadOBJ(const char* file_name)
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
          cout << "Can't open file " << file_name << endl;
          // throw "ERROR::OBKLOADER::Could not open a file.";
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
          else if(prefix == "f")
          {
               int counter = 0;
               while(ss >> temp_glint)
               {
                    //Pushing indicies into correnct arrays
                    if (counter == 0)
                         vertex_positions_incdicies.push_back(temp_glint);
                    else if (counter == 1)
                         vertex_texcoords_incdicies.push_back(temp_glint);
                    else if (counter == 2)
                         vertex_normals_incdicies.push_back(temp_glint);

                    //Handling characters
                    if (ss.peek() == '/')
                    {
                         ++counter;
                         ss.ignore(1, '/');
                    }
                    else if (ss.peek() == ' ')
                    {
                         ++counter;
                         ss.ignore(1, ' ');
                    }

                    // Reset the counter
                    if (counter > 2)
                         counter = 0;
               }
          }
          else
          {
               //Unknown case
          }

          //Build final vertex array (mesh)
          verticies.resize(vertex_positions_incdicies.size(), Vertex());
           
          //Load in all indicies 
          for (size_t i = 0; i < verticies.size(); ++i )
          {
               verticies[i].position = vertex_positions[vertex_positions_incdicies[i] - 1];
               verticies[i].texcoord = vertex_texcoords[vertex_texcoords_incdicies[i] - 1];
               verticies[i].normal = vertex_normals[vertex_normals_incdicies[i] - 1];
               verticies[i].color = vec4(0.f, 1.f, 0.f, 1.f);
          }
     
          //DEBUG
          // cout << "Nr of vertices:" << verticies.size() << "\n";
     }

     cout << "vertices " << verticies.size() << endl;
     cout << "vertex_positions_incdicies " << vertex_positions_incdicies.size() << endl;
     cout << "vertex_texcoords_incdicies" << vertex_texcoords_incdicies.size() << endl;
     cout << "vertex_normals_incdicies" << vertex_normals_incdicies.size() << endl;

     cout << "vertex_positions " << vertex_positions.size() << endl;
     cout << "vertex_texcoords " << vertex_texcoords.size() << endl;
     cout << "vertex_normals " << vertex_normals.size() << endl;

     //Loaded successful
     cout << "OBJ file is loaded!" << "\n";
     return verticies;
}
}