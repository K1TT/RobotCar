//======================================================================
//
// Test program to test the infrared sensors (and motors) of the
// 4tronix initio robot car. One can run this program within an
// ssh session.
//
// author: Raimund Kirner, University of Hertfordshire
//         initial version: Oct.2016
//
// license: GNU LESSER GENERAL PUBLIC LICENSE
//          Version 2.1, February 1999
//          (for details see LICENSE file)
//
// Compilation: 
// gcc -o line_follower -Wall -Werror -lcurses -lwiringPi -lpthread -linitio line_follower.c
//
//======================================================================

#include <stdlib.h>
#include <initio.h>
#include <curses.h>

//======================================================================
// line_follower():
// Simple program to test infrared line sensors:
// Drive along a black line. The black line is bordered on both sides
// with a white line to ensure contrast for the line sensors.
//======================================================================
void line_follower(int argc, char *argv[]) 
{
  int ch = 0;
  int irL,irR;	// status of infrared sensors
  int lfL,lfR;	// status of line sensors

  // initio_DriveForward (... ); // todo: Initially, try to drive straight forward

  while (ch != 'q') {
    mvprintw(1, 1,"%s: Press 'q' to end program", argv[0]);

    irL = initio_IrLeft();
    irR = initio_IrRight();
    lfL = 0; // todo: replace by read left line sensor
    lfR = 0; // todo: replace by read right line sensor

    if (irL != 0 || irR != 0) {
      mvprintw(3, 1,"Action: Stop (IR sensors: %d, %d)     ", irL, irR);
      initio_DriveForward (0); // Stop
    }
    // no obstacle ahead, so focus on line following
    else if ( 1 /* todo: change */) { 
      mvprintw(3, 1,"Action: Straight (Line sensors: %d, %d)    ", lfL, lfR);
      // todo: move straight forward
    }
    else if ( 1 /* todo: change */ ) {
      // car is too much on the right
      mvprintw(3, 1,"Action: Spin left (Line sensors: %d, %d)    ", lfL, lfR);
      // todo: turn left
    }
    else if ( 1 /* todo: change */ ) {
      // car is too much on the left
      mvprintw(3, 1,"Action: Spin right (Line sensors: %d, %d)    ", lfL, lfR);
      // todo: turn right
    }
    else {
      mvprintw(3, 1,"Lost my line (Line sensors: %d, %d)        ", lfL, lfR);
      // todo: Stop
    }

    ch = getch();
    if (ch != ERR)
      mvprintw(2, 1,"Key code: '%c' (%d)", ch, ch);
    refresh();
  } // while

  return;
}


//======================================================================
// main(): initialisation of libraries, etc
//======================================================================
int main (int argc, char *argv[])
{
  WINDOW *mainwin = initscr();  // curses: init screen
  noecho ();                    // curses: prevent the key being echoed
  cbreak();                     // curses: disable line buffering 
  nodelay(mainwin, TRUE);       // curses: set getch() as non-blocking 
  keypad (mainwin, TRUE);       // curses: enable detection of cursor and other keys

  initio_Init (); // initio: init the library

  line_follower(argc, argv);

  initio_Cleanup ();  // initio: cleanup the library (reset robot car)
  endwin();           // curses: cleanup the library
  return EXIT_SUCCESS;
}

