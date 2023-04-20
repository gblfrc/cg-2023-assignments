#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <iostream>
using namespace std;

void SetupProjectionMatrices(Assignment05 *A, float Ar) {
/**************
 Method Matrix(int N, glm::mat4 M) of object A,
 receives in N the number of the matrix that needs to be set, and the matrix in M
***************/

	glm::mat4 S;
	glm::mat4 M = glm::scale(glm::mat4(1), glm::vec3(1, -1, 1));		//y-mirror matrix  
	float n = 0.1;
	float f = 50.0;
	
	// Fov-y = 60 deg
	glm::mat4 P1 = glm::perspective(glm::radians(60.0f), Ar, n, f);		// perspective projection with fov-y = 60°
	S = M*P1;
	A->Matrix(1, S); // sets the matrix corresponding to piece 1

	// Fov-y = 105 deg
	glm::mat4 P2 = glm::perspective(glm::radians(105.0f), Ar, n, f);	// perspective projection with fov-y = 105°
	S = M*P2;
	A->Matrix(2, S); // sets the matrix corresponding to piece 2

	// Fov-y = 25 deg
	glm::mat4 P3 = glm::perspective(glm::radians(25.0f), Ar, n, f);		// perspective projection with fov-y = 25°
	S = M*P3;
	A->Matrix(3, S); // sets the matrix corresponding to piece 3

	// Right View, Fov-x = 45 deg
	// Create frustum matrix after computing coordinates for sides of the screen (l,r,t,b) 
	float k = n * glm::tan(45.0f / 2);
	float l = 0;
	float r = 2 * k;
	float t = k / Ar;
	float b = -k / Ar;
	glm::mat4 F = glm::frustum(l, r, b, t, n, f);
	S = M * F;
	A->Matrix(4, S); // sets the matrix corresponding to piece 4

}
