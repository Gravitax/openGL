#include "main.h"


void        gl_textures(t_env *env)
{
    glGenTextures(1, &env->tex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, env->tex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, env->img_w, env->img_h,
        0, GL_RGB, GL_UNSIGNED_BYTE, env->img);

    // // Black/white checkerboard
    // float pixels[] = {
    //     0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
    //     1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
    // };
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);

    // glUniform1i(glGetUniformLocation(env->shader_program, "tex"), 0);
    glGetUniformLocation(env->shader_program, "tex");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}
