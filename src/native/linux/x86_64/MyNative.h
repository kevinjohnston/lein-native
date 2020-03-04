#include <ncurses.h> //used to display information to terminal
#include <jni.h> //Java Native Interface header
#include <signal.h> //Java Native Interface header

#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define CYAN 5
#define MAGENTA 6
#define WHITE 7

#define DEFAULT_COLOR BLUE

#define SIGINT 2

int SCREENHEIGHT;
int SCREENWIDTH;
int IMAGEHEIGHT;
int IMAGEWIDTH;

int X;
int Y;

// the screen a user will see
WINDOW *wMain;
// the pad text can be drawn to in preparation for displaying to the user
WINDOW *wNext;

/* Header for class MyNative */

#ifndef _Included_MyNative
#define _Included_MyNative
#ifdef __cplusplus
extern "C" {
#endif

  void initMain();
  void initNext();
  void copyPads();
  void finish();
  void resetPadNext(int);
  void refreshScreens(int);
  JNIEXPORT void JNICALL Java_com_example_MyNative_setupNative(JNIEnv *, jobject);
  JNIEXPORT void JNICALL Java_com_example_MyNative_refresh__(JNIEnv *, jobject);
  JNIEXPORT void JNICALL Java_com_example_MyNative_refresh__I(JNIEnv *, jobject, int);
  JNIEXPORT void JNICALL Java_com_example_MyNative_finish(JNIEnv *, jobject);
  JNIEXPORT int  JNICALL Java_com_example_MyNative_readInput(JNIEnv *, jobject);
  JNIEXPORT void JNICALL Java_com_example_MyNative_changeColor(JNIEnv *, jobject, int);
  void graphicEngineInit();

#ifdef __cplusplus
}
#endif
#endif
