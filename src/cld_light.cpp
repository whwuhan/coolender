#include <cld_light.h>
using namespace coolender;
using namespace glm;
Light::Light():
position(0.0f, 100.0f, 100.0f),
color(1.0f, 1.0f, 1.0f, 1.0f), //HDR颜色
direction(0.0f, 1.0f, 1.0f)
{}

Light::Light(vec3 position, vec4 color, vec3 direction):
position(position),
color(color),
direction(direction)
{}