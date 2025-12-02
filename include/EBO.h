#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

class EBO {
public:
  // ID del buffer
  GLuint ID;

  // Constructor
  EBO(GLuint *indices, GLsizeiptr size);

  // Funciones de conexión
  void bind();
  void unbind();
  void destroy();
};
#endif
