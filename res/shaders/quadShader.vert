#version 430

attribute vec3 vertex;
attribute vec2 uv;
uniform mat4 mvp;

varying vec2 outUV;

void main(void) {
  gl_Position = mvp*vec4(vertex, 1);
  outUV = uv;
}