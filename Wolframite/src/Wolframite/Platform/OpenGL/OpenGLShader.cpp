//
// Created by Andrew Graser on 2/27/2024.
//

#include "OpenGLShader.h"

#include <Glad/glad.h>
#include <fstream>
#include <Wolframite/Core/Log.h>


#define SHADER_VERTEX_PREPROCESSOR "#Vertex"
#define SHADER_FRAGMENT_PREPROCESSOR "#Fragment"
#define SHADER_GEOMETRY_PREPROCESSOR "#Geometry"


namespace Tungsten {

    struct ShaderSource {
        std::string VertexSource;
        std::string FragmentSource;
        std::string GeometrySource;

        void AddLine(int type, const std::string& line){
            switch (type) {
                case TUNGSTEN_VERTEX_SHADER:          VertexSource.append('\n' + line); break;
                case TUNGSTEN_FRAGMENT_SHADER:        FragmentSource.append('\n' + line); break;
                case TUNGSTEN_GEOMETRY_SHADER:        GeometrySource.append('\n' + line); break;
            }
        }
    };

    ShaderSource LoadShaderSource(const std::string& path){
        ShaderSource source;

        int currentShader = TUNGSTEN_VERTEX_SHADER;
        std::ifstream file(path);
        TUNGSTEN_CORE_ASSERT(file.is_open(), "Failed to open file");

        std::string line;
        while(std::getline(file, line)){
            if(line == SHADER_VERTEX_PREPROCESSOR){
                currentShader = TUNGSTEN_VERTEX_SHADER;
                continue;
            } else if(line == SHADER_FRAGMENT_PREPROCESSOR){
                currentShader = TUNGSTEN_FRAGMENT_SHADER;
                continue;
            } else if(line == SHADER_GEOMETRY_PREPROCESSOR){
                currentShader = TUNGSTEN_GEOMETRY_SHADER;
                continue;
            }

            source.AddLine(currentShader, line);
        }
        file.close();


        return source;
    }

    OpenGLShader::OpenGLShader(const std::string &path) {
        auto source = LoadShaderSource(path);

        GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        GLint geometryShader = -1;
        if(!source.GeometrySource.empty()) {
            geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        }

        {
            auto src = source.VertexSource.c_str();
            glShaderSource(vertexShader, 1, &src, 0);

            glCompileShader(vertexShader);
            int success;
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

            if(!success){
                GLint maxLength = 0;
                glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(vertexShader);

                TUNGSTEN_CORE_ASSERT(false, "Vertex shader compilation failure!");
                TUNGSTEN_CORE_ERROR("{0}", infoLog.data());
                return;
            }
        }

        {
            auto src = source.FragmentSource.c_str();
            glShaderSource(fragmentShader, 1, &src, 0);

            glCompileShader(fragmentShader);
            int success;
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

            if(!success){
                GLint maxLength = 0;
                glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(fragmentShader);

                TUNGSTEN_CORE_ASSERT(false, "Fragment shader compilation failure!");
                TUNGSTEN_CORE_ERROR("{0}", infoLog.data());

                return;
            }
        }

        if(geometryShader != -1) {
            auto src = source.GeometrySource.c_str();
            glShaderSource(geometryShader, 1, &src, 0);

            glCompileShader(geometryShader);
            int success;
            glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);

            if(!success){
                GLint maxLength = 0;
                glGetShaderiv(geometryShader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(geometryShader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(geometryShader);

                TUNGSTEN_CORE_ASSERT(false, "Vertex shader compilation failure!");
                TUNGSTEN_CORE_ERROR("{0}", infoLog.data());

                return;
            }
        }

        mRendererID = glCreateProgram();

        glAttachShader(mRendererID, vertexShader);
        glAttachShader(mRendererID, fragmentShader);
        if(geometryShader != -1){
            glAttachShader(mRendererID, geometryShader);
        }

        glLinkProgram(mRendererID);

        GLint success;
        glGetProgramiv(mRendererID, GL_LINK_STATUS, (int *) &success);
        if (success == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(mRendererID, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(mRendererID, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(mRendererID);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            TUNGSTEN_CORE_ERROR("{0}", infoLog.data());
            TUNGSTEN_CORE_ASSERT(false, "Shader link failure!");

            return;
        }

        glDetachShader(mRendererID, vertexShader);
        glDetachShader(mRendererID, fragmentShader);
        if(geometryShader != -1){
            glDetachShader(mRendererID, geometryShader);
        }
    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(mRendererID);
    }

    void OpenGLShader::Bind() {
        glUseProgram(mRendererID);
    }

    void OpenGLShader::Unbind() {
        glUseProgram(0);
    }
}
