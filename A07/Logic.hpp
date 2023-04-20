

void GameLogic(Assignment07 *A, float Ar, glm::mat4 &ViewPrj, glm::mat4 &World) {
	// The procedure must implement the game logic  to move the character in third person.
	// Input:
	// <Assignment07 *A> Pointer to the current assignment code. Required to read the input from the user
	// <float Ar> Aspect ratio of the current window (for the Projection Matrix)
	// Output:
	// <glm::mat4 &ViewPrj> the view-projection matrix of the camera
	// <glm::mat4 &World> the world matrix of the object
	// Parameters
	// Camera FOV-y, Near Plane and Far Plane
	const float FOVy = glm::radians(45.0f);
	const float nearPlane = 0.1f;
	const float farPlane = 100.f;
	
	// Player starting point
	const glm::vec3 StartingPosition = glm::vec3(-41.50, 0.0, -19.5);
	
	// Camera target height and distance
	const float camHeight = 0.25;
	const float camDist = 1.5;
	// Camera Pitch limits
	const float minPitch = glm::radians(-8.75f);
	const float maxPitch = glm::radians(60.0f);
	// Rotation and motion speed
	const float ROT_SPEED = glm::radians(120.0f);
	const float MOVE_SPEED = 2.0f;

	// Integration with the timers and the controllers
	// returns:
	// <float deltaT> the time passed since the last frame
	// <glm::vec3 m> the state of the motion axes of the controllers (-1 <= m.x, m.y, m.z <= 1)
	// <glm::vec3 r> the state of the rotation axes of the controllers (-1 <= r.x, r.y, r.z <= 1)
	// <bool fire> if the user has pressed a fire button (not required in this assginment)
	float deltaT;
	glm::vec3 m = glm::vec3(0.0f), r = glm::vec3(0.0f);
	bool fire = false;
	A->getSixAxis(deltaT, m, r, fire);

	// Game Logic implementation
	// Current Player Position - statc variables make sure thattheri value remain unchanged in subsequent calls to the procedure
	static glm::vec3 Pos = StartingPosition;
	static float roll, pitch, yaw = 0;
	//static glm::vec3 cOld = Pos;	// previous position needed for damping on camera
	static float charYawOld = 0;	// previous rotation needed for damping on character
	float lambda = 10;				// damping factor for camera position
	float rho = 15;					// damping factor for character rotation
	float delta = 0.08;				// factor for preventing the character from moving if its direction is not completely set
	// Camera Roll limits
	const float minRoll = glm::radians(-20.0f);
	const float maxRoll = glm::radians(20.0f);
	// dead zone variables
	static glm::vec3 aOld = Pos;
	float dist = 1;
	float mu = 0.001;
	static bool follow = false;


	// update variables
	// define orientation vectors
	glm::vec3 ux = glm::vec3(glm::rotate(glm::mat4(1), yaw, glm::vec3(0, 1, 0)) * glm::vec4(1, 0, 0, 1));
	glm::vec3 uy = glm::vec3(0,1,0);
	glm::vec3 uz = glm::vec3(glm::rotate(glm::mat4(1), yaw, glm::vec3(0, 1, 0)) * glm::vec4(0, 0, -1, 1));
	// update angles
	pitch += ROT_SPEED * r.x * deltaT;
	pitch = pitch < minPitch ? minPitch : (pitch > maxPitch ? maxPitch : pitch); // restrict pitch within specified range
	yaw += ROT_SPEED * r.y * deltaT;
	// character rotation with damping (rotation is applied in the character's world matrix)
	float charYaw = charYawOld;
	if (m.x != 0 || m.z != 0){
		float charYawNew = yaw + atan2(-m.x, m.z);
		charYaw = charYawOld * exp(-rho * deltaT) + charYawNew * (1 - exp(-rho * deltaT));
	}
	// camera roll (later applied as rotation to look-at matrix)
	roll += ROT_SPEED * r.z * deltaT;
	roll = roll < minRoll ? minRoll : (roll > maxRoll ? maxRoll : roll); // restrict roll within specified range
	// update position (only if character direction is defined after damping)
	if (abs(charYaw - charYawOld) < delta) {
		Pos += ux * MOVE_SPEED * m.x * deltaT;
		Pos += uy * MOVE_SPEED * m.y * deltaT;
		Pos += uz * MOVE_SPEED * m.z * deltaT;
		// prevent character from going under plane
		if (Pos.y < 0) Pos.y = 0;
	}
	// update old character rotation
	charYawOld = charYaw;
	// define world matrix
	World = glm::translate(glm::mat4(1), Pos) *
			glm::rotate(glm::mat4(1), charYaw, glm::vec3(0, 1, 0)); 
	// scale and rotation on roll and pitch angles are not necessary in this case
	// positions for camera and target
	glm::vec3 aNew = World * glm::vec4(0, camHeight, 0, 1);	// new target position
	glm::vec3 a;	// position of the target that must be followed by the camera
	// define the position to base the translation of the camera
	// the camera will be based on a different position depending on whether it should follow or not the character
	if (abs(glm::length(aNew - aOld)) > dist) follow = true;
	if (follow) a = aNew;
	else a = aOld;
	// define matrix for translation of the camera
	glm::mat4 T = glm::translate(glm::mat4(1), a);
	// define previous camera position for damping (defined HERE as static because it requires T and other variables declared previously)
	static glm::vec3 cOld = glm::vec3(T * glm::rotate(glm::mat4(1), yaw, uy) *	// camera should not be rotated by world matrix (needs only translation)
								glm::vec4(0, camHeight + camDist * sin(pitch), camDist * cos(pitch), 1));
	// damping computation
	glm::vec3 cNew = glm::vec3(T * glm::rotate(glm::mat4(1), yaw, uy) *		// camera should not be rotated by world matrix (needs only translation)
		glm::vec4(0, camHeight + camDist * sin(pitch), camDist * cos(pitch), 1));
	glm::vec3 c = cOld * exp(-lambda * deltaT) + cNew * (1 - exp(-lambda * deltaT)); // camera position
	// reset aOld position when stopping
	// last condition is introduced to preserve damping effect
	if (follow and m.x == 0 and m.y == 0 and m.z == 0 and abs(glm::length(c - cOld)) < mu) { 
		follow = false;
		aOld = a;
	}
	// update cOld
	cOld = c;
	// define view-projection matrix
	glm::mat4 Proj = glm::perspective(FOVy, Ar, nearPlane, farPlane);
	glm::mat4 View = glm::rotate(glm::mat4(1), -roll, glm::vec3(0,0,1)) * glm::lookAt(c, aNew, uy);
	glm::mat4 MirrorY = glm::scale(glm::mat4(1), glm::vec3(1, -1, 1));
	ViewPrj =  MirrorY*Proj*View;
}