//
// Created by Andrew Graser on 11/29/2024.
//


#pragma once

namespace Tungsten
{
    class Texture {
    public:
        Texture() {}
        virtual ~Texture() {}


        void Bind(int loc = 0) const;
        void Unbind() const;


        [[nodiscard]] uint32_t GetWidth() const {return mWidth;}
        [[nodiscard]] uint32_t GetHeight() const {return mHeight;}
        [[nodiscard]] const std::string& GetName() const {return mName;}
        [[nodiscard]] uint32_t GetID() const {return mRendererID;}
        void SetName(const std::string& name) {mName = name;}


    protected:
        uint32_t LoadTextureData(const std::string& path);



    protected:
        std::string mFileLoc;
        uint32_t mRendererID;

        int mWidth, mHeight, mChannels;

        uint32_t mInternalFormat, mDataFormat;

        std::string mName;
    };

    class Texture2D : public Texture {
    public:
        static std::shared_ptr<Texture2D> Create(const std::string& path) {return std::make_shared<Texture2D>(path);}
        static std::shared_ptr<Texture2D> Create(int w, int h, const std::string& name);
        static void Init();
        static std::shared_ptr<Texture2D> Get(const std::string& name);
        static std::unordered_map<std::string, std::shared_ptr<Texture2D>> GetTextures();

    public:
        Texture2D(int width, int height, const std::string& name);
        Texture2D(const std::string& path);
        ~Texture2D();

        void SetData(void* data, uint32_t size) const;
    };
}
