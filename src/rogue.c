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



#include "rogue.h"



int main(int argc, char * argv[]){


    if(argc != 2){printf("Incorrect number of arguments\n"); exit(0);}/*exits if incorrect number of input files*/

    int dir,i,j;  /*direction for cursor, and counters for for loops*/
    char * msg;   /*for assigning messages*/
    int inputChar;/*for taking input*/
    char * room;  /*for getting room info from string*/



    FILE * infile;
    room = malloc(sizeof(char)*150);

    /*assigns initial values of variables for the items in struct*/
    struct Items * hero;

    hero = malloc(sizeof(struct Items));
    hero->treasure = 0;
    hero->weapon = 0;
    hero->potion = 0;

    /*reads in the input file*/
    infile = fopen(argv[1],"r");
    if (infile == NULL) {printf ("error opening file\n"); exit(0);}


    initCurses();

    printItems(1,hero);   /*prints hero's  current items*/

    while(fgets(room,150,infile) != NULL && inputChar != 'q'){ /*pressing q will exit*/

        /*clears board*/
        for(i=0;i<=30;i++){
            for(j=0;j<=30;j++)
                mvaddch(i,j,' ');
        }


        /*reads lines for the file*/
        /*fgets(room, 150, infile);*/


        drawRoom(room);

        /*for moving cursor/hero*/
        do{

            inputChar = getch();
            msg = "                             ";
            printMessage(msg,1,0);

            switch (inputChar) {
                case 'l': dir = RIGHT;break;
                case 'j': dir = LEFT;break;
                case 'i': dir = UP;break;
                case 'k': dir = DOWN;break;
                case 'n': break;
                default:
                    dir = -1;
                    msg = "Invalid keystroke, try again.";
                    printMessage(msg, 1,0);
                    break;

             }

               moveCursor(dir,hero); /*call function to move the cursor*/
               printItems(1,hero);   /*prints hero's  current items*/



            }while(inputChar != 'n' && inputChar != 'q');


    }

    for(i=0;i<=30;i++){
            for(j=0;j<=30;j++)
                mvaddch(i,j,' ');
        }

    move(0,0);
    msg = "Congratulations! You have raided the rooms! Press 'q' to quit";
    printMessage(msg,1,0);

    do{
        inputChar = getch();
    }
    while(inputChar != 'q');


        free(room);
        free(hero);
        endwin();


    return(0);
}
