#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

// note windows are normalized, so values must be between 1 and -1 on all axis
GLfloat SIMPLE_TRIANGLE_EQU[] = {
    -0.5f,-0.5f * float(sqrt(3)) / 3, 0.0f,
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
};

// Vertices coordinates
GLfloat TRIANGLE_NINE_COLORS[] =
{ //               COORDINATES                  /     COLORS           //
	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
};


GLfloat SIMPLE_TRIANGLE_ISO[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f
};

// Vertices coordinates
GLfloat TRIANGLE_NINE[] =
{
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
};

GLfloat TRIANGLE_EIGHTEEN[] = 
{
    -1.0f, -1.0f, 0.0f,
    -1.0f * 1/3, -1.0f, 0.0f,
    1.0f * 1/3, -1.0, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f * 2/3, -1.0f * 1/3, 0.0f,
    1.0f * 2/3, -1.0f * 1/3, 0.0f,
    0.0f, -1.0f * 1/3, 0.0f,
    0.0f + (-1.0f * 2/3)/2, 1.0f * 1/3, 0.0f,
    0.0f - (-1.0f * 2/3)/2, 1.0f * 1/3, 0.0f,
    0.0f, 1.0f, 0.0f,
};

// Indices for vertices order
GLuint INDICIES_TRIANGLE_EIGHTEEN[] =
{
  0, 1, 4,
  1, 2, 6,
  2, 3, 5,
  4, 6, 7,
  6, 5, 8,
  7, 8, 9

};

// Indices for vertices order
GLuint INDICES_TRIANGLE_NINE[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};