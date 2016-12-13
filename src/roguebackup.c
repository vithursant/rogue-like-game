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


void initCurses() {
  initscr ();
  cbreak ();
  noecho ();
  keypad (stdscr, TRUE);

}


void drawRoom(char * room){



    char * roomSize;            /*for storing the room size*/
    char *roomXTok, *roomYTok;  /*tokens of room's dimensions*/
    int roomX, roomY;           /*rooms dimensions*/
    int i,j,k,l;
    char * endPtr = NULL;

    char * roomCpy;             /*copy of the string of the room*/
    char * roomInfo;            /*for storing info about the room*/
    char * object;              /*for placing objects in the room*/
    int doorPos;                /*door coordinate for a wall*/

    int xCoordinate, yCoordinate;   /*x,y coordinates for placing objects*/
    int heroX, heroY;               /*x,y, coordinates for placing hero*/

    /*creates an array for the room and the objects*/
    object = malloc(sizeof(char)*7);
    roomCpy = malloc(sizeof(char)*150);


    strcpy(roomCpy, room);

    roomSize = strtok(room, " ");

    roomYTok = strtok(roomSize, "X");
    roomXTok = strtok(NULL, "X");
    roomY = (int)strtol(roomYTok,&endPtr,10);
    roomX = (int)strtol(roomXTok,&endPtr,10);

    /*draws thr room with the walls*/
       for(i=0;i<roomX;i++){
            mvaddch(0,i,'-');
            mvaddch(roomY-1,i,'-');
        }
       for(j=0;j<roomY;j++){
            mvaddch(j,0,'|');
            mvaddch(j,roomX,'|');

        }

        for(k=0;k<roomY-2;k++){
            for(l=0;l<roomX-1;l++)
                mvaddch(k+1,l+1,'.');
        }

        roomInfo = strtok(roomCpy, " ");

        /*goes through string to place objects in room until the string reaches null*/

        do{


                roomInfo = strtok(NULL," ");

                strcpy(object,roomInfo);
                /*places the doors*/
                if(object[0] == 'd'){

                    doorPos = (int)strtol(&object[2],&endPtr,10);

                    if(object[1] == 'e'){
                        mvaddch(doorPos,roomX, DOOR);
                    }
                    if(object[1] == 'w'){
                        mvaddch(doorPos,0, DOOR);
                    }
                    if(object[1] == 'n'){
                        mvaddch(0,doorPos,DOOR);
                    }
                    if(object[1] == 's'){
                        mvaddch(roomY-1,doorPos, DOOR);
                    }
                }

                else{
                    /*converts the object coordinates to ints to place that object*/
                    xCoordinate = (int)strtol(&object[1],&endPtr,10);
                    if(object[3] == ',')
                        yCoordinate = (int)strtol(&object[4],&endPtr,10);
                    else
                        yCoordinate = (int)strtol(&object[3],&endPtr,10);
                    /*placing objects*/
                    if(object[0] == 'h'){
                        mvaddch(yCoordinate, xCoordinate,HERO);
                        heroX = xCoordinate;
                        heroY = yCoordinate;
                    }
                    else if(object[0] == 't')
                        mvaddch(yCoordinate,xCoordinate,TREASURE);
                    else if(object[0] == 'p')
                        mvaddch(yCoordinate,xCoordinate,POTION);
                    else if(object[0] == 'm')
                        mvaddch(yCoordinate,xCoordinate,MONSTER);
                    else if(object[0] == 'w')
                        mvaddch(yCoordinate,xCoordinate,WEAPON);

                }

             move(heroY,heroX);

        }while(object[4] != '\n' && object[5] != '\n' && object[6] != '\n' );/*exits loop when string reaches newline*/


        free(object);
        free(roomCpy);


}



void printMessage (char * s, int lineNum)
{
    int x, y;

    getyx(stdscr, y, x);/*gets the cursor position*/

    /*prints the message on the line indicated plus 10 lines so not to interfere with gameboard*/
    mvwprintw (stdscr, 33+lineNum, 0, s );

    move(y, x);/*move cursor back to original position before outputting message*/
    refresh ();/*Refresh the display*/
}

void printItems (int lineNum, struct Items * hero)
{
    int x, y;

    getyx(stdscr, y, x);/*gets the cursor position*/

    /*prints the heros items on the line indicated plus 30 lines so not to interfere with gameboard*/
    mvprintw (30+lineNum, 0, "Gold: %d ", hero->treasure);
    mvprintw (31+lineNum, 0, "Nazerath Potions: %d ", hero->potion);
    mvprintw (32+lineNum, 0, "Weapons(Kobold Swords): %d ", hero->weapon);


    move(y, x);/*move cursor back to original position before outputting message*/
    refresh ();/*Refresh the display*/
}


void  moveCursor(int dir, struct Items * hero){

    int x, y;

    /*get cursor position*/
    getyx(stdscr, y, x);


    /*If defined constant is where the user
      wants to go, add/subtract one to respective
      coordinate*/

    if(dir == RIGHT){
        /*restricts movement from walking over walls and monsters*/
        if(mvinch(y,x+1) == '|' || mvinch(y,x+1) == DOOR || mvinch(y,x+1) == MONSTER){
            move(y,x);
        }
        else{
            if(mvinch(y,x+1) == TREASURE) /*picks up treasure,potion, weapon if walked over*/
                hero->treasure += 5;
            else if(mvinch(y,x+1) == POTION)
                hero->potion += 1;
            else if(mvinch(y,x+1) == WEAPON)
                hero->weapon += 1;
            mvaddch(y,x+1,HERO);
            mvaddch(y,x,'.');
            move(y,x+1);
        }
    }
    if(dir == LEFT){

        if(mvinch(y,x-1) == '|' || mvinch(y,x-1) == DOOR || mvinch(y,x-1) == MONSTER){
            move(y,x);
        }
        else{
             if(mvinch(y,x-1) == TREASURE)
                hero->treasure += 5;
            else if(mvinch(y,x-1) == POTION)
                hero->potion += 1;
            else if(mvinch(y,x-1) == WEAPON)
                hero->weapon += 1;
            mvaddch(y,x-1,HERO);
            mvaddch(y,x,'.');
            move(y,x-1);
        }
    }
    if(dir == UP){

        if(mvinch(y-1,x) == '-' || mvinch(y-1,x) == DOOR || mvinch(y-1,x) == MONSTER){
            move(y,x);
        }
        else{
            if(mvinch(y-1,x) == TREASURE)
                hero->treasure += 5;
            else if(mvinch(y-1,x) == POTION)
                hero->potion += 1;
            else if(mvinch(y-1,x) == WEAPON)
                hero->weapon += 1;
            mvaddch(y-1,x,HERO);
            mvaddch(y,x,'.');
            move(y-1,x);
        }
    }
    if(dir == DOWN){

        if(mvinch(y+1,x) == '-' || mvinch(y+1,x) == DOOR || mvinch(y+1,x) == MONSTER){
            move(y,x);
        }
        else{
            if(mvinch(y+1,x) == TREASURE)
                hero->treasure += 5;
            else if(mvinch(y+1,x) == POTION)
                hero->potion += 1;
            else if(mvinch(y+1,x) == WEAPON)
                hero->weapon += 1;
            mvaddch(y+1,x,HERO);
            mvaddch(y,x,'.');
            move(y+1,x);
        }
    }


    /*Refresh the display*/
    refresh();
}
