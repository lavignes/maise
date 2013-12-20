#version 140

in vec2 fst;
in vec4 light;

out vec4 color;

uniform sampler2D tex;

void main() {
  color = texture(tex, fst) * light;
}
