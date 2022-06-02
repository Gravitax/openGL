#include "main.h"


const char  *vertex_shader_text =
"#version 150 core\n"
"in vec2 position;\n"
"in vec3 color;\n"
"out vec3 Color;\n"
"void main()\n"
"{\n"
"    Color = color;\n"
"    gl_Position = vec4(position, 0.f, 1.f);\n"
"}\n";

const char   *fragment_shader_text =
"#version 150 core\n"
"in vec3 Color;\n"
"out vec4 outColor;\n"
"void main()\n"
"{\n"
"    outColor = vec4(Color, 1.f);\n"
"}\n";

const struct
{
    GLfloat x, y, z;
    GLfloat r, g, b;
} vertices[4] =
{
    { // top_left
        -0.5f, 0.5f, 0.f,
        1.f, 0.f, 0.f,
    },
    { // top_right
        0.5f, 0.5f, 0.f,
        0.f, 1.f, 0.f,
    },
    { // bottom_left
        0.5f, -0.5f, 0.f,
        0.f, 0.f, 1.f,
    },
    { // bottom_right
        -0.5f, -0.5f, 0.f,
        1.f, 1.f, 1.f
    }
};

static int  gl_create_window(GLFWwindow* *window, const char *title, bool fullscreen)
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

static void gl_init_callback(GLFWwindow* window)
{
    glfwSetKeyCallback(window, key_callback);
    // glfwSetCursorPosCallback(window, cursor_position_callback);
    // glfwSetWindowMaximizeCallback(window, window_maximize_callback);
    // glfwSetWindowFocusCallback(window, window_focus_callback);
    // glfwSetScrollCallback(window, scroll_callback);
}

static void gl_vobjects(t_env *env)
{
    GLuint  elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Create Vertex Array Object
    glGenVertexArrays(1, &env->vao);
    glBindVertexArray(env->vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &env->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, env->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create an Elements Buffer Object
    glGenBuffers(1, &env->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
}

static void gl_shaders(t_env *env)
{
    GLint   position;

    // Create and compile the vertex shader
    env->shader_vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(env->shader_vertex, 1, &vertex_shader_text, NULL);
    glCompileShader(env->shader_vertex);

    // Create and compile the fragment shader
    env->shader_fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(env->shader_fragment, 1, &fragment_shader_text, NULL);
    glCompileShader(env->shader_fragment);

    // Link the vertex and fragment shader into a shader program
    env->shader_program = glCreateProgram();
    glAttachShader(env->shader_program, env->shader_vertex);
    glAttachShader(env->shader_program, env->shader_fragment);
    glBindFragDataLocation(env->shader_program, 0, "outColor");
    glLinkProgram(env->shader_program);
    glUseProgram(env->shader_program);

    // Specify the layout of the vertex data
    position = glGetAttribLocation(env->shader_program, "position");
    glEnableVertexAttribArray(position);
    glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE,
        sizeof(GLfloat) * 6, (void *)0);

    position = glGetAttribLocation(env->shader_program, "color");
    glEnableVertexAttribArray(position);
    glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE,
        sizeof(GLfloat) * 6, (void *)(sizeof(GLfloat) * 3));
}

int         gl_init(t_env *env)
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit() || gl_create_window(&env->window, "scop", false) < 0)
        return (-1);
    gl_init_callback(env->window);
    gl_vobjects(env);
    gl_shaders(env);
    return (0);
}
