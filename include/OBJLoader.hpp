
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

//Own Libs
#include"Vertex.hpp"

namespace Engine
{
class OBJClass
{
public:
     static std::vector<Vertex> loadOBJ(const char* file_name);
};
}