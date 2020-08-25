#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragmentColor; //vertexColor
// Interpolated values from the vertex shaders
in vec2 UV;

out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D textureSampler;

void main() //glsl frag
{
    // Output color = color of the texture at the specified UV
    color = texture(textureSampler, UV).rgb; //rgb deve ignorar o alfa(eu acho)
}