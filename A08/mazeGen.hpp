#include <iostream>
#include <stdio.h>

void Assignment08::createMazeMesh(int row, int col, char **maze) {
	// The procedure gets in input the number of rows <row> of the maze, and the number of columns <col>
	// Element <maze[r][c]>, with 0 <= r <= row-1 and 0 <= c <= col-1 contains:
	//		Symbol ' ' if there is an empty space
	//		Symbol '#' if there is a wall
	//
	// Example: The following piece of code executes the instruction in the ... section
	//          if there is a wall in position r=5, c=7
	//
	// int r, c;
	// r = 5; c = 7;
	// if(maze[r][c] == '#') {
	//		...
	// }
	//
	// The example below creates a square, with four vertices and two triangles.
	// It must be deleted and replaced with your code creating the mesh of the maze.
	
	// Fill array vPos with the positions of the vertices of the mesh
	int r;
	int c;
	int z = 1;
	int count = 0;
	// push positions for the base
	vPos.push_back(0.0); vPos.push_back(0.0); vPos.push_back(0.0); 
	vPos.push_back(col); vPos.push_back(0.0); vPos.push_back(0.0); 
	vPos.push_back(0.0); vPos.push_back(0.0); vPos.push_back(row);
	vPos.push_back(col); vPos.push_back(0.0); vPos.push_back(row);
	// push vertices for horizontal walls
	for (r = 0; r < row; r++) {
		for (c = 0; c < col; c++) {
			// increase count if current cell is '#'
			if (maze[r][c] == '#') count++;
			// push positions of 4 vertices if starting or ending a row of more than one '#'
			if ((c < col - 1 and count == 1 and maze[r][c] == '#' and maze[r][c + 1] == '#') or
				(count > 1 and maze[r][c] == ' ')) {
				vPos.push_back(c); vPos.push_back(1.0); vPos.push_back(r);
				vPos.push_back(c); vPos.push_back(1.0); vPos.push_back(r+1);
				vPos.push_back(c); vPos.push_back(0.0); vPos.push_back(r);
				vPos.push_back(c); vPos.push_back(0.0); vPos.push_back(r+1);
				}
			// push position of vertices if ending a row of more than 1 '#' with last column
			if (c == col - 1 and count > 1) {
				vPos.push_back(c+1); vPos.push_back(1.0); vPos.push_back(r);
				vPos.push_back(c+1); vPos.push_back(1.0); vPos.push_back(r + 1);
				vPos.push_back(c+1); vPos.push_back(0.0); vPos.push_back(r);
				vPos.push_back(c+1); vPos.push_back(0.0); vPos.push_back(r + 1);
			}
			// update count
			if (c == col - 1 or maze[r][c] == ' ') {
				count = 0;
			}
		}
	}

	// push vertices for vertical walls
	for (c = 0; c < col; c++) {
		for (r = 0; r < row; r++) {
			// increase count if current cell is '#'
			if (maze[r][c] == '#') count++;
			// push positions of 4 vertices if starting or ending a column of more than one '#'
			if ((r < row -1 and count == 1 and maze[r][c] == '#' and maze[r+1][c] == '#') or
				(count > 1 and maze[r][c] == ' ')) {
				vPos.push_back(c+1); vPos.push_back(1.0); vPos.push_back(r);
				vPos.push_back(c); vPos.push_back(1.0); vPos.push_back(r);
				vPos.push_back(c+1); vPos.push_back(0.0); vPos.push_back(r);
				vPos.push_back(c); vPos.push_back(0.0); vPos.push_back(r);
			}
			// push position of vertices if ending a column of more than 1 '#' with last row
			if (r == row - 1 and count > 1) {
				vPos.push_back(c + 1); vPos.push_back(1.0); vPos.push_back(r+1);
				vPos.push_back(c); vPos.push_back(1.0); vPos.push_back(r + 1);
				vPos.push_back(c + 1); vPos.push_back(0.0); vPos.push_back(r+1);
				vPos.push_back(c); vPos.push_back(0.0); vPos.push_back(r + 1);
			}
			// update count
			if (r == row - 1 or maze[r][c] == ' ') {
				count = 0;
			}
		}
	}

	// translate maze to see it from front in the beginning
	for (int i = 0; i < vPos.size(); i += 3) {
		vPos[i] -= col/2;
		vPos[i + 2] -= row*2/3;
	}


	// Fill the array vIdx with the indices of the vertices of the triangles
	// push triangles for the base
	vIdx.push_back(0); vIdx.push_back(1); vIdx.push_back(2); 
	vIdx.push_back(1); vIdx.push_back(2); vIdx.push_back(3);
	for (int a = 4; a < vPos.size()/3; a+=8) {
		int b = a + 1;
		int c = a + 2;
		int d = a + 3;
		int e = a + 4;
		int f = a + 5;
		int g = a + 6;
		int h = a + 7;
		// push triangles
		// side faces
		vIdx.push_back(a); vIdx.push_back(b); vIdx.push_back(c);
		vIdx.push_back(d); vIdx.push_back(b); vIdx.push_back(c);
		vIdx.push_back(e); vIdx.push_back(f); vIdx.push_back(g);
		vIdx.push_back(h); vIdx.push_back(f); vIdx.push_back(g);
		// top face
		vIdx.push_back(a); vIdx.push_back(b); vIdx.push_back(f);
		vIdx.push_back(a); vIdx.push_back(e); vIdx.push_back(f);
		// side face, front
		vIdx.push_back(b); vIdx.push_back(f); vIdx.push_back(h);
		vIdx.push_back(b); vIdx.push_back(d); vIdx.push_back(h);
		// bottom face (useless after inserting the base)
		//vIdx.push_back(c); vIdx.push_back(d); vIdx.push_back(h);
		//vIdx.push_back(c); vIdx.push_back(g); vIdx.push_back(h);
		// side face, back
		vIdx.push_back(c); vIdx.push_back(g); vIdx.push_back(a);
		vIdx.push_back(e); vIdx.push_back(g); vIdx.push_back(a);
	}
}

