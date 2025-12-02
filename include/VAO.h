#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>

#include "VBO.h"

class VAO {
public:
  // ID del buffer
  GLuint ID;

  // Constructor
  VAO();

  // Funciones de conexión
  void linkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type,
                  GLsizeiptr stride, void *offset);
  void bind();
  void unbind();
  void destroy();
};
#endif
