#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>

class Shader {
public:
  // ID del programa Shader compilado
  GLuint ID;

  // Constructor, lee y compila los Shaders
  Shader(const char *vertexPath, const char *fragmentPath);

  // Activa el Shader
  void use();

  // Destructor
  void destroy();

private:
  // Función para detectar errores de compilación
  void checkCompileErrors(GLuint shader, std::string type);
};

#endif
