void Assignment14::createCubeMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) {
	// The procedure fills array vPos with the positions of the vertices and of the normal vectors of the mesh
	// The procedures also fill the array vIdx with the indices of the vertices of the triangles
	// The primitive built here is a cube centered in the origin, whose edge lenght is 2.

	// Fill array vPos with the positions of the vertices of the mesh
	// Idea: build cube from pairs of parallel faces, with vertices sharing the same normal direction
	float coords[] = {-1.0f, 1.0f};
	for (int n = 0; n < 3; n++) {
		for (float i : coords) {
			for (float j : coords) {
				for (float k : coords) {
					// first face pair: push vertices in order 0 1 2 3 4 5 6 7
					if (n == 0)	vDef.push_back({ {i, j, k}, {1.0f, 0.0f, 0.0f} });
					// second face pair: push vertices in order 0 2 4 6 1 3 5 7
					else if (n == 1) vDef.push_back({ {j, k, i}, {0.0f, 0.0f, 1.0f} });
					// third face pair: push vertices in order 0 1 4 5 2 3 6 7
					else if (n == 2) vDef.push_back({ {j, i, k}, {0.0f, 1.0f, 0.0f} });
				}
			}
		}
	}
	// Fill the array vIdx with the indices of the vertices of the triangles
	for (int i = 0; i < 24; i += 4) {	// 24 is the number of pushed vertices
		// push indices as pairs of triangles
		vIdx.push_back(i); vIdx.push_back(i+1); vIdx.push_back(i+2);
		vIdx.push_back(i+1); vIdx.push_back(i+2); vIdx.push_back(i+3);
	}
}

void Assignment14::createFunctionMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) {
	// The procedure fills array vPos with the positions of the vertices and of the normal vectors of the mesh
	// The procedures also fill the array vIdx with the indices of the vertices of the triangles
	// The primitive built here is the surface y = sin(x) * cos(z) with -3 <= x <= 3 and -3 <= z <= 3.
	int limit = 3;

	// Fill array vPos with the positions of the vertices of the mesh
	/*
	Computations for the normal vector (see link in pdf)
	Parmeterized function: v(x,z) = [x, sin(x)*cos(z), z]
	Partial derivative on x: dv/dx(x,z) = [1, cos(x)*cos(z), 0]
	Partial derivative on z: dv/dz(x,z) = [0, -sin(x)*sin(z), 1]
	Cross product of partial derivatives: cross = [cos(x)cos(z), -1, -sin(x)sin(z)]
	Unit normal vector is normalized version of cross product
	*/
	for (int x = -limit; x <= limit; x++) {
		for (int z = -limit; z <= limit; z++) {
			float y = sin(x) * cos(z);
			glm::vec3 unorm = -glm::normalize(glm::vec3(cos(x) * cos(z), -1, -sin(x) * sin(z)));
			vDef.push_back({{float(x), y, float(z)}, {unorm.x, unorm.y, unorm.z}});
		}
	}

	// Fill the array vIdx with the indices of the vertices of the triangles
	int line = 2 * limit + 1; // if limit is 3, line is 7
	for (int i = 0; i < line - 1; i++) {
		for (int j = 0; j < line - 1; j++) {
			int base = i * line + j;
			vIdx.push_back(base); vIdx.push_back(base + 1); vIdx.push_back(base + line);
			vIdx.push_back(base+1); vIdx.push_back(base + line); vIdx.push_back(base + line + 1);
		}
	}
}

void Assignment14::createCylinderMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) {
	// The procedure fills array vPos with the positions of the vertices and of the normal vectors of the mesh
	// The procedures also fill the array vIdx with the indices of the vertices of the triangles
	// The primitive built here is a cylinder, with radius 1, and height 2, centered in the origin.
	int slices = 8;
	float angle = glm::radians(360.0f / float(slices));
	
	// Fill array vPos with the positions of the vertices of the mesh
	float levels[] = { -1.0f, 1.0f };
	for (float y : levels) {
		// push cap
		vDef.push_back({ {0.0f, y, 0.0f}, {0.0f, 1.0f, 0.0f} });
		// push rings
		for (int i = 0; i < slices; i++) {
			float x = cos(i*angle);
			float z = sin(i*angle);
			vDef.push_back({ {x, y, z}, {0.0f, 1.0f, 0.0f} });	// cap vertex
			vDef.push_back({ {x, y, z}, {x, 0.0f, z} });		// side vertex
		}
	}


	// Fill the array vIdx with the indices of the vertices of the triangles
	int shift = (slices * 2 + 1); // for 8 slices, shift is 17
	// push indices for caps
	for (int n = 0; n < 2; n++) {
		int base = n * shift;
		for (int i = 0; i < slices; i++) {
			if (i != slices - 1) { vIdx.push_back(base); vIdx.push_back(base + 2 * i + 1); vIdx.push_back(base + 2 * i + 3); }
			else { vIdx.push_back(base); vIdx.push_back(base + 2 * i + 1); vIdx.push_back(base + 1); }
		}
	}
	// push indices for side
	for (int i = 0; i < slices; i++) {
		int base = 2 * (i + 1);
		if (i != slices - 1) { 
			vIdx.push_back(base); vIdx.push_back(base +2); vIdx.push_back(base + 2 + shift);
			vIdx.push_back(base); vIdx.push_back(base + shift); vIdx.push_back(base + 2 + shift);
		}
		else {
			vIdx.push_back(base); vIdx.push_back(2); vIdx.push_back(2 + shift);
			vIdx.push_back(base); vIdx.push_back(base + shift); vIdx.push_back(2 + shift);
		}
	}






}
