#include <cld_light.h>
using namespace coolender;
using namespace glm;
Light::Light():
position(0.0f, 1.0f, 0.0f),
color(1.0f, 1.0f, 1.0f, 1.0f),
direction(1.0f, 1.0f, 0.0f)
{}

Light::Light(vec3 position, vec4 color, vec3 direction):
position(position),
color(color),
direction(direction)
{}