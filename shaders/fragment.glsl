#version 330 core 
out vec4 FragColor; 
in vec4 vertexPos;

void main() {
    FragColor = vec4(1.0f / (1.0f - vertexPos.x), 1.0f / (vertexPos.y + 1.0f), 0.5f, 1.0f);
}
