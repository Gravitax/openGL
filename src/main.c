#include "main.h"


static const struct
{
    float x, y, z;
    float r, g, b;
} vertices[3] =
{
    {
        -0.5f, -0.5f, 0.0f,
        1.0f, 0.0f, 0.0f
    },
    {
        0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 1.0f
    },
    {
        0.5f, -0.5f, 0.0f,
        0.0f, 1.0f, 0.0f
    }
};
 
static const char*  vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";
 
static const char*  fragment_shader_text =
"#version 110\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";

int         gl_init_window(GLFWwindow* *window)
{
    // TO PUT FULLSCREEN ON WINDOW

    // GLFWmonitor*        monitor = glfwGetPrimaryMonitor();
    // const GLFWvidmode*  mode = glfwGetVideoMode(monitor);
 
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    // glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    // glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    // glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
 
    // *window = glfwCreateWindow(mode->width, mode->height, "Monitor example", monitor, NULL); 

    *window = glfwCreateWindow(_WIDTH, _HEIGHT, "Simple example", NULL, NULL);

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

void        gl_get_fps(double *lastTime, int *nbFrames)
{
    double  currentTime, ms_per_frame;
    int     fps;

    currentTime = glfwGetTime();
    ++(*nbFrames);
    if (currentTime - *lastTime >= 1.0f) // si il y a une diff de plus d'1 seconde
    {
        ms_per_frame = 1000.f / *nbFrames;
        // printf("ms/frame: %f\n", ms_per_frame);
        fps = 1 / ms_per_frame * 1000.f;
        // printf("fps: %d\n", fps);
        *nbFrames = 0;
        ++(*lastTime);
    }
}

int         render_loop(GLFWwindow* window, double *time, int *frames)
{
    if (glfwWindowShouldClose(window))
        return (-1);

    gl_get_fps(time, frames);

    float   ratio;
    int     width, height;
    mat4x4  m, p, mvp;
 
    glfwGetFramebufferSize(window, &width, &height);
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
 
    glfwSwapBuffers(window);
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

int         render()
{
    GLFWwindow* window;
    GLuint      vertex_buffer;
    GLuint      vertex_shader, fragment_shader, program;
    GLint       mvp_location, vpos_location, vcol_location;

    glfwSetErrorCallback(error_callback);
 
    if (!glfwInit() || gl_init_window(&window) < 0)
        return (-1);

    gl_init_callback(window);

    // NOTE: OpenGL error checks have been omitted for brevity
 
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
    // vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    // glCompileShader(vertex_shader);
 
    // fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    // glCompileShader(fragment_shader);
 
    // program = glCreateProgram();
    // glAttachShader(program, vertex_shader);
    // glAttachShader(program, fragment_shader);
    // glLinkProgram(program);
 
    // mvp_location = glGetUniformLocation(program, "MVP");
    // vpos_location = glGetAttribLocation(program, "vPos");
    // vcol_location = glGetAttribLocation(program, "vCol");
 
    // glEnableVertexAttribArray(vpos_location);
    // glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
    //     sizeof(vertices[0]), (void *)0);
    // glEnableVertexAttribArray(vcol_location);
    // glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
    //     sizeof(vertices[0]), (void *)(sizeof(vertices[0]) * 2));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        sizeof(float) * 3, (void *)0);
    glEnableVertexAttribArray(0);
 
    double  time;
    int     frames;

    time = glfwGetTime();
    frames = 0;
    while (render_loop(window, &time, &frames) > -1)
        ;
 
    glfwDestroyWindow(window);
    glfwTerminate();
    return (0);
}
 
int         main(void)
{
    if (render() < 0)
        exit(EXIT_FAILURE);    
    exit(EXIT_SUCCESS);
}
 

