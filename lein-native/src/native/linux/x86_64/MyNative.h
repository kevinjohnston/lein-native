#include <ncurses.h> //used to display information to terminal
#include <jni.h> //Java Native Interface header

#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define CYAN 5
#define MAGENTA 6
#define WHITE 7

#define DEFAULT_COLOR 4

int SCREENHEIGHT;
int SCREENWIDTH;
int IMAGEHEIGHT;
int IMAGEWIDTH;

int testX;
int testY;

/* Header for class MyNative */

#ifndef _Included_MyNative
#define _Included_MyNative
#ifdef __cplusplus
extern "C" {
#endif

  void initScreenMain();
  void initScreenTest();
  void copyPads();
  void resetScreenTest(int);
  JNIEXPORT void JNICALL Java_com_test_MyNative_setupNative(JNIEnv *, jobject);
  JNIEXPORT void JNICALL Java_com_test_MyNative_refresh__(JNIEnv *, jobject);
  JNIEXPORT void JNICALL Java_com_test_MyNative_refresh__I(JNIEnv *, jobject, int);
  JNIEXPORT void JNICALL Java_com_test_MyNative_finish(JNIEnv *, jobject);
  JNIEXPORT int JNICALL Java_com_test_MyNative_readInput(JNIEnv *, jobject);
  JNIEXPORT void JNICALL Java_com_test_MyNative_resetScreenTest(JNIEnv *, jobject, int);
  void graphicEngineInit();

#ifdef __cplusplus
}
#endif
#endif
