#pragma once

#include <vector>
#include <array>

#include "Vertex.hpp"

namespace Engine
{

class Primitive
{
public:
    Primitive() {};
    virtual ~Primitive() {};

    void set(const Vertex* vertices, const unsigned nrOfVertices, const unsigned* indices, const unsigned nrOfIndices);

    inline Vertex* getVertices() { return this->vertices.data(); }
    inline unsigned* getIndices() { return this->indices.data(); }
    inline const unsigned getNumberOfVertices() { return this->vertices.size(); }
    inline const unsigned  getNumberOfIndices() { return this-> indices.size(); }

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};

}