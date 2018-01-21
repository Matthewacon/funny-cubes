#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <tgmath.h>
#include "ogl_utils.hpp"

//Resize callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
 glViewport(0, 0, width, height);
}

//Input delegate
void processInput(GLFWwindow* window) {
 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  glfwSetWindowShouldClose(window, true);
}

int main() {
 //Initialize GLFW and window properties
 glfwInit();
 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
 glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
 glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
 //Create GLFW window
 GLFWwindow* window = glfwCreateWindow(800, 600, "\u25A1", NULL, NULL);
 if (window == NULL) {
  std::cerr << "Failed to create GLFW window!" << std::endl;
  glfwTerminate();
  return -1;
 }
 glfwMakeContextCurrent(window);
 //Load GLAD
 if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
  std::cerr << "Failed to initialize GLAD" << std::endl;
  return -1;
 }
 glViewport(0, 0, 800, 600);
 //Set resize callback
 glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

 //Compile and link shaders to a shader program
 unsigned int vertShader, fragShader, shaderProgram;
 customCompileShader(
  GL_VERTEX_SHADER,
  "/PATH/src/shaders/test_shader.vert",
  &vertShader
 );
 customCompileShader(
  GL_FRAGMENT_SHADER,
  "/PATH/src/shaders/test_shader.frag",
  &fragShader
 );
 shaderProgram = glCreateProgram();
 glAttachShader(shaderProgram, vertShader);
 glAttachShader(shaderProgram, fragShader);
 glLinkProgram(shaderProgram);
 //Clean up shader objects
 glDeleteShader(vertShader);
 glDeleteShader(fragShader);

// //Triangle definition
// float vertices[] = {
//  //vertices          //colours
//  -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, //bottom left
//  0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, //bottom right
//  0.0f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f //top
// };
// float texCoords[] = {
//  -0.5f, -0.5f, //bottom left
//  0.5f, 0.5f, //bottom right
//  0.0f, 0.5f //top
// };
 //Square definition
 float square[] = {
  //vertices          //colours
  0.5f, 0.5f, 0.0f,   0.1f, 0.0f, 0.0f,  1.0f, 1.0f, // top right
  0.5f, -0.5f, 0.0f,  0.0f, 0.1f, 0.0f,  1.0f, 0.0f, // bottom right
  -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.1f,  0.0f, 0.0f,// bottom left
  -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f// top left
 };
 //Square indexed rendering definitions
 unsigned int indices[] = {  // note that we start from 0!
  0, 1, 3,  // first Triangle
  1, 2, 3   // second Triangle
 };
 //Generate, bind and populate vertex buffer object
 unsigned int VBO, VAO, EBO;
 glGenVertexArrays(1, &VAO);
 glGenBuffers(1, &VBO);
 glGenBuffers(1, &EBO);
 glBindVertexArray(VAO);

 glBindBuffer(GL_ARRAY_BUFFER, VBO);
 glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);

 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
 glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

 //Configure VBO layout for vector data
 //layout #, vector size, data type, should normalize (0to1), stride, offset from start
 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
 glEnableVertexAttribArray(0);

 //Configure VBO layout for colour data
 glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
 glEnableVertexAttribArray(1);

 //Configure VBO layout for texture data
 glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
 glEnableVertexAttribArray(2);

 //Unbind the array buffer since there won't be any operations performed on it anymore
 glBindBuffer(GL_ARRAY_BUFFER, 0);
 //Unbind the vertex array buffer to avoid confusion and accidental writes
 glBindVertexArray(0);

// //set polygon rendering mode
// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
// int vertexNewColourLocation = glGetUniformLocation(shaderProgram, "newColour");
// double updateTime = 0;
 unsigned int texture = load2DTexture("/PATH/resources/thonk.png");
 //Activate shader before assigning uniforms
 glUseProgram(shaderProgram);
 GLint theTexture = glGetUniformLocation(shaderProgram, "newTexture");
 glUniform1i(theTexture, 0);
 //Draw loop
 while(!glfwWindowShouldClose(window)) {
//  updateTime = glfwGetTime();
  //Process input
  processInput(window);
  //Clear screen with RGBA colour
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  //Acid trip
//  glClearColor(
//   (cos(updateTime+270)/2.0f)+0.5f,
//   (sin(updateTime)/2.0f)+0.5f,
//   (sin(updateTime+90)/2.0f)+0.5f,
//   1.0f
//  );
  glClear(GL_COLOR_BUFFER_BIT);
  //Run shader program
  glUseProgram(shaderProgram);
  //Update uniform value in shaderProgram
//  glUniform4f(
//   vertexNewColourLocation,
//   (cos(updateTime) / 2.0f) + 0.5f,
//   (sin(updateTime) / 2.0f) + 0.5f,
//   (sin(updateTime + 180) / 2.0f) + 0.5f,
//   1.0f
//  );
  //Bind texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  //Bind VAO
  glBindVertexArray(VAO);
//  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  //Unbind VAO (Not necessary at this point)
  //glBindVertexArray(0);
  //Swap front buffer into back buffer
  glfwSwapBuffers(window);
  //Update glfw events
  glfwPollEvents();
 }
 //Clean up
 glDeleteVertexArrays(1, &VAO);
 glDeleteBuffers(1, &VBO);
 glDeleteBuffers(1, &EBO);

 glfwTerminate();
 return 0;
}
