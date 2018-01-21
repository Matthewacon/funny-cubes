#version 330 core
out vec4 FragColor;

// in vec4 vertexColour;
in vec2 texCoord;

uniform sampler2D newTexture;

void main() {
 // FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
 FragColor = texture(newTexture, texCoord);
 // FragColor = vec4(texCoord, texCoord);
}