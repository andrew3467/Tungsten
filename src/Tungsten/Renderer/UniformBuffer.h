//
// Created by Andrew Graser on 7/7/2026.
//


#pragma once

namespace Tungsten {
    class UniformBuffer {
    public:
        UniformBuffer(size_t size, uint32_t binding);
        ~UniformBuffer() = default;

        void SetData(const void* data, size_t size, size_t offset = 0);


        void Bind() const;
        void Unbind() const;

    private:
        uint32_t mRendererID;
        uint32_t mBinding;
    };
}
