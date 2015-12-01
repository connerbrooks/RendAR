#version 330 core
out vec4 color;

uniform vec3 objectColor;

void main()
{
  color = vec4(objectColor, 1.0f);
}
