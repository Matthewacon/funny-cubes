#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <string.h>
#include "stb_image.h"
#include "glad/glad.h"

int customCompileShader(GLenum shaderType, const char *file, unsigned int *shader) {
 static char compileLog[512];
 FILE *fp = fopen(file, "r");
 if (!fp) {
  std::cerr << "Error opening file '" << file << "'!" << std::endl;
  return -1;
 }
 fseek(fp, 0, SEEK_END);
 const long length = ftell(fp);
 char *data = new char[length+1];
 //add null terminator to end of string
 data[length] = '\0';
 fseek(fp, 0, SEEK_SET);
 fread(data, 1, length, fp);
 *shader = glCreateShader(shaderType);
 if (!*shader) {
  std::cerr << "Error occurred creating shader!" << std::endl;
  return *shader;
 }
 if (*shader == GL_INVALID_ENUM) {
  std::cerr << "Invalid shader type provided!" << std::endl;
  return *shader;
 }
 glShaderSource(*shader, 1, (const GLchar**)&data, NULL);
 glCompileShader(*shader);
 int success;
 glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
 if (!success) {
  glGetShaderInfoLog(*shader, 512, NULL, compileLog);
  std::cerr << "Error compiling shader: '" << file << "'!\n" << compileLog << std::endl;
  memset(&compileLog, 0, sizeof(char)*512);
 }
 return success;
}

unsigned int load2DTexture(const char* file) {
 int width, height, nrChannels;
 unsigned int texture;
 stbi_set_flip_vertically_on_load(1);
 unsigned char *data = stbi_load(file, &width, &height, &nrChannels, 0);
 if (data) {
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  //set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  //set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
 } else {
  std::cerr << "Failed to load texture '" << file << "'!" << std::endl;
  return -1;
 }
 stbi_image_free(data);
 glBindTexture(GL_TEXTURE_2D, 0);
 return texture;
}
