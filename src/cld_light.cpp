#include <cld_light.h>
using namespace coolender;
using namespace glm;
Light::Light():
pos(0.0f, 0.0f, 0.0f),
color(0.0f, 0.0f, 0.0f, 0.0f),
intensity(0.3)
{}

Light::Light(vec3 pos, vec4 color, float intensity):
pos(pos),
color(color),
intensity(intensity)
{}