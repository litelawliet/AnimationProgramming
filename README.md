Animation Programming is an ISART Digital Montreal project made in second year of Game Programming using a home made ISART Digital engine called WhiteBox. It allows us to obtain the data of bones, vertices and animations from an fbx file.

The goal of the project was to read those data and run the animation on screen. It uses the math library we made that year to perform all the calculation on the CPU (except the hardware skinning who is done in the vertex shader).

Note: If not running on first try, make sure the Project Working Directory is set on : $(SolutionDir)Data
Otherwise change it to that manners.
Also please note that the project can only run in x86 Platform due to WhiteBox's specifications.

During the run, keys :

 - 1 : improve the speed of the animation
 - 2 : decrease the speed of the animation
 - 3 : reset the speed to normal speed
 - R : switch to the running animation
 - Z : switch to the walking animation
 - WASD : to move in world space
 - mouse : to rotate in world space
