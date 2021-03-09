#include <cld_light.h>
using namespace coolender;
using namespace glm;
Light::Light():
position(0.0f, 10.0f, 10.0f),
color(1.0f, 1.0f, 1.0f, 1.0f), 
lookAt(0.0f, -1.0f, -0.0f)//光源聚焦位置
{}

Light::Light(vec3 position, vec4 color, vec3 lookAt):
position(position),
color(color),
lookAt(lookAt)
{}