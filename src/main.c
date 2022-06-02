#include "main.h"


static const struct
{
    float x, y, z;
    float r, g, b;
} vertices[3] =
{
    {
        -0.5f, -0.5f, 0.f,
        1.f, 0.f, 0.f
    },
    {
        0.f, 0.5f, 0.f,
        0.f, 0.f, 1.f
    },
    {
        0.5f, -0.5f, 0.f,
        0.f, 1.f, 0.f
    }
};
 
// static const char*  vertex_shader_text =
// "#version 110\n"
// "uniform mat4 MVP;\n"
// "attribute vec3 vCol;\n"
// "attribute vec2 vPos;\n"
// "varying vec3 color;\n"
// "void main()\n"
// "{\n"
// "    gl_Position = MVP * vec4(vPos, 0.f, 1.f);\n"
// "    color = vCol;\n"
// "}\n";

// static const char*  fragment_shader_text =
// "#version 110\n"
// "varying vec3 color;\n"
// "void main()\n"
// "{\n"
// "    gl_FragColor = vec4(color, 1.f);\n"
// "}\n";

static const char*  vertex_shader_text =
"#version 150 core\n"
"in vec2 position;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(position, 0.f, 1.f);\n"
"}\n";

static const char*  fragment_shader_text =
"#version 150 core\n"
"out vec4 outColor;\n"
"void main()\n"
"{\n"
"    outColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
"}\n";

int         gl_create_window(GLFWwindow* *window, const char *title, bool fullscreen)
{
    GLFWmonitor         *monitor;
    const GLFWvidmode   *mode;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    if (fullscreen)
    {
        monitor = glfwGetPrimaryMonitor();
        mode = glfwGetVideoMode(monitor);
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
 
        *window = glfwCreateWindow(mode->width, mode->height, title, monitor, NULL);
    }
    else
        *window = glfwCreateWindow(_WIDTH, _HEIGHT, title, NULL, NULL);
    if (!*window)
    {
        glfwTerminate();
        return (-1);
    }
    glfwMakeContextCurrent(*window);
    gladLoadGL();
    glfwSwapInterval(1);
    return(0);
}

int         window_open(t_env *env)
{
    if (glfwWindowShouldClose(env->window))
        return (-1);

    gl_fps(env, true);

    float   ratio;
    int     width, height;
    mat4x4  m, p, mvp;
 
    glfwGetFramebufferSize(env->window, &width, &height);
    ratio = width / (float)height;
 
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
 
    // mat4x4_identity(m);
    // mat4x4_rotate_Z(m, m, (float)glfwGetTime());
    // mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    // mat4x4_mul(mvp, p, m);
 
    // glUseProgram(program);
    // glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *)mvp);
    glDrawArrays(GL_TRIANGLES, 0, 3);
 
    glfwSwapBuffers(env->window);
    glfwPollEvents();
    return (0);
}

void        gl_init_callback(GLFWwindow* window)
{
    glfwSetKeyCallback(window, key_callback);
    // glfwSetCursorPosCallback(window, cursor_position_callback);
    // glfwSetWindowMaximizeCallback(window, window_maximize_callback);
    // glfwSetWindowFocusCallback(window, window_focus_callback);
    // glfwSetScrollCallback(window, scroll_callback);
}

void        gl_buffer(t_env *env)
{
    glGenBuffers(1, &env->vbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, env->vbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

int         scop(t_env *env)
{
    GLuint      vertex_shader, fragment_shader, program;
    GLint       mvp_location, vpos_location, vcol_location;

    glfwSetErrorCallback(error_callback);
 
    if (!glfwInit() || gl_create_window(&env->window, "scop", false) < 0)
        return (-1);

    gl_init_callback(env->window);

    // NOTE: OpenGL error checks have been omitted for brevity

    gl_buffer(env);
 
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);
 
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);
 
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(program);
    glUseProgram(program);
 
    // mvp_location = glGetUniformLocation(program, "MVP");
    // vpos_location = glGetAttribLocation(program, "vPos");
    // vcol_location = glGetAttribLocation(program, "vCol");
 
    // glEnableVertexAttribArray(vpos_location);
    // glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
    //     sizeof(vertices[0]), (void *)0);
    // glEnableVertexAttribArray(vcol_location);
    // glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
    //     sizeof(vertices[0]), (void *)(sizeof(vertices[0]) * 2));

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
    //     sizeof(float) * 3, (void *)0);
    // glEnableVertexAttribArray(0);

    env->time = glfwGetTime();
    while (window_open(env) > -1)
        ;
 
    glfwDestroyWindow(env->window);
    glfwTerminate();
    return (0);
}
 
int         main(void)
{
    t_env   env;

    ft_memset(&env, 0, sizeof(t_env));
    exit(scop(&env) < 0 ? EXIT_FAILURE : EXIT_SUCCESS);
}
 

