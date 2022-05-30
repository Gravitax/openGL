#include "main.h"

# define _WIDTH 640
# define _HEIGHT 480


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

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: (%d): %s\n", error, description);
}
 
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    else if (key != GLFW_KEY_ESCAPE)
        printf("key: %d\n", key);
}
 
int         main(void)
{
    GLFWwindow* window;
    GLuint      vertex_buffer;
    GLuint      vertex_shader, fragment_shader, program;
    GLint       mvp_location, vpos_location, vcol_location;
 
    glfwSetErrorCallback(error_callback);
 
    if (!glfwInit())
        exit(EXIT_FAILURE);
 
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
 
    window = glfwCreateWindow(_WIDTH, _HEIGHT, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
 
    glfwSetKeyCallback(window, key_callback);
 
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);
 
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
 
    while (!glfwWindowShouldClose(window))
    {
        // float   ratio;
        int     width, height;
        // mat4x4  m, p, mvp;
 
        glfwGetFramebufferSize(window, &width, &height);
        // ratio = width / (float)height;
 
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
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
 

