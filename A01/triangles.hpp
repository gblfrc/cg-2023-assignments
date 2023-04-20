

void SetupTriangles(Assignment01 *A) {
/**************
 Function Triangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b)

 draws a triangle connecting points (x1,y1)  (x2, y2) and (x3, y3), colored with the (r,g,b) specified color.
 vertex are expressed in Normalized screen coordinates, (i.e. in range [-1,+1]), following the Vulkan convention.
 The red, green and blue (r,g,b) values are in the range [0,1].
 
 Using function Triangle(...) try to draw a children house, similar to the one below.
 
 First remove the two function below (given only as an example), and replace them with your own.
 Since it is a C program, you can use for loops if you think it can be helpful in your drawing.
 The for() command below that draws a sun like shape in exact center of the screen near the top,
 is an example on how you can use it: please remove it, and replace it with your own code.
 It is not necessery to use a for loop if you do not really need it: it has been put here only as
 an example to help students not familiar with C++.
***************/

	/*
	COLORS:
	RED: 255, 0, 0
	YELLOW: 235, 185, 7
	PURPLE: 148, 43, 158
	BLUE: 40, 157, 212			(bottom triangle)
	SKY BLUE: 138, 212, 235		(top triangle)
	PINK: 237, 166, 205
	GREEN: 111, 148, 16
	*/

	// declare color arrays
	float red[3] = { 255 / 255.0, 0 / 255.0, 0 / 255.0 };
	float yellow[3] = { 235 / 255.0, 185 / 255.0, 7 / 255.0 };
	float purple[3] = { 148 / 255.0, 43 / 255.0, 158 / 255.0 };
	float blue[3] = { 40 / 255.0, 157 / 255.0, 212 / 255.0 };
	float sky_blue[3] = { 138 / 255.0, 212 / 255.0, 235 / 255.0 };
	float pink[3] = { 237 / 255.0, 166 / 255.0, 205 / 255.0 };
	float green[3] = { 111 / 255.0, 148 / 255.0, 15 / 255.0 };

	//A->Triangle(-1,-1, 0,0, -1,1,   1,0,0);	// Draws a red triangle pointing right
	//A->Triangle(1,-1, 0,0, 1,1,   0,1,0);	// Draws a green triangle pointing left
	A->Triangle(-0.27,0.1,	0.12,0.65,	0.12,-0.42,	red[0],red[1],red[2]); // red triangle
	A->Triangle(-0.27,0.1,	-0.27,0.85,	0.27,0.85,	blue[0],blue[1],blue[2]); // blue triangle
	A->Triangle(-0.44,0.58,	-0.27,0.85,	-0.64,0.85,	green[0],green[1],green[2]); // green parallelogram (1)
	A->Triangle(-0.44,0.58,	-0.8,0.58,	-0.64,0.85,	green[0],green[1],green[2]); // green parallelogram (2)
	A->Triangle(0.12,-0.42,	0.38,-0.05,	0.12,0.33,	yellow[0],yellow[1],yellow[2]); // yellow triangle
	A->Triangle(0.12,-0.42,	0.3,-0.16,	0.5,-0.42,	purple[0],purple[1],purple[2]); // purple square (1)
	A->Triangle(0.12,-0.42,	0.3,-0.67,	0.5,-0.42,	purple[0],purple[1],purple[2]); // purple square (2)
	A->Triangle(0.5,-0.94,	0.3,-0.67,	0.5,-0.42,	sky_blue[0],sky_blue[1],sky_blue[2]); // sky blue triangle
	A->Triangle(0.12, -0.42, 0.3, -0.67, 0.12,-0.94, pink[0], pink[1], pink[2]); // purple square (2)

}
