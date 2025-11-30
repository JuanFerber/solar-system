#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

#include <Shader.h>

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
  // Registramos un Callback para el reporte de errores
  glfwSetErrorCallback(error_callback);

  // Inicializa GLFW
  glfwInit();

  // Se le indica a GLFW que versión de OpenGL vamos a usar
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // Le indicamos que vamos a usar las funciones modernas del perfil "CORE"
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Creamos un objeto GLFWwindow
  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
  // Verificamos que se haya creado correctamente
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  // Ponemos la ventana ("window") en el contexto actual
  glfwMakeContextCurrent(window);

  // Cargamos GLAD para que configure OpenGL
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // Registramos un Callback que maneje el cambio de tamaño de la ventana
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Bloque de ambito
  {
    // Invocamos al constructor y le pasamos las rutas de los archivos GLSL
    Shader ourShader("shaders/basic.vert", "shaders/basic.frag");

    // 3 puntos con coordenadas (x,y,z) que corresponden a un triángulo
    GLfloat vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                          0.0f,  0.0f,  0.5f, 0.0f};

    // Vertex Buffer Objects (VBO):
    // Se usa para almacenar memoria cruda, en este caso lo usamos para los
    // vértices
    // Vertex Array Object (VAO):
    // Almacena el estado de configuración de los VBO
    GLuint VAO, VBO;

    // Genera un ID único correspondiente tanto al VAO como al VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Le decimos a OpenGL que comience a guardar cualquier configuración o
    // atributo del VBO
    glBindVertexArray(VAO);

    // Se asigna el ID generado anteriormente a un tipo de buffer específico
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Se indica a que buffer, de que tamaño, los datos y como se lo va a tratar
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Le decimos a OpenGL como debe de interpretar los datos del Vertex
    glVertexAttribPointer(
        // Canal por el cual se conecta C++ con el Shader
        0,
        // Tamaño del componente (x,y,z)
        3,
        // Tipo de dato de cada valor
        GL_FLOAT,
        // Sirve para normalizar automáticamente los números entre 0 y 1
        GL_FALSE,
        // Cuantos bytes tiene que saltar para encontrar el siguiente vértice
        3 * sizeof(float),
        // Offset o inicio, indica desde donde empieza a leer el buffer
        (void *)0);

    // Encendemos los atributos especificados
    glEnableVertexAttribArray(0);

    // Una vez ya configurado y almacenado lo relacionado al VBO dejamos de
    // "grabar" el estado
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Loop de la ventana
    while (!glfwWindowShouldClose(window)) {
      // Procesamos los inputs
      processInput(window);

      // Especificamos el color del fondo de la ventana en el back buffer
      glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

      // Limpiamos el back buffer actual y asignamos el color especificado
      glClear(GL_COLOR_BUFFER_BIT);

      // Activamos el Shader Program, lo que se dibuje va a ser procesado por
      // sus Vertex y Fragment Shaders
      ourShader.use();

      // Le decimos a OpenGL que recupere la configuración de los punteros y
      // VBOs que que se guardaron anteriormente
      glBindVertexArray(VAO);

      // Envía una orden a la GPU para que dibuje un triángulo
      glDrawArrays(GL_TRIANGLES, 0, 3);

      // Se encarga de todos los eventos GLFW
      glfwPollEvents();

      // Hacemos un cambio entre el front buffer y el back buffer ("swap")
      glfwSwapBuffers(window);
    }

    // Elimino los objetos que fui creando
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
  }

  // Elimina la ventana antes de cerrar el programa
  glfwDestroyWindow(window);

  // Termina con GLFW antes de cerrar el programa
  glfwTerminate();
  return 0;
}
