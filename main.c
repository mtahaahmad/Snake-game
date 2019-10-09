#include <msp430.h> 
#include "HAL_Dogs102x6.h"
//#include "HAL_Buttons.h"
#include "snakeFunctions.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


/***** x 0-101, y 0-63 *****/

#define maxLength 1500

uint16_t controlButtons = 0x00A6; //0b10100110
volatile float score = 0;
char buffer[100];
int foodScore = 0;
int ateFood = 1;
int xFood, yFood;
int gameOver = 0;
int snakeLength = 15;
int snakeDirection = 1; //0 is for up, 1 for right, 2 for down, and 3 for left
int snakeXCoordinates[maxLength]; // first element is the xCoordinate of the  head of the snake and the next elements follow
int snakeYCoordinates[maxLength]; // first element is the yCoordinate of the  head of the snake and the next elements follow

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	srand((unsigned) time(0));

	P1DIR |= BIT0; // LED1
	P1OUT &= ~BIT0;

	volatile unsigned int i;
    uint8_t contrast, brightness;
    contrast = 11;
    brightness = 11;

    initializeTimerA();

    /* up is connected to P2.0
     * right is connected to P2.3
     * down is connected to P2.4
     * left is connected to P2.6
     */

    // Configure buttons as inputs with pulldown resistor
    initializeButtons(controlButtons);
    // Enable Interrupts
    __enable_interrupt();
    interrupt4Buttons(controlButtons);

	// Configure Dogs102x6 ports
    P5OUT &= ~(BIT6 + BIT7);        // LCD_C/D, LCD_RST
    P5DIR |= BIT6 + BIT7;
    P7OUT &= ~(BIT4 + BIT6);        // LCD_CS, LCD_BL_EN
    P7DIR |= BIT4 + BIT6;
    P4OUT &= ~(BIT1 + BIT3);        // SIMO, SCK
    P4DIR &= ~BIT2;                 // SOMI pin is input
    P4DIR |= BIT1 + BIT3;

    // LCD initialization
    Dogs102x6_init();
    Dogs102x6_backlightInit();

    Dogs102x6_setBacklight(brightness);
    Dogs102x6_setContrast(contrast);
    Dogs102x6_clearScreen();
    Dogs102x6_stringDraw(3,36,"SNAKE",DOGS102x6_DRAW_NORMAL);
    for(i=1; i<=5; i++)
        __delay_cycles(200000);

    initializeSnakeCoordinates(snakeXCoordinates, snakeYCoordinates, maxLength);
    initializeSnake(snakeXCoordinates, snakeYCoordinates, &snakeLength);

    while(!gameOver)
    {
        moveSnake(snakeXCoordinates, snakeYCoordinates, &snakeLength, snakeDirection);
        snakeFood(snakeXCoordinates, snakeYCoordinates, snakeLength, &ateFood, &xFood, &yFood); //ateFood = 0 means didn't eat
        Dogs102x6_pixelDraw(xFood, yFood, 0);
        checkForCollision(snakeXCoordinates, snakeYCoordinates, snakeLength, &gameOver);
        checkIfFoodEaten(snakeXCoordinates, snakeYCoordinates, &snakeLength, &ateFood, xFood, yFood);
    }

    Dogs102x6_clearScreen();
    Dogs102x6_stringDraw(3,23,"GAME OVER!",DOGS102x6_DRAW_NORMAL);
    sprintf(&buffer, "%f", score);
    Dogs102x6_stringDraw(4,23,"Score: ",DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDraw(5,23,&buffer,DOGS102x6_DRAW_NORMAL);

	return 0;
}
