# CubeSolver
A desktop app that solves Rubik's Cubes in 24 moves or less using a variation of Kociemba's algorithm. This app was made as a hobby project, which gave me a challenge to create a simpler and easier to understand implementation of a solving algorithm, as well as a way to learn how to delvelop GUI apps. 
The app includes an interactive 2-d cube on which face turns may be applied, as well as an editor for user input patterns. Includes pattern validation and random scramblingand a display for the solution, which shows the colors of the faces to be turned, as well as the notation that matches the buttons to allow for solving the 2d-cube. The display also shows the amount of time it took for each solution to be found. For more information about how the algorithm works, see the [HOW_CUBESOLVER_WORKS.txt](HOW_CUBESOLVER_WORKS.txt) file

## Getting started
### Hardware Requirements
* 80 MB free disk space
* 90 MB RAM free
* 1 GHz (2 cores) CPU or better

### Installing
Download CubeSolver.zip by clicking on it and then clicking "Download" and extract it to a folder in your PC's file manager. The .exe can be run from the file or a shortcut can be made andadded to the desktop. Make sure that the .bin and .dll files are in the same directory as the .exe or the program won't run.

### How to use
To input a pattern, simply click "Empty Cube" to make a blank cube (except the centers), and then use the color buttons to select the 
color and click each of the cube tiles to color them as they appear on the cube. The centers of the physical cube being used should
match the cube shown in the program (red facing the user and white face down, for example)

To generate a random pattern, first click "Solved cube" so that a random scramble can be applied to the pattern and then click "Random"
If a valid cube was already entered, then there is no need to set the cube to its solved state first.

Each of the buttons under "Apply move" will turn a face of the cube in a way that corresponds to its notation. The starting letter of 
each button denotes the side of the cube that is turned (F for front, U for up, D for down, B for back, R and L for right and left) 
while the second digit denotes either a half turn or counter-clockwise quarter turn (2 or i respectively). A single letter and nothing 
else denotes a clockwise quarter turn on that face

Once a pattern has been entered, click "Solve" to solve it.

### Troubleshooting
If a missing file error occurs, make sure to place the .bin files as noted in the message in the same directory as the .exe. The files
may be found in the original .zip file of the program.
If an out of memory error occurs, make sure to free enough memory to use the app (at least 90 MB)

An edge or corner parity error means that either the physical cube was entered incorrectly (ensure the orientations match), or the cube 
has been tampered with. If you are sure the pattern on the physical cube was entered correctly (the cube appears exactly as it does on 
your screen), either 2 edges or 2 corners on the physical cube will need to be swapped.

A corner or edge orientation error should be handled as above, only instead, the edge will need to be flipped or the corner will need to
be twisted respectively.
If either of these errors errors occur while using the random scramble, make sure that either the starting pattern was valid or "Solved
Cube" was clicked first. 

If the program "freezes", make sure that the .bin files have not been modified or replace them with the original copies. If the issue
persists or any other problem arises and none of the solutions provided are applicable or work, you may create an issue (if you use
GitHub) or reach me at dylanevans595@gmail.com.

## Built with
* Qt 5.14.0 (MSVC 2017) -- The framework used

## Contributing
Simply make a pull request, create an issue, or reach me at dylanevans595@gmail.com if you wish to suggest improvements or provide
additional features

## License
This project is licensed under the MIT License, which can be found [here](LICENSE).
Note that this project uses Qt 5.14.0 libraries, which are licensed under LGPLv3. Thus it is necessary to use these libraries in a way
which complies with that license. For more information, see the [LGPLv3](https://opensource.org/licenses/lgpl-3.0.html)

## Credits
Special thanks to Herbert Kociemba, who devised the Two Phase Algorithm, on which this program is based (Note that this program
is NOT based on Kociemba's Cube Explorer). This work would have proven much more difficult without his work in the development of such 
an efficient, yet easily understood algorithm. To learn more about theTwo Phase Algorithm, visit [here](http://kociemba.org/cube.htm).
