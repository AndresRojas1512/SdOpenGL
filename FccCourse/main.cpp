#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "shaderClass.h"
#include "EBO.h"
#include "VAO.h"
#include "VBO.h"

GLfloat vertices[] =
{
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
};

GLuint indices[] =
{
    0, 3, 5, // Lower left triangle
    3, 2, 4, // Lower right triangle
    5, 4, 1 // Upper triangle
};

int main(void)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
    // Create the window
    GLFWwindow *window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);

    if (!window)
    {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // Use the window. Context - object that holds all the window
    glfwMakeContextCurrent(window);
    gladLoadGL(); // Load the needed configurations for OpenGL
    glViewport(0, 0, 800, 800); // bottom left to top height    

    Shader shaderProgram("default.vert", "default.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices)); // Vertices Buffer Object - is and array of vertices. Serves for passing data between the CPU and the GPU
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkVBO(VBO1, 0);
    VAO1.Unbind();
    VBO1.Unbind();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window); // Make sure that the image get updates each frame
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}