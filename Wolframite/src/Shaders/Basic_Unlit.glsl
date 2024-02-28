#Vertex
#version 460 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;


uniform mat4 uViewProjection;


out vec3 vPosition;

void main() {
    vPosition = aPosition;
    gl_Position = uViewProjection * vec4(aPosition, 1.0);
}

#Fragment
#version 460 core


in vec3 vPosition;

layout (location = 0) out vec4 FragColor;

uniform vec4 uColor;

void main() {
    FragColor = uColor;
}