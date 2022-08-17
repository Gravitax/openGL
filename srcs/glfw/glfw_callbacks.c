#include "../../includes/main.h"


void    	cb_error(int error, const char *description)
{
    fprintf(stderr, "Error: (%d): %s\n", error, description);
    scop_exit();
}
 
void    	cb_key(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    printf("key: %d\n", key);
}

static void update_matrices(t_camera *camera)
{
	camera->yaw = camera->yaw > 180 ? -180 : camera->yaw;
	camera->yaw = camera->yaw < -180 ? 180 : camera->yaw;
	camera->pitch = camera->pitch > 90 ? 90 : camera->pitch;
	camera->pitch = camera->pitch < -90 ? -90 : camera->pitch;

    // Rotation XYZ matrix
	mat4_identity(camera->rot_xyz);
	mat4_rotate(camera->rot_xyz, (float)ft_to_radians(camera->pitch), (float)ft_to_radians(camera->yaw), 0);
}

static void mouse_events(t_env *env, float xpos, float ypos)
{
    t_camera    *camera;
    float       xoffset, yoffset, camera_speed;

    camera = &env->camera;
    if (camera->first_mouse)
    {
        camera->mx = xpos;
        camera->my = ypos;
        camera->first_mouse = false;
    }
    xoffset = xpos - camera->mx;
    yoffset = ypos - camera->my;
    camera->mx = xpos;
    camera->my = ypos;

    camera_speed = camera->sensitivity * 0.1f;
    xoffset *= camera_speed;
    yoffset *= camera_speed;
    camera->yaw += xoffset;
    camera->pitch += yoffset;
    printf("yaw   : %f\n", camera->yaw);
    printf("pitch : %f\n", camera->pitch);

    update_matrices(camera);
}

void    	cb_cursor_position(GLFWwindow *window, double xpos, double ypos)
{
    t_env	    *env;

    glfwGetCursorPos(window, &xpos, &ypos);
	env = st_env(NULL, false);
	if (env == NULL)
		return ;
    // mouse_events(env, (float)xpos, (float)ypos);
}

void    	cb_window_maximize(GLFWwindow *window, int maximized)
{
    if (maximized)
    {
        // The window was maximized
        printf("The window was maximized\n");
    }
    else
    {
        // The window was restored
        printf("The window was restored\n");
    }
}

void    	cb_window_focus(GLFWwindow *window, int focused)
{
    if (focused)
    {
        // The window gained input focus
        printf("The window gained input focus\n");
    }
    else
    {
        // The window lost input focus
        printf("The window lost input focus\n");
    }
}

void    	cb_scroll(GLFWwindow *window, double xoffset, double yoffset)
{
    printf("offset_x: %f, offset_y: %f\n", xoffset, yoffset);
}

void		cb_framebuffer_size(GLFWwindow *window, int width, int height)
{
	t_env	*env;

	env = st_env(NULL, false);
	if (env == NULL)
		return ;
    glViewport(0, 0, width, height);
	env->gl.window.w = width;
	env->gl.window.h = height;
    env->camera.ratio = (float)width / (float)height;
    mat4_projection(env->camera.projection, env->camera.fov, env->camera.near, env->camera.far, env->camera.ratio);
}
