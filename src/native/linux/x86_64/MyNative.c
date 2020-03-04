#include "MyNative.h"

/**
 * Initialize main window
 */
void initMain()
{
  // Use lines and columns detected by ncurses
  SCREENHEIGHT = LINES;
  SCREENWIDTH = COLS;

  IMAGEHEIGHT = 14;
  IMAGEWIDTH = 38;

  // top left x and y positions for text to display
  X = (SCREENWIDTH / 2) - (IMAGEWIDTH / 2);
  Y = (SCREENHEIGHT / 2) - (IMAGEHEIGHT / 2);

  // new window (height, width, x y)
  wMain = newwin(SCREENHEIGHT, SCREENWIDTH, 0, 0);

  // clear window
  wclear(wMain);

  // move window
  mvwin(wMain, 0, 0);
}

/**
 * Initialize example text
 */
void initNext()
{
  wNext = newpad(IMAGEHEIGHT, IMAGEWIDTH);
  resetPadNext(DEFAULT_COLOR);
}

/**
 * Example signal handler
 */
void finish(int signal)
{
  endwin();
}

/**
 * Copy pads to the main window.
 */
void copyPads(){
  // since the displayed view is not decomposed into multiple sections only
  // one copy needs to be made, for more complicated screens multiple sections
  // would be copied over here
  copywin(wNext, wMain, 0, 0, Y, X, Y + IMAGEHEIGHT - 1, X + IMAGEWIDTH - 1, 0);
}

/**
 * Resets the pad used to draw the next main screen
 */
void resetPadNext(int textColor)
{
  wclear(wNext);
  wattrset(wNext, COLOR_PAIR(textColor));
  // blank lines cause mangling by ncurses in some cases, not sure why,
  // workaround by using ------ instead
  waddstr(wNext, "--------------------------------------");
  waddstr(wNext, " ##      ####  ######  ###### ##   ## ");
  waddstr(wNext, " ##     ##  ## ##   ## ##     ####### ");
  waddstr(wNext, " ##     ##  ## ######  #####  ## # ## ");
  waddstr(wNext, " ##     ##  ## ##  ##  ##     ##   ## ");
  waddstr(wNext, " ######  ####  ##   ## ###### ##   ## ");
  waddstr(wNext, "--------------------------------------");
  waddstr(wNext, " ###### ######  ###### ##  ## ##   ## ");
  waddstr(wNext, "   ##   ##   ## ##     ##  ## ####### ");
  waddstr(wNext, "   ##   ######  ###### ##  ## ## # ## ");
  waddstr(wNext, "   ##   ##          ## ###### ##   ## ");
  waddstr(wNext, " ###### ##      ######  ####  ##   ## ");
  waddstr(wNext, "--------------------------------------");
  waddstr(wNext, " Enter 1-7 to change colors, q to exit");
}


void refreshScreens(int clear)
{
  // clear everything on the screen
  if (clear > 0)
    wclear(wMain);

  copyPads();

  // move the cursor position
  wmove(wMain, SCREENHEIGHT - 1, 0);

  ///// refresh everything
  // refresh the pad (not actually necessary)
  //prefresh(wNext, 0, 0, Y, X, Y + IMAGEHEIGHT - 1, X + IMAGEWIDTH - 1);
  // refresh the window
  wrefresh(wMain);
}

JNIEXPORT void JNICALL Java_com_example_MyNative_setupNative(JNIEnv *env, jobject javaobj)
{
  graphicEngineInit();
}

/**
 * Example of overloaded method syntax.
 * This method refreshes the screen.
 */
JNIEXPORT void JNICALL Java_com_example_MyNative_refresh__(JNIEnv *env, jobject javaobj)
{
  refreshScreens(0);
}

/**
 * Example of overloaded method syntax with an int parameter.
 * This method completely clears the screen before refreshing.
 */
JNIEXPORT void JNICALL Java_com_example_MyNative_refresh__I(JNIEnv *env,
                                                            jobject javaobj,
                                                            int clear)
{
  refreshScreens(clear);
}

/**
 * Cleanup ncurses. reset command may still be needed for some terminals
 */
JNIEXPORT void JNICALL Java_com_example_MyNative_finish(JNIEnv *env,
                                                        jobject javaobj)
{
  endwin(); // reset terminal into proper non-visual mode
}

/**
 * Reads input from keyboard and returns it
 */
JNIEXPORT int JNICALL Java_com_example_MyNative_readInput(JNIEnv *env,
                                                          jobject javaobj)
{
  // Keep cursor in same location
  wmove(wMain, SCREENHEIGHT - 1, X);
  // return input
  return getch();
}

JNIEXPORT void JNICALL Java_com_example_MyNative_changeColor(JNIEnv *env,
                                                             jobject javaobj,
                                                             int textColor)
{
  // change the next pad
  resetPadNext(textColor);
  refreshScreens(1);
}

/**
 * Initialize n_curses, set callbacks, and setup initial screens
 */
void graphicEngineInit()
{
  // signal callbacks
  (void) signal(SIGINT, finish); // on signal "SIGINT" call method "finish"

  // configuration via ncurses api, see <curses.h>
  (void) initscr();      // do initialization work
  keypad(stdscr, TRUE);  // enable keypad for input
  (void) nonl();         // disable translation return/ newline for detection of return key
  (void) cbreak();       // do not buffer typed characters, use at once
  (void) noecho();       // do not echo typed characters
  start_color();         // use colors

  // use ncurses api to define color-pairs
  // e.g. associate RED with forground RED and background BLACK
  init_pair(RED, COLOR_RED, COLOR_BLACK);
  init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
  init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
  init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
  init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
  init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);

  // setup screens
  initMain();
  initNext();
  refreshScreens(0);

  // needed to display graphics properly at startup on some terminals
  redrawwin(wMain);
}
