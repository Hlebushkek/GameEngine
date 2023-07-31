#include <math.h>
#include <vector>
#include <glm/gtc/constants.hpp>
#include "Sphere.hpp"

namespace Engine
{

Sphere::Sphere(float radius, int rings, int sectors) : Primitive()
{
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    int startRing = -rings / 2 + 1;
    int endRing = rings / 2 - 1;

    glm::vec3 souhPolePosition = glm::vec3(0, -radius, 0);
    vertices.push_back({
        souhPolePosition,
        glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
        glm::vec2(0.f, 0.f),
        glm::normalize(souhPolePosition)
    });

    for (int ring = startRing; ring <= endRing; ++ring)
    {
        float phi = glm::pi<float>() * static_cast<float>(ring) / static_cast<float>(rings - 1);
        float cosPhi = std::cos(phi);
        float sinPhi = std::sin(phi);

        for (int sector = 0; sector < sectors; ++sector)
        {
            float theta = glm::two_pi<float>() * static_cast<float>(sector) / static_cast<float>(sectors - 1);
            float cosTheta = std::cos(theta);
            float sinTheta = std::sin(theta);

            glm::vec3 position = glm::vec3(radius * cosTheta * cosPhi,
                                           radius * sinPhi,
                                           radius * sinTheta * cosPhi);
            glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
            glm::vec2 texcoord = glm::vec2(static_cast<float>(sector) / static_cast<float>(sectors - 1),
                                           static_cast<float>(ring) / static_cast<float>(rings - 1));
            glm::vec3 normal = glm::normalize(position);

            vertices.push_back({position, color, texcoord, normal});
        }
    }

    glm::vec3 northePolePosition = glm::vec3(0, radius, 0);
    vertices.push_back({
        northePolePosition,
        glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
        glm::vec2(1.f, 1.f),
        glm::normalize(northePolePosition)
    });

    //South Pole
    for (int sector = 0; sector < sectors; sector++)
    {
        indices.push_back(0);
        indices.push_back(sector);
        indices.push_back(sector + 1);
    }

    //Main Part
    for (int ring = 0; ring < rings - 2; ++ring)
    {
        for (int sector = 0; sector < sectors - 1; sector++)
        {
            int currentRow = ring * sectors;
            int nextRow = (ring + 1) * sectors;

            indices.push_back(currentRow + sector + 1);
            indices.push_back(nextRow + sector + 1);
            indices.push_back(currentRow + sector + 2);

            indices.push_back(nextRow + sector + 1);
            indices.push_back(nextRow + sector + 2);
            indices.push_back(currentRow + sector + 2);
        }
    }

    //North Pole
    for (int sector = 0; sector < sectors; sector++)
    {
        indices.push_back(vertices.size() - 1);
        indices.push_back(vertices.size() - 1 - sector);
        indices.push_back(vertices.size() - 1 - sector - 1);
    }

    this->set(vertices.data(), vertices.size(), indices.data(), indices.size());
}

}