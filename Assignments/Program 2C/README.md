## Program 2C - Knucklebones Program  
### Author: Jesus Mendoza 
### Description:  

This program is a digital version of the dice-based game *Knucklebones*. Players take turns rolling a die and strategically placing its value into a 3x3 grid to maximize their score. The program uses SFML for graphics, allowing for an animated dice roll and an interactive UI. Each player tries to outscore their opponent by filling their grid while competing for the highest calculated score.  

The program also includes animations for rolling dice, displays the current player's turn, and determines the winner at the end of the game.  

### Files  

|   #   | File                | Description                                          |  
| :---: | ------------------- | ---------------------------------------------------- |  
|   1   | [knuckebones.cpp](Knucklebones/knucklebones.cpp)  | Main program that implements the game. |  
|   2   | [images/](Knucklebones/images)           | Folder containing dice face images and animation.    |  
|   3   | [arial.ttf](Knucklebones/Arial.ttf)         | Font used for text rendering in the program.         |  

### Instructions  

#### Dependencies:  
- **SFML Library**: This program requires the SFML library to handle graphics and rendering. Make sure SFML is installed and correctly linked with your compiler.  

#### Running the Program:  
1. Compile the program:  
   ```bash  
   g++ knucklebones.cpp -o knucklebones -lsfml-graphics -lsfml-window -lsfml-system  
   ```  
2. Run the compiled program:  
   ```bash  
   ./knucklebones  
   ```  

#### Gameplay:  
- The game alternates between Player 1 and Player 2.  
- Press `R` to roll the dice on your turn.  
- Click on a column in your grid to place the rolled value.  
- The game ends after 18 turns (when all grid cells are filled).  
- The scores are calculated, and the winner is displayed.  

#### Files in `images/`:  
- **Dice Face Images**: Files named `1.png` to `6.png` represent the dice faces.  
- **Animation Frames**: Files named `frame_001.png` to `frame_024.png` for the dice animation.  
- **Logo**: `knuckleboneslogo.jpg` displayed at the top of the window.  

### Notes:  
- Make sure all image files are in the `images/` folder and the font file `arial.ttf` is in the same directory as the executable.  
