#include "MyNative.h"

WINDOW *wMainScreen;
WINDOW *wTestScreen;

/**
 * initialize main window
 */
void initScreenMain()
{
  SCREENHEIGHT = LINES;//Use number of lines detected by ncurses
  SCREENWIDTH = COLS;//Use number of cols detected by ncurses

  IMAGEHEIGHT = 14;//Number of lines used by the test screen
  IMAGEWIDTH = 38;//Number of cols used by the test screen

  testX = (SCREENWIDTH / 2) - (IMAGEWIDTH / 2); //x position for test screen
  testY = (SCREENHEIGHT / 2) - (IMAGEHEIGHT / 2); //y position for test screen

  wMainScreen = newwin(SCREENHEIGHT, SCREENWIDTH, 0, 0);	// new window (height, width, x y)
  wclear(wMainScreen);						// clear window

  mvwin(wMainScreen, 0, 0);					// move window
}

/**
 * initialize test graphic
 */
void initScreenTest()
{
  wTestScreen = newpad(IMAGEHEIGHT, IMAGEWIDTH);
  resetScreenTest(DEFAULT_COLOR);
}

/**
 * Copy pads to the main window.
 */
void copyPads(){
  copywin(wTestScreen, wMainScreen, 0, 0, testY, testX, testY + IMAGEHEIGHT - 1, testX + IMAGEWIDTH - 1, 0);
}

/**
 * Resets the test pad
 */
void resetScreenTest(int testColor)
{
  wclear(wTestScreen);
  wattrset(wTestScreen, COLOR_PAIR(testColor));
  //blank lines cause mangling by ncurses in some cases, not sure why, workaround by using ------ instead
  waddstr(wTestScreen, "--------------------------------------");
  waddstr(wTestScreen, " ##      ####  ######  ###### ##   ## ");
  waddstr(wTestScreen, " ##     ##  ## ##   ## ##     ####### ");
  waddstr(wTestScreen, " ##     ##  ## ######  #####  ## # ## ");
  waddstr(wTestScreen, " ##     ##  ## ##  ##  ##     ##   ## ");
  waddstr(wTestScreen, " ######  ####  ##   ## ###### ##   ## ");
  waddstr(wTestScreen, "--------------------------------------");
  waddstr(wTestScreen, " ###### ######  ###### ##  ## ##   ## ");
  waddstr(wTestScreen, "   ##   ##   ## ##     ##  ## ####### ");
  waddstr(wTestScreen, "   ##   ######  ###### ##  ## ## # ## ");
  waddstr(wTestScreen, "   ##   ##          ## ###### ##   ## ");
  waddstr(wTestScreen, " ###### ##      ######  ####  ##   ## ");
  waddstr(wTestScreen, "--------------------------------------");
  waddstr(wTestScreen, " Enter 1-7 to change colors, q to exit");
  wclear(wMainScreen);
  copywin(wTestScreen, wMainScreen, 0, 0, testY, testX, testY + IMAGEHEIGHT - 1, testX + IMAGEWIDTH - 1, 0);
}

JNIEXPORT void JNICALL Java_com_test_MyNative_setupNative(JNIEnv *env, jobject javaobj)
{
  graphicEngineInit();
}

/**
 * Example of overloaded method syntax, this method simply refreshes the screen
 */
JNIEXPORT void JNICALL Java_com_test_MyNative_refresh__(JNIEnv *env, jobject javaobj)
{
  //refresh everything
  prefresh(wTestScreen, 0, 0, testY, testX, testY + IMAGEHEIGHT - 1, testX + IMAGEWIDTH - 1); //refresh the pad
  wrefresh(wMainScreen); //refresh the window
}

/**
 * Example of overloaded method syntax, with an int parameter, this method completely clears the screen before refreshing
 */
JNIEXPORT void JNICALL Java_com_test_MyNative_refresh__I(JNIEnv *env, jobject javaobj, int col)
{
  //clear everything on the screen
  wclear(wMainScreen);
  //copy the pads back onto the screen
  copyPads();
  //refresh everything
  prefresh(wTestScreen, 0, 0, testY, testX, testY + IMAGEHEIGHT - 1, testX + IMAGEWIDTH - 1); //refresh the pad
  wrefresh(wMainScreen); //refresh the window
}

/**
 * Cleanup ncurses. reset command may still be needed for some terminals
 */
JNIEXPORT void JNICALL Java_com_test_MyNative_finish(JNIEnv *env, jobject javaobj)
{
  endwin();	// <curses.h> reset terminal into proper non-visual mode
}

/**
 * Reads input from keyboard and returns it
 */
JNIEXPORT int JNICALL Java_com_test_MyNative_readInput(JNIEnv *env, jobject javaobj)
{
  //Keep cursor in same location
  wmove(wMainScreen, SCREENHEIGHT - 1, testX);
  //return input
  return getch();
}

JNIEXPORT void JNICALL Java_com_test_MyNative_resetScreenTest(JNIEnv *env, jobject javaobj, int testColor)
{
  //change the test screen
  resetScreenTest(testColor);
}

/**
 * Initialize n_courses
 */
void graphicEngineInit()
{
  //(void) signal(SIGINT, finish);	// <signal.h> on signal "SIGINT" call method "finish"
  (void) initscr();		// <curses.h> do initialization work
  keypad(stdscr, TRUE);		// <curses.h> enable keypad for input
  (void) nonl();			// <curses.h> disable translation return/ newline for detection of return key
  (void) cbreak();		// <curses.h> do not buffer typed characters, use at once
  (void) noecho();		// <curses.h> do not echo typed characters
  start_color();			// <curses.h> use colors
  init_pair(RED, COLOR_RED, COLOR_BLACK);		// <curses.h> define color-pair
  init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);	// <curses.h> define color-pair
  init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);	// <curses.h> define color-pair
  init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);	// <curses.h> define color-pair
  init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);	// <curses.h> define color-pair
  init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);	// <curses.h> define color-pair
  init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);	// <curses.h> define color-pair

  initScreenMain();
  initScreenTest();
  redrawwin(wMainScreen); // needed to display graphics properly at startup on some terminals
}
