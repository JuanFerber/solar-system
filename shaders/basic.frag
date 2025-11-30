// La declaración de versión corresponde con:
// La versión de OpenGL 3.3 y el perfil CORE
#version 330 core

// Variable de tipo vector de 4 componentes que es de salida
out vec4 FragColor;

void main() {
  // Obligatorio tener una variable de salida
  FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);
}
