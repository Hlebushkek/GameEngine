#include "Cube.hpp"

namespace Engine
{
    Cube::Cube(int excludedFaces) : Primitive()
    {
        std::array<Vertex, 24> vertices =
        {
            //Cube Front
            Vertex{ {-0.5f, 0.5f, 0.5f}, { 1.0f, 0.0f, 0.0f, 1.0f}, { 0.5f,0.66f}, { 0.0f, 0.0f, 1.0f} },
            Vertex{ {-0.5f,-0.5f, 0.5f}, { 0.0f, 1.0f, 0.0f, 1.0f}, { 0.5f,0.34f}, { 0.0f, 0.0f, 1.0f} },
            Vertex{ { 0.5f,-0.5f, 0.5f}, { 0.0f, 0.0f, 1.0f, 1.0f}, {0.75f,0.34f}, { 0.0f, 0.0f, 1.0f} },
            Vertex{ { 0.5f, 0.5f, 0.5f}, { 1.0f, 1.0f, 0.0f, 1.0f}, {0.75f,0.66f}, { 0.0f, 0.0f, 1.0f} },
            //Cube Right
            Vertex{ { 0.5f, 0.5f, 0.5f}, { 1.0f, 0.0f, 0.0f, 1.0f}, {0.25f,0.66f}, { 1.0f, 0.0f, 0.0f} },
            Vertex{ { 0.5f,-0.5f, 0.5f}, { 0.0f, 1.0f, 0.0f, 1.0f}, {0.25f,0.34f}, { 1.0f, 0.0f, 0.0f} },
            Vertex{ { 0.5f,-0.5f,-0.5f}, { 0.0f, 0.0f, 1.0f, 1.0f}, { 0.5f,0.34f}, { 1.0f, 0.0f, 0.0f} },
            Vertex{ { 0.5f, 0.5f,-0.5f}, { 1.0f, 1.0f, 0.0f, 1.0f}, { 0.5f,0.66f}, { 1.0f, 0.0f, 0.0f} },
            //Cube Back
            Vertex{ { 0.5f, 0.5f,-0.5f}, { 1.0f, 0.0f, 0.0f, 1.0f}, { 0.0f,0.66f}, { 0.0f, 0.0f,-1.0f} },
            Vertex{ { 0.5f,-0.5f,-0.5f}, { 0.0f, 1.0f, 0.0f, 1.0f}, { 0.0f,0.34f}, { 0.0f, 0.0f,-1.0f} },
            Vertex{ {-0.5f,-0.5f,-0.5f}, { 0.0f, 0.0f, 1.0f, 1.0f}, {0.25f,0.34f}, { 0.0f, 0.0f,-1.0f} },
            Vertex{ {-0.5f, 0.5f,-0.5f}, { 1.0f, 1.0f, 0.0f, 1.0f}, {0.25f,0.66f}, { 0.0f, 0.0f,-1.0f} },
            //Cube Left
            Vertex{ {-0.5f, 0.5f,-0.5f}, { 1.0f, 0.0f, 0.0f, 1.0f}, {0.75f,0.66f}, {-1.0f, 0.0f, 0.0f} },
            Vertex{ {-0.5f,-0.5f,-0.5f}, { 0.0f, 1.0f, 0.0f, 1.0f}, {0.75f,0.34f}, {-1.0f, 0.0f, 0.0f} },
            Vertex{ {-0.5f,-0.5f, 0.5f}, { 0.0f, 0.0f, 1.0f, 1.0f}, { 1.0f,0.34f}, {-1.0f, 0.0f, 0.0f} },
            Vertex{ {-0.5f, 0.5f, 0.5f}, { 1.0f, 1.0f, 0.0f, 1.0f}, { 1.0f,0.66f}, {-1.0f, 0.0f, 0.0f} },
            //Cube Up
            Vertex{ {-0.5f, 0.5f,-0.5f}, { 1.0f, 0.0f, 0.0f, 1.0f}, { 0.5f, 1.0f}, { 0.0f, 1.0f, 0.0f} },
            Vertex{ {-0.5f, 0.5f, 0.5f}, { 0.0f, 1.0f, 0.0f, 1.0f}, { 0.5f,0.67f}, { 0.0f, 1.0f, 0.0f} },
            Vertex{ { 0.5f, 0.5f, 0.5f}, { 0.0f, 0.0f, 1.0f, 1.0f}, {0.75f,0.67f}, { 0.0f, 1.0f, 0.0f} },
            Vertex{ { 0.5f, 0.5f,-0.5f}, { 1.0f, 1.0f, 0.0f, 1.0f}, {0.75f, 1.0f}, { 0.0f, 1.0f, 0.0f} },
            //Cube Down
            Vertex{ {-0.5f,-0.5f,-0.5f}, { 1.0f, 0.0f, 0.0f, 1.0f}, { 0.5f,0.33f}, { 0.0f,-1.0f, 0.0f} },
            Vertex{ {-0.5f,-0.5f, 0.5f}, { 0.0f, 1.0f, 0.0f, 1.0f}, { 0.5f, 0.0f}, { 0.0f,-1.0f, 0.0f} },
            Vertex{ { 0.5f,-0.5f, 0.5f}, { 0.0f, 0.0f, 1.0f, 1.0f}, {0.75f, 0.0f}, { 0.0f,-1.0f, 0.0f} },
            Vertex{ { 0.5f,-0.5f,-0.5f}, { 1.0f, 1.0f, 0.0f, 1.0f}, {0.75f,0.33f}, { 0.0f,-1.0f, 0.0f} }
        };
        unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

        std::vector<unsigned> front =
        {
            0, 1, 2,
            0, 2, 3
        };
        std::vector<unsigned> right =
        {
            4, 5, 6,
            4, 6, 7
        };
        std::vector<unsigned> back =
        {
            8, 9,10,
            8,10,11,
        };
        std::vector<unsigned> left =
        {
            12,13,14,
            12,14,15,
        };
        std::vector<unsigned> up =
        {
            16,17,18,
            16,18,19,
        };
        std::vector<unsigned> down =
        {
            23,22,20,
            22,21,20
        };

        std::vector<unsigned> indices;

        if (!(excludedFaces & FORWARD)) indices.insert(indices.end(), front.begin(), front.end());
        if (!(excludedFaces & RIGHT))   indices.insert(indices.end(), right.begin(), right.end());
        if (!(excludedFaces & BACKWARD))indices.insert(indices.end(), back.begin(), back.end());
        if (!(excludedFaces & LEFT))    indices.insert(indices.end(), left.begin(), left.end());
        if (!(excludedFaces & UP))      indices.insert(indices.end(), up.begin(), up.end());
        if (!(excludedFaces & DOWN))    indices.insert(indices.end(), down.begin(), down.end());

        unsigned int nrOfIndices = indices.size();

        if (excludedFaces != DIRECTION_ALL)
            this->set(vertices.data(), nrOfVertices, indices.data(), nrOfIndices);
    }
}