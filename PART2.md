# Part 2

## Video Demo

Please provide the YouTube link to your [Video Demo](https://youtube.com).

## Minimum Requirements

### Completed


1. Game Board
2. Attributes
3. Movements and Attacks
4. Multiple Zombies
5. Game Objects
6. Game Controls
7. Commands
8. Save Game
9. Load Game
10. Win or Dead (Quit Game)
11. Reset Path

### Incomplete

1. Set the life limit for Alien
2. Arrow of turn for attacks

## Additional Features

N/A

## Contributions


MUHAMMAD AMIRUL HAIQAL BIN ZAMERI

1. Doing Game Objects
3. Doing Game Contols
4. Commands
5. Load Game

MUHAMMAD AFIF JAZIMIN BIN IDRIS

1. Doing Game Board
2. Doing Game Flow
3. Doing the Win or Dead (Quit Game)
4. Save Game

LEE JUN YAO

1. Attributes
2. Movement and Attacks
3. Multiple Zombies
4. Reset Path

## Problems Encountered & Solutions

1.Problem: Unable to make path reseting
Solution: Finding help from other people

2.Problem: Unable to figure out valid position for zombies
Solution: It first checks if the position is occupied by an alien by comparing the input position with the values stored in the alienX and alienY variables. If they are equal, the function returns false, indicating that the position is not valid.

Next, it loops through the zombies and checks if any of the zombies occupy the position by comparing the input position with the values stored in the zombiesX and zombiesY arrays. If there is a match, the function returns false.

If none of the checks return false, the function returns true, indicating that the position is valid. r and c, and returns a boolean value indicating whether the position (r, c) is valid or not.

3.Problem: Unable to enter the name of the file to save to and load from it because we encountered segmentation fault and cannot run the code.
Solution: We redo the code from the beginning and change it to just only overwrite in one file of the saved game file.

4.Problem: When we run the code of the new saved and loaded part, we found out that we couldn't print the board if the row is more than 5 when we loaded it.
Solution: We dynamically allocate memory for the grid array to the code.
