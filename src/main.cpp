#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

// clang-format off

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// clang-format on

const int WIDTH = 800;
const int HEIGHT = 600;
const char *TITLE = "Sistema solar";

void error_callback(int error, const char *description) {
  std::cerr << "Error: " << description << std::endl;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int main() {
  glfwSetErrorCallback(error_callback);

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  Shader ourShader("shaders/basic.vert", "shaders/basic.frag");

  // Puntos con coordenadas (x,y,z)
  GLfloat vertices[] = {
      -0.5f,     -0.5f, 0.0f, 0.8f, 0.3f,  0.02f, // Lower Left
      0.5f,      -0.5f, 0.0f, 0.8f, 0.3f,  0.02f, // Lower Right
      0.0f,      0.5f,  0.0f, 1.0f, 0.6f,  0.32f, // Top
      -0.5f / 2, 0.0f,  0.0f, 0.9f, 0.45f, 0.17f, // Inner Left
      0.5f / 2,  0.0f,  0.0f, 0.9f, 0.45f, 0.17f, // Inner right
      0.0f,      -0.5f, 0.0f, 0.8f, 0.3f,  0.02f  // Bottom
  };

  // Orden en el que queremos dibujar los puntos
  GLuint indices[] = {
      0, 5, 3, // Lower Left
      5, 1, 4, // Lower Right
      3, 4, 2  // Top
  };

  VAO VAO_1;

  VAO_1.bind();

  VBO VBO_1(vertices, sizeof(vertices));
  EBO EBO_1(indices, sizeof(indices));

  VAO_1.linkAttrib(VBO_1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void *)0);
  VAO_1.linkAttrib(VBO_1, 1, 3, GL_FLOAT, 6 * sizeof(float),
                   (void *)(3 * sizeof(float)));

  VAO_1.unbind();
  VBO_1.unbind();
  EBO_1.unbind();

  GLuint uniID = glGetUniformLocation(ourShader.ID, "scale");

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    ourShader.use();

    glUniform1f(uniID, 0.5f);

    VAO_1.bind();

    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, (void *)0);

    glfwPollEvents();

    glfwSwapBuffers(window);
  }

  VAO_1.destroy();
  VBO_1.destroy();
  EBO_1.destroy();
  ourShader.destroy();

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
