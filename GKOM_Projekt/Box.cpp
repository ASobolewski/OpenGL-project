#include"Box.h"

GLuint boxIndices[] = {
	//bottom
	0, 1, 2,
	1, 2, 3,
	//top
	4, 5, 6,
	5, 6, 7,
	//left
	0, 2, 4,
	2, 4, 6,
	//right
	1, 3, 5,
	3, 5, 7,
	//front
	0, 1, 4,
	1, 4, 5,
	//back
	2, 3, 6,
	3, 6, 7
};

GLfloat boxNormals[] = {
	0.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,

	-1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, 1.0f
};

void calc_rectangle_coords(std::vector<GLfloat> &coords, GLfloat x, GLfloat y, GLfloat z, GLfloat a, GLfloat b)
{
	coords.push_back(x);
	coords.push_back(y);
	coords.push_back(z);

	coords.push_back(x + a);
	coords.push_back(y);
	coords.push_back(z);

	coords.push_back(x);
	coords.push_back(y);
	coords.push_back(z + b);

	coords.push_back(x + a);
	coords.push_back(y);
	coords.push_back(z + b);
}

std::vector<GLfloat> calc_final_box_coords(std::vector<GLfloat> coords)
{
	std::vector<GLfloat> result;
	int j = 0;
	int k = 0;
	for (int i = 0; i < sizeof(boxIndices) / sizeof(GLuint); i++)
	{
		result.push_back(coords[3 * boxIndices[i]]);
		result.push_back(coords[3 * boxIndices[i] + 1]);
		result.push_back(coords[3 * boxIndices[i] + 2]);
		result.push_back(boxNormals[j]);
		result.push_back(boxNormals[j + 1]);
		result.push_back(boxNormals[j + 2]);
		k++;
		if (k % 6 == 0)
			j += 3;
	}
	return result;
}

std::vector<GLfloat> calc_box_coords(GLfloat x, GLfloat y, GLfloat z, GLfloat a, GLfloat b, GLfloat h)
{
	std::vector<GLfloat> coords;
	calc_rectangle_coords(coords, x, y, z, a, b);
	calc_rectangle_coords(coords, x, y + h, z, a, b);
	std::vector<GLfloat> boxCoords = calc_final_box_coords(coords);
	return boxCoords;
}

