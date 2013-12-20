#version 130

in vec2 fst;

out vec4 color;

uniform sampler2D tex;

void main() {
  color = texture(tex, fst);
}
