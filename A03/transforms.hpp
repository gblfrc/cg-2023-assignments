

void SetupMatrices(Assignment03 *A) {
/**************
 Method Matrix(int N, glm::mat4 M) of object A,
 receives in N the number of the matrix that needs to be set, and the matrix in M
***************/

	glm::mat4 S;
	
	
	// To solve the puzzle: scale 2x proportionally, centered in (2,0,-3)
	glm::mat4 S1 = glm::scale(glm::mat4(1), glm::vec3(2));				// scale proportionally 2x
	glm::mat4 T1 = glm::translate(glm::mat4(1), glm::vec3(2,0,-3));		// translate (2,0,-3)
	S = T1*S1*inverse(T1);												// compute transformation matrix as in the slides
	A->Matrix(1, S); // sets the matrix corresponding to piece 1

	// To solve the puzzle: scale 3x on an axis oriented 45 degrees between the x and z axis and passing through point (1,0,0)
	glm::mat4 R2 = glm::rotate(glm::mat4(1), glm::radians(45.0f), glm::vec3(0, 1, 0));	// rotate around axis y 45 degrees
	glm::mat4 T2 = glm::translate(glm::mat4(1), glm::vec3(1,0,0));						// translate (1,0,0)
	glm::mat4 S2 = glm::scale(glm::mat4(1), glm::vec3(3,1,1));							// scale 3x on the x axis
	S = T2*R2*S2*inverse(R2)*inverse(T2);												// compute transformation matrix as in the slides
	A->Matrix(2, S); // sets the matrix corresponding to piece 2

	// To solve the puzzle: find it yourself! Hint: compose a rotation around an arbitrary point with a translation
	glm::mat4 T3 = glm::translate(glm::mat4(1), glm::vec3(2, 0, 3));					// translate (2,0,3) (needed inverse to origin)
	glm::mat4 R3 = glm::rotate(glm::mat4(1), glm::radians(-45.0f), glm::vec3(0, 1, 0));	// rotate 45 degrees around y axis
	glm::mat4 T3_1 = glm::translate(glm::mat4(1), glm::vec3(1, 0, 2));					// translate (1,0,2) (place to position)
	S = T3_1*inverse(R3)*inverse(T3);													// compute transformation matrix
	A->Matrix(3, S); // sets the matrix corresponding to piece 3

	// To solve the puzzle: rotate 60 degree around the y axis, centered in (-1,0,-2)
	glm::mat4 T4 = glm::translate(glm::mat4(1), glm::vec3(-1, 0, -2));					// translate (-1,0,-2)
	glm::mat4 R4 = glm::rotate(glm::mat4(1), glm::radians(60.0f), glm::vec3(0, 1, 0));	// rotate 60 degrees around y axis
	S = T4*R4*inverse(T4);																// compute transformation matrix
	A->Matrix(4, S); // sets the matrix corresponding to piece 4

	// To solve the puzzle: rotate -90 degree around an arbitrary axis passing in (-1,0,0). The x axis can be aligned to this arbitrary direction with a rotation of -45 around the y axis.	
	glm::mat4 T5 = glm::translate(glm::mat4(1), glm::vec3(-1, 0, 0));						// translate (-1,0,0)
	glm::mat4 R5y = glm::rotate(glm::mat4(1), glm::radians(45.0f), glm::vec3(0, 1, 0));		// rotate 45 degrees on y axis
	glm::mat4 R5z = glm::rotate(glm::mat4(1), glm::radians(45.0f), glm::vec3(0, 0, 1));		// rotate 45 degrees on z axis
	glm::mat4 R5x = glm::rotate(glm::mat4(1), glm::radians(-90.0f), glm::vec3(1, 0, 0));	// rotate 90 degrees on x axis
	glm::mat4 R5y_1 = glm::rotate(glm::mat4(1), glm::radians(-90.0f), glm::vec3(0, 1, 0));	// rotate 90 degrees on x axis
	S = T5*R5y_1*R5x*R5z*R5y*inverse(T5);													// compute transformation matrix
	A->Matrix(5, S); // sets the matrix corresponding to piece 5

	// To solve the puzzle: find it yourself! Hint: compose a non-proportional scaling that halves the object along one of the main axes, centered in an arbitrary point, with a translation
	glm::mat4 T6 = glm::translate(glm::mat4(1), glm::vec3(-3, 0, 2));						// translate (-3,0,2)
	glm::mat4 S6 = glm::scale(glm::mat4(1), glm::vec3(2, 1, 1));							// double size on x (needed inverse)
	glm::mat4 T6_1 = glm::translate(glm::mat4(1), glm::vec3(-1, 0, 2));						// translate (-1,0,2)
	S = T6_1*inverse(S6)*inverse(T6);														// compute transformation matrix
	A->Matrix(6, S); // sets the matrix corresponding to piece 6

}
