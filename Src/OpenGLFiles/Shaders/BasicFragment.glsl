#version 330 core

// Interpolated values from the vertex shaders
in vec4 fragmentColor; //vertexColor
// Interpolated values from the vertex shaders
in vec2 UV;

out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D textureSampler;
uniform int dominoColorID;

void main() //glsl frag
{
    // Output color = color of the texture at the specified UV
    vec3 texColor = texture(textureSampler, UV).rgb;

    if(length(texColor) < 0.1)
    {
        if(dominoColorID == 1)
        {
            texColor += vec3(1.0,0.1,0.3);
        }
        else if(dominoColorID == 2)
        {
            texColor += vec3(0.0,0.55,1.0);
        }
    } 
    color = vec4(texColor, 1.0); //rgb deve ignorar o alfa(eu acho)
}