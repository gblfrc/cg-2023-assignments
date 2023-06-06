
void Assignment15::createBoxMesh(std::vector<Vertex>& vDef, std::vector<uint32_t>& vIdx) {
	// The primitive built here is a box centered in the origin, with proportions respecting the texture.

	// define size of the texture
	int texw = 1024;
	int texh = 512;

	// define sizes of the box
	float w = 1.0f;		// half of the width of the box
	float h = 0.9f;		// half of the height of the box
	float d = 0.25f;		// half of the depth of the box
	// create array of vertices of the box
	glm::vec3 vertices[8];
	int idx = 0;
	for (float i : {d, -d}) {
		for (float j : {h, -h}) {
			for (float k : {w, -w}) {
				if (idx < 4) vertices[idx] = glm::vec3(i, j, k);
				else  vertices[idx] = glm::vec3(i, j, -k);
				idx++;
			}
		}
	}

	// define convenient structures
	// order to push vertices for the different faces
	int indices[24] = { 0,1,2,3,4,5,6,7,
					    5,0,7,2,1,4,3,6,
					    5,4,0,1,2,3,7,6 };
	// coefficients for the normals of the vertices
	int nx[3] = { 1,0,0 };
	int ny[3] = { 0,0,1 };
	int nz[3] = { 0,1,0 };
	// uv coordinate information for the different faces
	float uv0[3][2] = { 93.0f / texw, 93.0 / texh,	// first yz face 
						0.0f, 93.0 / texh,			// first xy face
						93.0f / texw, 0.0f};		// first xz face
	float uv1[3][2] = { uv0[0][0] + 446.0f / texw, uv0[0][1],	// second yz face 
						uv0[1][0] + 446.0f / texw, uv0[1][1],	// second xy face 
						uv0[2][0], uv0[2][1] + 418.0f / texh};	// second xz face
	float faceSize[3][2] = {351.0f / texw, 325.0f / texh,	// size yz faces
					  93.0f / texw, 325.0f / texh,			// size xy faces
					  351.0f / texw, 93.0f / texh };		// size xz faces
	// loop to push vertices
	for (int iter = 0; iter < 3; iter++) {
		for (int i = 0; i < 8; i++) {
			idx = indices[iter * 8 + i];
			float uv[] = { (1 - i / 4) * uv0[iter][0] + (i / 4) * uv1[iter][0],
							(1 - i / 4)* uv0[iter][1] + (i / 4) * uv1[iter][1]};
			vDef.push_back({
				// push vertex positions
				{vertices[idx].x, vertices[idx].y, vertices[idx].z},
				// push vertex normals
				{nx[iter]*(vertices[idx].x / glm::abs(vertices[idx].x)),
				 ny[iter]*(vertices[idx].y / glm::abs(vertices[idx].y)),
				 nz[iter]*(vertices[idx].z / glm::abs(vertices[idx].z))},
				// push vertex uv coordinates
				{uv[0] + (i - 4*(i/4)) % 2 * faceSize[iter][0],uv[1] + ((i-4*(i/4)) / 2) * faceSize[iter][1]} });
		}
	}

	/*
	*	Previous attempt 
	*	The non-commented attempt above is just a condensed version of the one commented below.
	* 
	// push vertices for yz faces of the box
	float baseuv[] = { 93.0f / texw, 93.0 / texh };					// uv coordinates for top-left corner of the face
	float face_wh[] = { 351.0f / texw, 325.0f / texh };			// uv size of the face
	float baseuv2[] = { baseuv[0] + 446.0f / texw, baseuv[1] }; // uv coordinates for top-left corner of the opposite face
	for (idx = 0; idx < 4; idx++) {
		vDef.push_back({ {vertices[idx].x, vertices[idx].y, vertices[idx].z},
						 {vertices[idx].x / glm::abs(vertices[idx].x), 0.0f, 0.0f},
						 {baseuv[0] + idx % 2 * face_wh[0],baseuv[1] + (idx / 2) * face_wh[1]} });
	}
	for (idx = 4; idx < 8; idx++) {
		vDef.push_back({ {vertices[idx].x, vertices[idx].y, vertices[idx].z},
						 {vertices[idx].x / glm::abs(vertices[idx].x), 0.0f, 0.0f},
						 {baseuv2[0] + (idx - 4) % 2 * face_wh[0],baseuv2[1] + ((idx - 4) / 2) * face_wh[1]} });
	}
	// push vertices for xy faces of the box
	int indices[8] = { 5,0,7,2,1,4,3,6 };
	baseuv[0] = 0.0f;						// uv coordinates for top-left corner of the face
	face_wh[0] = 93.0f / texw;				// uv width of the face
	baseuv2[0] = baseuv[0] + 446.0f/texw;	// uv coordinates for top-left corner of the opposite face
	baseuv2[1] = baseuv[1];					// uv coordinates for top-left corner of the opposite face
	for (int i = 0; i < 4; i++) {
		idx = indices[i];
		vDef.push_back({ {vertices[idx].x, vertices[idx].y, vertices[idx].z},
						 {0.0f, 0.0f, vertices[idx].z / glm::abs(vertices[idx].z)},
						 {baseuv[0] + i % 2 * face_wh[0],baseuv[1] + (i / 2) * face_wh[1]} });
	}
	for (int i = 4; i < 8; i++) {
		idx = indices[i];
		vDef.push_back({ {vertices[idx].x, vertices[idx].y, vertices[idx].z},
						 {0.0f, 0.0f, vertices[idx].z / glm::abs(vertices[idx].z)},
						 {baseuv2[0] + (i - 4) % 2 * face_wh[0],baseuv2[1] + ((i-4) / 2) * face_wh[1]} });
	}
	// push vertices for xz faces of the box
	indices[1] = 4;							// order of indices for vertices of the box
	indices[2] = 0;
	indices[3] = 1;
	indices[4] = 2;
	indices[5] = 3;
	indices[6] = 7;
	baseuv[0] = 93.0f / texw;				// uv coordinates for top-left corner of the face
	baseuv[1] = 0.0f;						// uv coordinates for top-left corner of the face
	face_wh[0] = 351.0f / texw;				// uv width of the face
	face_wh[1] = 93.0f / texh;				// uv height of the face
	baseuv2[0] = baseuv[0];					// uv coordinates for top-left corner of the opposite face
	baseuv2[1] = baseuv[1] + 418.0f / texh;	// uv coordinates for top-left corner of the opposite face
	for (int i = 0; i < 4; i++) {
		idx = indices[i];
		vDef.push_back({ {vertices[idx].x, vertices[idx].y, vertices[idx].z},
						 {0.0f, vertices[idx].y / glm::abs(vertices[idx].y), 0.0f},
						 {baseuv[0] + i % 2 * face_wh[0],baseuv[1] + (i / 2) * face_wh[1]} });
	}
	for (int i = 4; i < 8; i++) {
		idx = indices[i];
		vDef.push_back({ {vertices[idx].x, vertices[idx].y, vertices[idx].z},
						 {0.0f, vertices[idx].y / glm::abs(vertices[idx].y), 0.0f},
						 {baseuv2[0] + (i - 4) % 2 * face_wh[0],baseuv2[1] + ((i-4) / 2) * face_wh[1]} });
	}
	*/

	// The procedures also fill the array vIdx with the indices of the vertices of the triangles
	for (int i = 0; i < 24; i += 4) {	// 24 is the number of pushed vertices
		// push indices as pairs of triangles
		vIdx.push_back(i); vIdx.push_back(i + 1); vIdx.push_back(i + 2);
		vIdx.push_back(i + 1); vIdx.push_back(i + 2); vIdx.push_back(i + 3);
	}
}

