#include <light.h>
using namespace coolender;
using namespace glm;
Light::Light():
pos(0.0f, 0.0f, 0.0f),
color(0.0f, 0.0f, 0.0f, 0.0f)
{}

Light::Light(vec3 pos, vec4 color):
pos(pos),
color(color)
{}