// La declaración de versión corresponde con:
// La versión de OpenGL 3.3 y el perfil CORE
#version 330 core

// Se define el canal por donde pasan los datos y una variable de tipo
// vector de 3 componentes que es de entrada
layout(location = 0) in vec3 aPos;

void main() {
  // variable predefinida y obligatoria que se utiliza para saber donde
  // colocar el punto en pantalla
  gl_Position = vec4(aPos, 1.0);
}
