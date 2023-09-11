#include "Rect.hpp"

namespace Engine
{
    Rect::Rect() : Primitive()
    {
        std::array<Vertex, 4> vertices = {
        Vertex{ {-0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.f, 1.f}, { 0.0f,  0.0f, 1.0f} },
        Vertex{ {-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.f, 0.f}, { 0.0f,  0.0f, 1.0f} },
        Vertex{ { 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.f, 0.f}, { 0.0f,  0.0f, 1.0f} },

        Vertex{ { 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f}, {1.f, 1.f}, { 0.0f,  0.0f, 1.0f} }
        };
        unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

        unsigned indices[] =
        {
            0, 1, 2,
            0, 2, 3
        };
        unsigned nrOfIndices = sizeof(indices) / sizeof(unsigned);

        this->set(vertices.data(), nrOfVertices, indices, nrOfIndices);
    }
}