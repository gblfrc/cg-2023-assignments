# Computer Graphics - Assignments
This folder contains my personal solutions to the assigments for the Computer Graphics course, held at [Politecnico di Milano](https://polimi.it) in Spring 2023. 

***DISCLAIMER***: The assignments represent a relevant part of the course work and are a necessary requirement for its passing. Therefore, any form of plagiarism is highly discouraged and the author doesn't hold accountable for any consequence thereof. This repository aims at being primarily an archive, for the author, of the job done for  the aforementioned course, and a source of inspiration for future students attempting the solution of the assignments.

## Table of contents
- [Repository organisation](#repository-organisation)
- [Running](#running)
- [Additional notes](#additional-notes)
  - [A00](#a00)
  - [A07](#a07)
  - [A09](#a09)
  - [A10](#a10)
- [Author](#author)


## Repository organisation
In this repository each folder corresponds to a specific assignment and contains:
- a *.zip* archive, containing the blank version of the assignment;
- the files modified by the author and representing the solution for the related assignment.

The aforementioned *.zip* archive corresponds exactly with the one published on the institutional website, [WeBeep](https://webeep.polimi.it), by the professor.

## Running
The author solved and run the assignments with Visual Studio 2022 (VS) on a machine running Windows 11. Therefore, the assignments and their solution have been completely tested under that specific environment, to which the following steps refer. In order to successfully run the solutions to the assignments:
1. Download the folder for a specific assignment;
2. Create a VS project with the necessary settings, which are explained in A00 and follow the Vulkan installation tutorial available [here](https://vulkan-tutorial.com/Development_environment);
3. Open in the file explorer the project directory, where VS has put the *.sln* file for the just-created project;
4. Extract in such folder the content of the *.zip* archive downloaded in the assignment folder;
5. From the VS solution explorer, select all the extracted files and folders and include them in the project[^inclusion];
6. Reference the files provided in the *headers* folder (extracted from the *.zip* archive) in the project settings;
7. Replace the blank files in the project with the solution files provided in the solution folder[^solutions].
8. Compile and run the project by pressing F5.

## Additional notes
This section contains supplementary notes towards a successful run and a complete understanding of the proposed solutions to the assignments.

### A00
This is the introductory assignment to the course and its aim is to let the student set-up correctly the Vulkan environment for the following assigments. For this reason, no solution file is inserted in the related folder.

### A07
For this assignment the aim is to implement a full 3rd person controller. The basic tasks for this assignment are expressed in the related *.pdf*, which can be found after unzipping its related archive. However, in the provided solution, some additional tasks, proposed by the professor during the lecture, have been implemented; these are:
- Damping on camera: the camera does not arrest abruptly when the character stops moving.
- Indipendent camera rotation: the camera can be rotated without affecting the character and the character can be seen from different angles.
- Movement-driven character rotation: the character orientation depends on the direction in which he is moving. 
- Damping on character: the character dooes not rotate abruptly when changing movement direction.
- Camera roll: the camera can rotate on its facing axis[^a07-camera-rot].
- Flying character: the character can detach from ground and move on a line which is orthogonal to the ground; a small check prevents it from going under the ground level.
- Dead zone: the camera waits for the character to change its position of a specific distance before following him

### A09
Similarly to the case of [A00](#a00), the folder for this assignment comes with no solution file. The reason behind this choice is the simplicity of the task provided in the assignment, i.e., the compilation of shaders with the *glslc* compiler. To solve this assigment, follow the instructions in the [Running](#running) section. Attempting to compile and run the assignment at this point will result in an error. To solve it, open a terminal window in the *shaders* folder and run the following commands[^glslc]:

`glslc PhongShader.vert -o PhongVert.spv`
`glslc PhongShader.frag -o PhongFrag.spv`

Now the assignment should show two grey squares, a horizontal and a vertical one. Repeat the same process changing the names of the input shaders to the ones including *.v2*; when running the program with the new shaders you should see a [Mandelbrot set](https://en.wikipedia.org/wiki/Mandelbrot_set). 

### A10
The solution to this assignment required editing two shader files. For this reason, the folder for this assignment contains another folder, called *shaders*. To successfully run the solution replace the whole *shaders* folder with the one provided and compile the files contained therein with the same commands written above for A09.

## Author
- [Gibellini Federico](https://github.com/gblfrc)

[^inclusion]: A note of caution: VS generally does not import all the files in folders recursively. In most of the cases, not importing such files does not prevent the projects to be run; in other cases, such as those in which the solutions are to put in a specific folder, it is simply enough to open the folder from the solution explorer and directly include the specific files.
[^solutions]: In most of the cases, there is a single file to replace in the main project folder. In very few occasions more than a file has to be replaced. For all those cases, please consult the [Additional notes](#additional-notes) section.
[^glslc]: The *glslc* command is not a native command in Windows. However, this compiler is usually distributed and installed with the Vulkan SDK. To make the command accessible from any directory, browse for the related executable in the Vulkan SDK *bin* folder and add the folder to the *PATH* environment variable. 
[^a07-camera-rot]: In order to avoid unpleasant effects, the camera roll was bound to 20°.
