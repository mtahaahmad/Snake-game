/*
 * snakeFunctions.c
 *
 *  Created on: Nov 30, 2018
 *      Author: mxa176630
 */
#include "msp430.h"
#include "HAL_Dogs102x6.h"
#include "snakeFunctions.h"

volatile extern int snakeDirection;
volatile extern float score;
float *ptr = &score;

void initializeTimerA(void)
{
//    TA0CCTL0 = CM_1 + CCIS_0 + SCS + CAP + CCIE;      //capture on rising edge, CCI0A, synchronize capture source, capture mode, capture interrupt enable
//    TA0CTL = TASSEL_1 + MC_2 + TACLR;         // SMCLK, continuous mode, clear TAR

    TA0CCTL0 = CCIE;                          // CCR0 interrupt enabled
    TA0CCR0 = 65535;
    TA0CTL = TASSEL_1 + MC_1 + TACLR;         // SMCLK, upmode, clear TAR
}


void initializeButtons(uint16_t ctrlButtons)
{
    P2DIR &= ctrlButtons;
    P2OUT &= ctrlButtons;
    P2REN |= ~ctrlButtons; //pull down
    P2SEL &= ctrlButtons;
}


void interrupt4Buttons(uint16_t ctrlButtons)
{
    P2IES &= ctrlButtons; //select rising edge trigger
    P2IFG &= ctrlButtons; //clear flags
    P2IE |= ~ctrlButtons;   //enable interrupts
}


/* Make a snake somewhere in the middle of the LCD
*/
void initializeSnake(int *xCoord, int *yCoord, int *len)
{
    // zeroth index is the head of the snake
    *xCoord =  50;
    *yCoord =  30;

    Dogs102x6_clearScreen();
    int i;
    for(i=0; i<*len; i++)
    {
        Dogs102x6_pixelDraw(*(xCoord + i), *(yCoord + i), 0);
        *(xCoord + i + 1) =  *(xCoord + i) - 1;
        *(yCoord + i + 1) =  *(yCoord + i);
    }

}


/* Initialize all coordinates to zero
 */
void initializeSnakeCoordinates(int *xCoord, int *yCoord, int maxLen)
{
    int i;
    for(i=0; i<maxLen; i++)
    {
        *(xCoord + i) = 0;
        *(yCoord + i) = 0;
    }
}


/* update the snakeCoordinates in the direction of dir
 * dir=0 is up, dir=1 is rigth, dir=2 is down, dir=3 is left
 */
void moveSnake(int *xCoord, int *yCoord, int *len, int dir)
{
    switch(dir)
    {
    int i, j, tempX, tempY;
    int prevTempX, prevTempY;
    case 0: // direction is up

        if(*yCoord <= 0)
            *yCoord = 64;

        prevTempX = *xCoord;
        prevTempY = *yCoord - 1;
        Dogs102x6_clearScreen();

        for(i=0; i<*len; i++)
        {
            tempX = *(xCoord + i);
            tempY = *(yCoord + i);
            *(xCoord + i) = prevTempX;
            *(yCoord + i) = prevTempY;

            Dogs102x6_pixelDraw(*(xCoord + i), *(yCoord + i), 0);
            prevTempX = tempX;
            prevTempY = tempY;
        }


/*      The following for loop just keeps a record of some additional coordinates
 *      so once the snake length increases we already know what coordinates to assign
 *      to those pixels
 */
        j = i;
        for(i=j; i<j+3; i++)
        {
            tempX = *(xCoord + i);
            tempY = *(yCoord + i);
            *(xCoord + i) = prevTempX;
            *(yCoord + i) = prevTempY;

            prevTempX = tempX;
            prevTempY = tempY;
        }

        break;

    case 1: // direction is right

        if(*xCoord >= 101)
            *xCoord = -1;

        prevTempX = *xCoord + 1;
        prevTempY = *yCoord;
        Dogs102x6_clearScreen();

        for(i=0; i<*len; i++)
        {
            tempX = *(xCoord + i);
            tempY = *(yCoord + i);
            *(xCoord + i) = prevTempX;
            *(yCoord + i) = prevTempY;

            Dogs102x6_pixelDraw(*(xCoord + i), *(yCoord + i), 0);
            prevTempX = tempX;
            prevTempY = tempY;
        }

/*      The following for loop just keeps a record of some additional coordinates
 *      so once the snake length increases we already know what coordinates to assign
 *      to those pixels
 */
        j = i;
        for(i=j; i<j+3; i++)
        {
            tempX = *(xCoord + i);
            tempY = *(yCoord + i);
            *(xCoord + i) = prevTempX;
            *(yCoord + i) = prevTempY;

            prevTempX = tempX;
            prevTempY = tempY;
        }

        break;

    case 2: // direction is down

        if(*yCoord >= 63)
            *yCoord = -1;

        prevTempX = *xCoord;
        prevTempY = *yCoord + 1;
        Dogs102x6_clearScreen();

        for(i=0; i<*len; i++)
        {
            tempX = *(xCoord + i);
            tempY = *(yCoord + i);
            *(xCoord + i) = prevTempX;
            *(yCoord + i) = prevTempY;

            Dogs102x6_pixelDraw(*(xCoord + i), *(yCoord + i), 0);
            prevTempX = tempX;
            prevTempY = tempY;
        }

/*      The following for loop just keeps a record of some additional coordinates
 *      so once the snake length increases we already know what coordinates to assign
 *      to those pixels
 */
        j = i;
        for(i=j; i<j+3; i++)
        {
            tempX = *(xCoord + i);
            tempY = *(yCoord + i);
            *(xCoord + i) = prevTempX;
            *(yCoord + i) = prevTempY;

            prevTempX = tempX;
            prevTempY = tempY;
        }

        break;

    case 3: // direction is left

        if(*xCoord <= 0)
            *xCoord = 102;

        prevTempX = *xCoord - 1;
        prevTempY = *yCoord;
        Dogs102x6_clearScreen();

        for(i=0; i<*len; i++)
        {
            tempX = *(xCoord + i);
            tempY = *(yCoord + i);
            *(xCoord + i) = prevTempX;
            *(yCoord + i) = prevTempY;

            Dogs102x6_pixelDraw(*(xCoord + i), *(yCoord + i), 0);
            prevTempX = tempX;
            prevTempY = tempY;
        }

/*      The following for loop just keeps a record of some additional coordinates
 *      so once the snake length increases we already know what coordinates to assign
 *      to those pixels
 */
        j = i;
        for(i=j; i<j+3; i++)
        {
            tempX = *(xCoord + i);
            tempY = *(yCoord + i);
            *(xCoord + i) = prevTempX;
            *(yCoord + i) = prevTempY;

            prevTempX = tempX;
            prevTempY = tempY;
        }

        break;

    default:
        break;
    }
}


