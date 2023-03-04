#include "Renderer.h"
#include <GLFW/glfw3.h>

#include <iostream>

#include "VertexArray.h"
#include "Buffer.h"
#include "Shader.h"
#include "Texture.h"


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
            -0.5f, -0.5f, 0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f, 1.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, 1.0f, 1.0f
        };

        unsigned int indices[]
        {
            0, 1, 2,
            1, 2, 3
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray vertexArray;

        BufferLayout layout;
        layout.Push<float>(2, GL_FALSE);
        layout.Push<float>(2, GL_FALSE);

        Buffer vertexBuffer(positions, sizeof(positions), GL_ARRAY_BUFFER);
        vertexArray.AddBufferLayout(vertexBuffer, layout);

        vertexArray.Unbind();
        vertexBuffer.Unbind();


        Buffer indexBuffer(indices, sizeof(indices), GL_ELEMENT_ARRAY_BUFFER);
        indexBuffer.Unbind();

        Shader shader("resources/shaders/vertexShader.glsl", "resources/shaders/fragmentShader.glsl");

        float color = 0.0f;
        float increment = 0.02f;

        Texture texture("resources/textures/Image.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        Renderer renderer;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            renderer.Draw(vertexArray, indexBuffer, shader);

            shader.SetUniform4f("u_Color", 1.0f, 0.0f, color, 1.0f);
            changeColor(color, increment);


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}