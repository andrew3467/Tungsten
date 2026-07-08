//
// Created by Andrew Graser on 7/7/2026.
//


#pragma once

#include "Mesh.h"

namespace Tungsten {
    class Primitive {
    public:
        static void Init();

        static void CreateQuad();
        static void CreateCube();



        static Mesh Quad() {return *mQuadMesh;}
        static Mesh Cube() {return *mCubeMesh;}


    private:
        static std::shared_ptr<Mesh> mQuadMesh;
        static std::shared_ptr<Mesh> mCubeMesh;
    };
}
