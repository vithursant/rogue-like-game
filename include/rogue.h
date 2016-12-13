/*************************rogue.c****************************
Student Name: Vithursan                       Student Number:  0821795
Date: January 10th 2014                       Course Name: CIS 2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
****************************************************************************/

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UP	    1
#define DOWN	2
#define LEFT	3
#define RIGHT	4

#define DOOR '+'
#define POTION '!'
#define TREASURE '*'
#define MONSTER 'M'
#define HERO '@'
#define WEAPON ')'

/*for counting items that the hero has picked up*/
struct Items{

    int treasure;
    int weapon;
    int potion;

};


/*for use of ncurses*/
void initCurses();

/*for use of drawing the room and its contents*/
void drawRoom(char * buffer);

/*for printing messages on screen*/
void printMessage (char * s, int lineNum, int xDir);

/*for moving the cursor/hero around the board*/
void moveCursor(int dir, struct Items * hero);

/*for printing the items that the hero has picked up*/
void printItems(int lineNum, struct Items * hero);


