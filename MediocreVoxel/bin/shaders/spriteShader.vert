#version 430

in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

//uniform float pointSize; // radius of the point in opengl
//uniform float textureCoordPointSize;

uniform mat4 P; // projection


void main() {
     //Set the x,y position on the screen
    gl_Position = (P * vec4(vertexPosition.x, vertexPosition.y, 0.0, 1.0));
    //the z position is zero since we are in 2D
    //gl_Position.z = 0.0;
    
    //Indicate that the coordinates are normalized
    //gl_Position.w = 1.0;
    
    fragmentPosition = vertexPosition;
    
    fragmentColor = vertexColor;
    
	fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);

}