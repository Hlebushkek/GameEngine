#pragma once

#include <glm/glm.hpp>

typedef struct FrameData
{
    glm::mat4 view_matrix;
    glm::mat4 projection_matrix;
    glm::vec3 camera_position;
    unsigned int framebuffer_width;
    unsigned int framebuffer_height;
} FrameData;

typedef struct MeshData
{
    glm::mat4 model_matrix;
    bool is_texture_bound;
} MeshData;

typedef struct Material
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
} Material;