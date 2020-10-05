#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
// Notice that the "2" here equals the "1" in glVertexAttribPointer
layout(location = 1) in vec2 vertexUV;
  
// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform float Time;

// Output data ; will be interpolated for each fragment.
out vec4 fragmentColor;
out vec2 UV;
  
void main()
{
    // Output position of the vertex, in clip space : MVP * position
    //ertexPosition_modelspace.x = 1.0;

    vec3 newPosition = vertexPosition_modelspace;

    //newPosition.x += sin(Time); 

    gl_Position =  MVP * vec4(newPosition,1);
    UV = vertexUV;
}