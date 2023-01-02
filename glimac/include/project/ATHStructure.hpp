#pragma once

#include <glimac/Program.hpp> 

using namespace glimac;

struct ATHProgram {
    Program mProgram;
    // Gestion position et texture
    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;
    GLint uTexture2;

    ATHProgram() {}

    void loadATHProgram(const FilePath& applicationPath) {
        mProgram = loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/multiTex3D.fs.glsl");
        uMVPMatrix = glGetUniformLocation(mProgram.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(mProgram.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(mProgram.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(mProgram.getGLId(), "uTexture");
        uTexture2 = glGetUniformLocation(mProgram.getGLId(), "uTexture2");
    }
    /*
    ATHProgram(const FilePath& applicationPath):
        mProgram(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/multiTex3D.fs.glsl")) { 
        uMVPMatrix = glGetUniformLocation(mProgram.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(mProgram.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(mProgram.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(mProgram.getGLId(), "uTexture");
        uTexture2 = glGetUniformLocation(mProgram.getGLId(), "uTexture2");
    }
    */
};