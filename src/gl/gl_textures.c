#include "main.h"


void        gl_textures(t_env *env)
{
    glGenTextures(1, &env->tex);
    glBindTexture(GL_TEXTURE_2D, env->tex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, env->img_w, env->img_h,
        0, GL_RGB, GL_UNSIGNED_BYTE, env->img);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
