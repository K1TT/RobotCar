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
  //int irL,irR;	// status of infrared sensors
  int lfL,lfR;	// status of line sensors
  //int time=0, last_time=0;
  //int bled=0;

  // initio_DriveForward (... ); // todo: Initially, try to drive straight forward
  pinMode (37, OUTPUT) ; // set Pin 37 to output mode
  
  // CUSTOM TO DO LIST
  // - Modify Initio library to output sensor data to be used to collect data
  // - Adjust values and if statements to make software more efficient

  while (ch != 'q') {
    mvprintw(1, 1,"%s: Press 'q' to end program", argv[0]);

    //irL = initio_IrLeft();
    //irR = initio_IrRight();
    lfL = initio_IrLineLeft();
    lfR = initio_IrLineRight();

	digitalWrite (37, 0);

    /*if (irL != 0 || irR != 0) {
      mvprintw(3, 1,"Action: Stop (IR sensors: %d, %d)     ", irL, irR);
      initio_DriveForward (0); // StopWall -Werror -mfloat-abi=hard -linitio -lcurses -lwiringPi -lpthread line_follower.c
esd36@navio-rpi:~/LineFollow2$ sudo ./line_follower
esd36@navio-rpi:~/LineFollow2$ make line_follower
gcc -o line_follower -Wall -Werror -mfloat-abi=hard -linitio -lcurses -lwiringPi -lpthread line_follower.c
esd36@navio-rpi:~/LineFollow2$ sudo ./line_follower
esd36@navio-rpi:~/LineFollow2$ make line_follower
gcc -o line_follower -Wall -Werror -mfloat-abi=hard -linitio -lcurses -lwiringPi -lpthread line_follower.c
esd36@navio-rpi:~/LineFollow2$ sudo ./line_follower
esd36@navio-rpi:~/LineFollow2$ make l
    }*/
    // no obstacle ahead, so focus on line following
    if (lfL == 0 && lfR == 0) { 
      mvprintw(3, 1,"Action: Straight (Line sensors: %d, %d)    ", lfL, lfR);
	  initio_DriveForward(70);
    }
	else if(lfR !=0 && lfL !=0){
		mvprintw(3, 1,"Action: Backwards (Line sensors: %d, %d)    ", lfL, lfR);
		initio_DriveReverse(70);
	}
    else if (lfR != 0) {
      // car is too much on the right
      mvprintw(3, 1,"Action: Spin left (Line sensors: %d, %d)    ", lfL, lfR);
	digitalWrite (37, 1);
	initio_SpinLeft(100);
	//initio_DriveForward(0);
	//initio_TurnForward(60, 30);
	
    }
    else if (lfL != 0) {
      // car is too much on the left
      mvprintw(3, 1,"Action: Spin right (Line sensors: %d, %d)    ", lfL, lfR);
	digitalWrite (37, 1);
	initio_SpinRight(100);
	//initio_TurnForward(30, 60);
    }
    else {
      mvprintw(3, 1,"Lost my line (Line sensors: %d, %d)        ", lfL, lfR);
      initio_DriveForward(0);
    }

/*
    time = millis();
    if (time > last_time+500) {
      bled = !bled;
      digitalWrite (37, bled);  // set Pin 37 to current value
      last_time = time;
    }
*/
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

