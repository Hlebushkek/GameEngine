#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "Core.hpp"
#include "Vertex.hpp"

namespace Engine
{
     class ENGINE_API OBJClass
     {
     public:
          static std::vector<Vertex> loadOBJ(const std::string& fileName);
     };
}
