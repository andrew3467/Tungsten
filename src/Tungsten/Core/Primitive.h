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



        static std::shared_ptr<Mesh> Quad() {return mQuadMesh;}
        static std::shared_ptr<Mesh> Cube() {return mCubeMesh;}


    private:
        static std::shared_ptr<Mesh> mQuadMesh;
        static std::shared_ptr<Mesh> mCubeMesh;
    };
}
