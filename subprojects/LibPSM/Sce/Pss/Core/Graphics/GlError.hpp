#ifndef LIB_PSS_GLERROR_H
#define LIB_PSS_GLERROR_H 1
#include <glad/glad.h>

static const char* glErrorToString(GLenum err) {
    switch (err) {
        case GL_NO_ERROR: return "GL_NO_ERROR";
        case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
        case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
        default: return "UNKNOWN_GL_ERROR";
    }
}

#define GL_CALL(expr) \
    do { \
        expr; \
        GLenum err; \
        while ((err = glGetError()) != GL_NO_ERROR) { \
            std::cerr << "[OpenGL] Error after `" #expr "` at " \
                      << __FILE__ << ":" << __LINE__ << ": " \
                      << glErrorToString(err) << " (0x" << std::hex << err << std::dec << ")" \
                      << std::endl; \
        } \
    } while (0)

#endif