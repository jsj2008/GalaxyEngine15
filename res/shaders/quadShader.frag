#version 430

uniform sampler2D tex;
varying vec2 outUV;

void main(){    

	vec4 color = texture(tex, outUV);
	//color.a = color.a;
    gl_FragColor = color;
}