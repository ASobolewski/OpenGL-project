#include "Cylinder.h"


void calc_circle_coords(std::vector<GLfloat> &coords, GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLuint segments)
{
	GLfloat alfa = 2.0f * glm::pi<GLfloat>() / segments;

	coords.push_back(x);
	coords.push_back(y);
	coords.push_back(z);
	for (GLuint i = 0; i < segments; i++)
	{

		GLfloat xi = radius *glm::cos(alfa*i);
		GLfloat yi = radius *glm::sin(alfa*i);
		coords.push_back(x + xi);
		coords.push_back(y + yi);
		coords.push_back(z);
	}
}
std::vector<GLuint> calc_circle_indices(GLuint segments)
{
	std::vector<GLuint> indices;
	for (GLuint i = 1; i < segments; i++)
	{
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i + 1);
	}
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(segments);

	for (GLuint i = segments + 2; i < segments * 2 + 1; i++)
	{
		indices.push_back(segments + 1);
		indices.push_back(i);
		indices.push_back(i + 1);
	}
	indices.push_back(segments + 1);
	indices.push_back(segments * 2 + 1);
	indices.push_back(segments + 2);
	return indices;
}

std::vector<GLuint> calc_cylinder_side_indices(GLuint segments)
{
	std::vector<GLuint> indices;
	for (GLuint i = 1; i < segments; i++)
	{
		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(segments + 1 + i);
	}
	indices.push_back(segments);
	indices.push_back(1);
	indices.push_back(segments * 2 + 1);

	for (GLuint i = segments + 2; i < segments * 2 + 1; i++)
	{
		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i - segments);
	}
	indices.push_back(1);
	indices.push_back(segments + 2);
	indices.push_back(segments * 2 + 1);
	return indices;
}

std::vector<GLuint> calc_cylinder_indices(GLuint segments)
{
	std::vector<GLuint> circleIndices = calc_circle_indices(segments);
	std::vector<GLuint> sideIndices = calc_cylinder_side_indices(segments);
	std::vector<GLuint> cylinderIndices;
	cylinderIndices.reserve(circleIndices.size() + sideIndices.size());
	cylinderIndices.insert(cylinderIndices.end(), circleIndices.begin(), circleIndices.end());
	cylinderIndices.insert(cylinderIndices.end(), sideIndices.begin(), sideIndices.end());
	return cylinderIndices;
}


std::vector<GLfloat> calc_cylinder_normals(std::vector<GLfloat> cylinderCoords, std::vector<GLuint> indices)
{
	std::vector<GLfloat> normals;

	glm::vec3 A;
	glm::vec3 B;

	for (GLuint i = 0; i < indices.size(); i += 3)
	{
		A = glm::vec3(cylinderCoords[3 * indices[i + 1]] - cylinderCoords[3 * indices[i]],
			cylinderCoords[3 * indices[i + 1] + 1] - cylinderCoords[3 * indices[i] + 1],
			cylinderCoords[3 * indices[i + 1] + 2] - cylinderCoords[3 * indices[i] + 2]);

		B = glm::vec3(cylinderCoords[3 * indices[i + 2]] - cylinderCoords[3 * indices[i]],
			cylinderCoords[3 * indices[i + 2] + 1] - cylinderCoords[3 * indices[i] + 1],
			cylinderCoords[3 * indices[i + 2] + 2] - cylinderCoords[3 * indices[i] + 2]);
		glm::vec3 iloczyn;

		if (i < indices.size() / 4 - 3)
			iloczyn = glm::normalize(glm::cross(B, A));
		else if (i < indices.size() / 2 - 3)
			iloczyn = glm::normalize(glm::cross(A, B));
		else if (i< indices.size() * 3 / 4)
			iloczyn = glm::normalize(glm::cross(A, B));
		else if (i< indices.size() - 3)
			iloczyn = glm::normalize(glm::cross(B, A));
		else
			iloczyn = glm::normalize(glm::cross(A, B));

		normals.push_back(iloczyn.x);
		normals.push_back(iloczyn.y);
		normals.push_back(iloczyn.z);
	}

	return normals;
}

std::vector<GLfloat> calc_cylinder_final(std::vector<GLfloat> coords, std::vector<GLfloat> normals, std::vector<GLuint> indices, int segments)
{
	std::vector<GLfloat> result;

	int j = 0;
	int k = 0;
	for (GLuint i = 0; i < indices.size(); i++)
	{
		result.push_back(coords[3 * indices[i]]);
		result.push_back(coords[3 * indices[i] + 1]);
		result.push_back(coords[3 * indices[i] + 2]);
		result.push_back(normals[j]);
		result.push_back(normals[j + 1]);
		result.push_back(normals[j + 2]);
		k++;
		if (k % 3 == 0)
		{
			j += 3;
		}
	}

	return result;
}

std::vector<GLfloat> calc_cylinder_coords(GLfloat x, GLfloat y, GLfloat z, GLfloat height, GLfloat radius, GLuint segments)
{
	std::vector<GLfloat> coords;
	calc_circle_coords(coords, x, y, z, radius, segments);
	calc_circle_coords(coords, x, y, z + height, radius, segments);

	std::vector<GLuint> indices = calc_cylinder_indices(segments);

	std::vector<GLfloat>cylinderCoords = calc_cylinder_final(coords, calc_cylinder_normals(coords, indices), indices, segments);

	return cylinderCoords;
}