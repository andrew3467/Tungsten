//
// Created by Andrew Graser on 12/7/2024.
//

#include "OrthographicCamera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Engine.h"


namespace Tungsten
{
    OrthographicCamera::OrthographicCamera(const glm::vec3 &pos)
        : mPosition(pos)
    {
        const glm::vec2 windowSize = Engine::Get().GetWindow().GetSize();
        mOrthoMatrix = glm::ortho(0.f, windowSize.x, windowSize.y, 0.f, 0.0f, 100.0f);
    }

    glm::mat4 OrthographicCamera::GetProjection() const
    {
        return mOrthoMatrix * glm::lookAt(mPosition, glm::vec3(0.0f), mUp);
    }
}
