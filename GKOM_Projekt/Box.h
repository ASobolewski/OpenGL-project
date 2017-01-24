#ifndef BOX_H
#define BOX_H
#include "Utilities.h"

GLuint boxIndices[];
GLfloat boxNormals[];


void calc_rectangle_coords(std::vector<GLfloat> &coords, GLfloat x, GLfloat y, GLfloat z, GLfloat a, GLfloat b);
std::vector<GLfloat> calc_final_box_coords(std::vector<GLfloat> coords);
std::vector<GLfloat> calc_box_coords(GLfloat x, GLfloat y, GLfloat z, GLfloat a, GLfloat b, GLfloat h);

#endif