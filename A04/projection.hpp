#include <glm/gtx/transform2.hpp>

void SetupProjectionMatrices(Assignment04 *A, float Ar) {
/**************
 Method Matrix(int N, glm::mat4 M) of object A,
 receives in N the number of the matrix that needs to be set, and the matrix in M
***************/

	glm::mat4 S;
	
	// define useful parameters
	float w = 10.0;
	float n = -50.0;
	float f = 50.0;
	// define generic orthogonal projection matrix (built following formula on the slides)
	glm::mat4 Port = glm::translate(glm::mat4(1), glm::vec3(0, 0, n / (n - f)));
	Port = glm::scale(Port, glm::vec3(1 / w, -Ar / w, 1 / (n - f)));
	
	// Isometric projection
	glm::mat4 RyIso = glm::rotate(glm::mat4(1), glm::radians(-45.0f), glm::vec3(0, 1, 0));		// rotation 45° on y axis
	glm::mat4 RxIso = glm::rotate(glm::mat4(1), glm::radians(35.26f), glm::vec3(1, 0, 0));		// rotation 35.26° on x axis
	S = Port*RxIso*RyIso;
	A->Matrix(1, S); // sets the matrix corresponding to piece 1

	// Dimetric
	glm::mat4 RyDim = RyIso;	// rotation on y axis is the same as in isometric case
	float alpha = 50.0f;		// define angle for rotation on x axis
	glm::mat4 RxDim = glm::rotate(glm::mat4(1), glm::radians(alpha), glm::vec3(1, 0, 0));		// rotation alpha-degrees on x axis
	S = Port*RxDim*RyDim;
	A->Matrix(2, S); // sets the matrix corresponding to piece 2

	// Trimetric
	float beta = -15.0f;	// define angle for rotation on y
	glm::mat4 RyTri = glm::rotate(glm::mat4(1), glm::radians(beta), glm::vec3(0, 1, 0));		// rotation beta-degrees on y axis
	glm::mat4 RxTri = RxDim;	// for rotation on x axis reuse rotation from dimetric
	S = Port*RxTri*RyTri;
	A->Matrix(3, S); // sets the matrix corresponding to piece 3

	// Cabinet
	float rho = 0.5;	// define reduction factor
	alpha = 45.0f;		// adjust alpha angle
	glm::mat4 SCab = glm::shearZ3D(glm::mat4(1), -rho * glm::cos(alpha), -rho * glm::sin(alpha));	// shear on z axis
	S = Port*SCab;
	A->Matrix(4, S); // sets the matrix corresponding to piece 4

}
