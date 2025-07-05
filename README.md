### Naval battle game
Completed for the MA-20 - Application of C, at CPNV. 
- The player has 10 minutes to sink all the computer boats
- At the first start, the program will create text files in the folder where it is run to save scores and players list.

![Language](https://img.shields.io/badge/language-french-darkblue)

<p align="center">
<img src="https://raw.githubusercontent.com/laurentbarraud/bataillenavale/refs/heads/master/bataille-navale-screenshot.jpg" height="300" alt="screenshot of bataille navale" >
</p>

### Installation
1. Download the main. c file to a local folder
2. In this local folder, create a new folder and call it "grids" (without quotes)
3. In the grids folder, create text files "grille01.txt", "grille02.txt", etc. up to 20.
4. Open each grid file and write in it according to this legend:
 - 1 Aircraft carrier (5 boxes), represented by the character "1"
 - 1 Cruiser (4 boxes), represented by the character "2"
 - 1 Destroyer (3 boxes), represented by the character "3"
 - 1 Submarine (3 boxes), represented by the character "4"
 - 1 torpedo boat (2 boxes), represented by the character "5"
 - Fill in the character "0" all the rest of the grid to have 10 lines of 10 characters.
5. Compile main.c file. 
I recommend using a C compiler from a popular IDE like CLion or Eclipse.
6. Run main.exe that has been produced.

