/*
 * snakeFunctions.h
 *
 *  Created on: Nov 30, 2018
 *      Author: mxa176630
 */

#ifndef SNAKEFUNCTIONS_H_
#define SNAKEFUNCTIONS_H_

#include <stdint.h>

//void initializeTimerA(void);

void initializeTimerA(void);
void initializeButtons(uint16_t ctrlButtons);
void interrupt4Buttons(uint16_t ctrlButtons);

void initializeSnake(int *xCoord, int *yCoord, int *len);
void initializeSnakeCoordinates(int *xCoord, int *yCoord, int maxLen);
void moveSnake(int *xCoord, int *yCoord, int *len, int dir);
void snakeFood(int *xCoord, int *yCoord, int len, int *ateFood, int *xFood, int *yFood);
void checkForCollision(int *xCoord, int *yCoord, int len, int *gameOver);
void checkIfFoodEaten(int *xCoord, int *yCoord, int *len, int *ateFood, int xFood, int yFood);
void calculateScore(void);


#endif /* SNAKEFUNCTIONS_H_ */
