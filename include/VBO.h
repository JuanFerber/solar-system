#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

class VBO {
public:
  // ID del buffer
  GLuint ID;

  // Constructor
  VBO(GLfloat *vertices, GLsizeiptr size);

  // Funciones de conexión
  void bind();
  void unbind();
  void destroy();
};
#endif
