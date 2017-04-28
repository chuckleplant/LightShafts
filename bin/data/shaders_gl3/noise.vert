#version 150
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec4 color;
in vec4 normal;
in vec2 texcoord;
// this is the end of the default functionality

out vec2 varyingtexcoord;

void main(){    

	//finally set the pos to be that actual position rendered
    varyingtexcoord = texcoord;
	gl_Position = modelViewProjectionMatrix * position;
}
