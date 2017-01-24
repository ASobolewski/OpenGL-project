#include"Utilities.h"

void calc_circle_coords(std::vector<GLfloat> &coords, GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLuint segments);
std::vector<GLuint> calc_circle_indices(GLuint segments);
std::vector<GLuint> calc_cylinder_side_indices(GLuint segments);
std::vector<GLuint> calc_cylinder_indices(GLuint segments);
std::vector<GLfloat> calc_cylinder_normals(std::vector<GLfloat> cylinderCoords, std::vector<GLuint> indices);
std::vector<GLfloat> calc_cylinder_final(std::vector<GLfloat> coords, std::vector<GLfloat> normals, std::vector<GLuint> indices, int segments);
std::vector<GLfloat> calc_cylinder_coords(GLfloat x, GLfloat y, GLfloat z, GLfloat height, GLfloat radius, GLuint segments);