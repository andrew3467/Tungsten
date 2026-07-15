//
// Created by Andrew Graser on 7/7/2026.
//

#include <glm/ext/scalar_constants.hpp>
#include <cmath>
#include <glm/geometric.hpp>
#include "Primitive.h"


namespace Tungsten {
    std::shared_ptr<Mesh> Primitive::mQuadMesh = nullptr;
    std::shared_ptr<Mesh> Primitive::mCubeMesh = nullptr;

    void Primitive::Init() {
        CreateQuad();
        CreateCube();
    }

    void Primitive::CreateQuad() {
        std::vector<Vertex> vertices = {
                {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},   // A
                {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},   // B
                {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},   // C
                {{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},   // D
        };

        std::vector<uint32_t> indices = {
                0, 1, 2,     //A, B, C
                2, 3, 0,     //C, D, A
        };

        mQuadMesh = Mesh::Create();

        mQuadMesh->SetVertices(vertices);
        mQuadMesh->SetIndices(indices);
    }

    void Primitive::CreateCube() {
        std::vector<Vertex> vertices = {
                {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},  // A 0
                {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},  // B 1
                {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},  // C 2
                {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},  // D 3
                {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},  // E 4
                {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},   // F 5
                {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},   // G 6
                {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},   // H 7

                {{-0.5f, 0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},  // D 8
                {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},  // A 9
                {{-0.5f, -0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},  // E 10
                {{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},  // H 11
                {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},   // B 12
                {{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},   // C 13
                {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, { 1.0f, 1.0f }},   // G 14
                {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},   // F 15

                {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},  // A 16
                {{0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},   // B 17
                {{0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},   // F 18
                {{-0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},  // E 19
                {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},  // C 20
                {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},  // D 21
                {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},  // H 22
                {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},  // G 23
        };
        std::vector<uint32_t> indices = {

                // front and back
                0, 3, 2,
                2, 1, 0,
                4, 5, 6,
                6, 7 ,4,
                // left and right
                11, 8, 9,
                9, 10, 11,
                12, 13, 14,
                14, 15, 12,
                // bottom and top
                16, 17, 18,
                18, 19, 16,
                20, 21, 22,
                22, 23, 20
        };



        mCubeMesh = Mesh::Create();

        mCubeMesh->SetVertices(vertices);
        mCubeMesh->SetIndices(indices);
    }

    //https://www.songho.ca/opengl/gl_sphere.html
    std::shared_ptr<Mesh> Primitive::Sphere(int stacks, int sectors) {
        std::vector<Vertex> vertices;
        std::vector<uint32_t > indices;

        float sectorStep = 2 * glm::pi<float>() / sectors;
        float stackStep =  glm::pi<float>() / stacks;
        float sectorAngle, stackAngle;

        //Prefer unit sphere, scaling up done on shader level
        const float radius = 1.0f;

        float x, y, z, xy;

        for (int i = 0; i <= stacks; ++i) {
            stackAngle = glm::pi<float>() / 2.0f - i * stackStep;
            xy = radius * cosf(stackAngle);
            z = radius * sinf(stackAngle);

            for (int j = 0; j <= sectors; ++j) {
                sectorAngle = j * sectorStep;

                x = xy * cosf(sectorAngle);
                y = xy * sinf(sectorAngle);
                glm::vec3 position(x,y,z);
                glm::vec3 normal = glm::normalize(glm::vec3(x,y,z));

                glm::vec2 texCoord((float)j / sectors, (float)i / stacks);

                vertices.emplace_back(position, normal, texCoord);
            }
        }

        //Indices
        int k1, k2;
        for(int i = 0; i < stacks; ++i)
        {
            k1 = i * (sectors + 1);     // beginning of current stack
            k2 = k1 + sectors + 1;      // beginning of next stack

            for(int j = 0; j < sectors; ++j, ++k1, ++k2)
            {
                if(i != 0)
                {
                    indices.push_back(k1);
                    indices.push_back(k2);
                    indices.push_back(k1 + 1);
                }

                if(i != (stacks-1))
                {
                    indices.push_back(k1 + 1);
                    indices.push_back(k2);
                    indices.push_back(k2 + 1);
                }


            }
        }


        auto mesh = Mesh::Create();

        mesh->SetVertices(vertices);
        mesh->SetIndices(indices);

        return mesh;
    }
}