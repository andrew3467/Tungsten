//
// Created by Andrew Graser on 7/7/2026.
//

#include <Renderer/Shader.h>
#include <Renderer/Texture.h>
#include "Material.h"

namespace Tungsten {
    Material::Material() {
        Shader = Shader::Get("Basic_Lit");
        Texture = Texture2D::Get("Default");


    }

    void Material::Bind() {
        Shader->Bind();

        Shader->SetFloat3("uColor", Albedo);

        Shader->SetFloat("uShininess", Shininess);
        Shader->SetFloat("uMetallic", Metallic);
        Shader->SetFloat("uRoughness", Roughness);


        Texture->Bind(0);
    }
} // Tungsten