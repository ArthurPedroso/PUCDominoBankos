#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>

#ifdef __cplusplus
extern "C"
{
#endif

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

#ifdef __cplusplus
}
#endif
#endif
