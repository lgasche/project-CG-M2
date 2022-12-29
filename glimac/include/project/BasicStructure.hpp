#pragma once

#include <glimac/Program.hpp> 

using namespace glimac;

struct BasicProgram {
    Program mProgram;
    // Gestion position et texture
    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;
    // Gestion lumière
    GLint uKd;
    GLint uKs;
    GLint uShininess;
    GLint uLightPos_vs;
    GLint uLightIntensity;

    BasicProgram(const FilePath& applicationPath):
        mProgram(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/multiTex3Dlight.fs.glsl")) { //shaders/tex3D.fs.glsl
        uMVPMatrix = glGetUniformLocation(mProgram.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(mProgram.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(mProgram.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(mProgram.getGLId(), "uTexture");

        uKd = glGetUniformLocation(mProgram.getGLId(), "uKd");
        uKs = glGetUniformLocation(mProgram.getGLId(), "uKs");
        uShininess = glGetUniformLocation(mProgram.getGLId(), "uShininess");
        uLightPos_vs = glGetUniformLocation(mProgram.getGLId(), "uLightPos_vs");
        uLightIntensity = glGetUniformLocation(mProgram.getGLId(), "uLightIntensity");
    }
};