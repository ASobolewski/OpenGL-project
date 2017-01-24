#include "Gear.h"

void calc_gear_coords(std::vector<GLfloat> &coords, GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLuint segments)
{
	GLfloat alfa = 2.0f * glm::pi<GLfloat>() / segments;
	GLfloat xi, yi;
	coords.push_back(x);
	coords.push_back(y);
	coords.push_back(z);

	for (GLuint i = 0; i < segments; i++)
	{
		if (i % 2)
		{
			xi = radius * 1.5 * cosf(alfa * i);
			yi = radius * 1.5 * sinf(alfa * i);
		}
		else
		{
			xi = radius * cosf(alfa * i);
			yi = radius * sinf(alfa * i);
		}
		coords.push_back(x + xi);
		coords.push_back(y + yi);
		coords.push_back(z);
	}
}

std::vector<GLfloat> calc_gear_coords(GLfloat x, GLfloat y, GLfloat z, GLfloat height, GLfloat radius, GLuint segments)
{
	std::vector<GLfloat> coords;
	calc_gear_coords(coords, x, y, z, radius, segments);
	calc_gear_coords(coords, x, y, z + height, radius, segments);

	std::vector<GLuint> indices = calc_cylinder_indices(segments);

	std::vector<GLfloat>gearCoords = calc_cylinder_final(coords, calc_cylinder_normals(coords, indices), indices, segments);

	return gearCoords;

}