#define M_PI 3.141595f
void Assignment15::createSphereMesh(std::vector<Vertex>& vDef, std::vector<uint32_t>& vIdx) {
	// The primitive built here is a sphere of radius 1, centered in the origin, on which the Mars texture is applied seamless.
	float radius = 1.0f;
	int slices = 32;
	int rings = 32;
	float sliceAngleStep = M_PI / (slices / 2);
	float ringAngleStep = M_PI / rings;
	float uStep = 1.0f / slices;
	float vStep = 1.0f / rings;

	// The procedure fills array vPos with the positions of the vertices and of the normal vectors of the mesh
	// Procedure to push vertices: push top vertex, push intermediate rings, push bottom vertex
	// It is possible to generate a sphere with a single vertex on top; however, this might lead to pole pinching
	// To make this problem less evident, each triangle in the cap ring can refer to a different vertex
	// push top vertices
	for (int i = 0; i < slices; i++) {
		vDef.push_back({ {0,1.0f,0}, {0,1.0f,1}, {(uStep / 2) * (i +1), 0.0f}});
	}
	// push vertices on the rings
	for (int i = 0; i < rings - 1; i++) {
		float currentRingAngle = M_PI / 2 - (i + 1) * ringAngleStep;
		float y = radius * sin(currentRingAngle);
		float currentRadius = radius * cos(currentRingAngle);
		float v = vStep * (i + 1);
		for (int j = 0; j <= slices; j++) {
			float currentSliceAngle = j * sliceAngleStep;
			float x = currentRadius * cos(currentSliceAngle);
			float z = currentRadius * sin(currentSliceAngle);
			glm::vec3 pos = glm::vec3(x, y, z);
			glm::vec3 norm = glm::normalize(pos);
			float u = uStep * j;
			vDef.push_back({ {pos.x, pos.y, pos.z}, {norm.x, norm.y, norm.z}, {u,v} });
		}
	}
	// push bottom vertex
	for (int i = 0; i < slices; i++) {
		vDef.push_back({ {0,-1.0f,0}, {0,-1.0f,1}, {(uStep / 2) * (i + 1), 0.0f} });
	}


	// The procedures also fill the array vIdx with the indices of the vertices of the triangles
	// push top cap
	for (int i = 0; i < slices; i++) {
		vIdx.push_back(i); vIdx.push_back(i + slices); vIdx.push_back(i + slices + 1);
	}
	// push intermediate rings
	int shift = slices + 1;
	for (int j = 0; j < rings; j++) {
		for (int i = 0; i <= slices; i++) {
			int idx = slices + j * (slices + 1) + i;
			vIdx.push_back(idx); vIdx.push_back(idx + 1); vIdx.push_back(idx + shift);
			vIdx.push_back(idx + 1); vIdx.push_back(idx + shift); vIdx.push_back(idx + shift + 1);
		}
	}
	// push bottom cap
	int last = 2 * slices + (slices + 1) * (rings - 1);
	for (int i = 0; i < slices; i++) {
			vIdx.push_back(last - i); vIdx.push_back(last - i - slices); vIdx.push_back(last - i - slices - 1);
	}
}

