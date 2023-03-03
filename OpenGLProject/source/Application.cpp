#include "Renderer.h"
#include <GLFW/glfw3.h>

#include <iostream>

#include "VertexArray.h"
#include "Buffer.h"
#include "GLProgram.h"


// Callbacks //

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if ((key == GLFW_KEY_SPACE || key == GLFW_KEY_ENTER) && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}


// Unrelated //

void changeColor(float& color, float& increment) {
    if (color >= 1.0f) {
        increment = -0.02f;
    }
    else if (color <= 0.0f) {
        increment = 0.02f;
    }
    color += increment;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    glfwSetErrorCallback(error_callback);


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    glfwSetKeyCallback(window, key_callback);

    {
        float positions[]
        {
            -0.5f, -0.5f,
            -0.5f,  0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f
        };

        unsigned int indices[]
        {
            0, 1, 2,
            0, 2, 3
        };

        
        VertexArray vertexArray;

        BufferLayout layout;
        layout.Push<float>(2, GL_FALSE);

        Buffer vertexBuffer(positions, sizeof(positions), GL_ARRAY_BUFFER);
        vertexArray.AddBufferLayout(vertexBuffer, layout);

        vertexArray.Unbind();
        vertexBuffer.Unbind();


        Buffer indexBuffer(indices, sizeof(indices), GL_ELEMENT_ARRAY_BUFFER);
        indexBuffer.Unbind();

        unsigned int program = GLProgram::CreateProgram("resources/shaders/vertexShader.glsl", "resources/shaders/fragmentShader.glsl");


        float color = 0.0f;
        float increment = 0.02f;


        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            GLCall(glClear(GL_COLOR_BUFFER_BIT));

            vertexArray.Bind();
            indexBuffer.Bind();
            GLCall(glUseProgram(program));


            int u_ColorLocation = glGetUniformLocation(program, "u_Color");
            if (u_ColorLocation == -1) {
                ASSERT(false);
            }
            changeColor(color, increment);

            GLCall(glUniform4f(u_ColorLocation, 1.0f, 0.0f, color, 1.0f));

            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glDeleteProgram(program);
    }

    glfwTerminate();
    return 0;
}