void snakeFood(int *xCoord, int *yCoord, int len, int *ateFood, int *xFood, int *yFood)
{
    if(*ateFood)
    {
        int lookForNewCoord = 1;

        while(lookForNewCoord)
        {
            lookForNewCoord = 0;
            *xFood = rand()%102;
            *yFood = rand()%64;

            int i;
            for(i=0; i<=len; i++)
            {
                if(*xFood == *(xCoord + i) || *yFood == *(yCoord + i))
                    lookForNewCoord = 1;
            }
        }

        *ateFood = 0;
    }
}


void checkForCollision(int *xCoord, int *yCoord, int len, int *gameOver)
{
    int i;
    for(i=1; i<len; i++)
    {
        if(*xCoord == *(xCoord + i) && *yCoord == *(yCoord + i))
            *gameOver = 1;
    }
}


void checkIfFoodEaten(int *xCoord, int *yCoord, int *len, int *ateFood, int xFood, int yFood)
{
    if(*xCoord == xFood && *yCoord == yFood)
    {
        *ateFood = 1;
        *len += 3;
        Dogs102x6_clearScreen();
    }
}


void calculateScore(void)
{
    *ptr += 100;
}


#pragma vector=PORT2_VECTOR
__interrupt void Port2_ISR(void)
{
    //
    // Context save interrupt flag before calling interrupt vector.
    // Reading interrupt vector generator will automatically clear IFG flag
    //

    switch (__even_in_range(P2IV, P2IV_P2IFG7))
    {
        // Vector  P2IV_NONE:  No Interrupt pending
        case  P2IV_NONE:
            break;

        // Vector  P2IV_P2IFG0:  P2IV P2IFG.0
        case  P2IV_P2IFG0:

            P1OUT ^= BIT0;
            if(snakeDirection != 2)
                snakeDirection = 0;

            __delay_cycles(150000);
            P2IV = ~P2IV_P2IFG0;
            break;

        // Vector  P2IV_P2IFG1:  P2IV P2IFG.1
        case  P2IV_P2IFG1:
            break;

        // Vector  P2IV_P2IFG2:  P2IV P2IFG.2
        case  P2IV_P2IFG2:
            break;

        // Vector  P2IV_P2IFG3:  P2IV P2IFG.3
        case  P2IV_P2IFG3:

            P1OUT ^= BIT0;
            if(snakeDirection != 3)
                snakeDirection = 1;

            __delay_cycles(150000);
            P2IV = ~P2IV_P2IFG3;
            break;

        // Vector  P2IV_P2IFG4:  P2IV P2IFG.4
        case  P2IV_P2IFG4:

            P1OUT ^= BIT0;
            if(snakeDirection != 0)
                snakeDirection = 2;

            __delay_cycles(150000);
            P2IV = ~P2IV_P2IFG4;
            break;

        // Vector  P2IV_P2IFG5:  P2IV P2IFG.5
        case  P2IV_P2IFG5:
            break;

        // Vector  P2IV_P2IFG1:  P2IV P2IFG.6
        case  P2IV_P2IFG6:

            P1OUT ^= BIT0;
            if(snakeDirection != 1)
                snakeDirection = 3;

            __delay_cycles(150000);
            P2IV = ~P2IV_P2IFG6;
            break;

        // Vector  P2IV_P2IFG7:  P2IV P2IFG.7
        case  P2IV_P2IFG7:
            break;

        // Default case
        default:
            break;
    }
}



// Timer0 A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)

{
    calculateScore();
    P1OUT ^= 0x01;                            // Toggle P1.0
}

