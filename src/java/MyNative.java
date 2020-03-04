package com.example;

/**
 *  Java wrapper class for native methods. Once created via getSingleton, the
 *  start method will begin the viewlayer display.
 */
public class MyNative {
  ///////////////////////////////////////////////////////
  ///// Native methods
  ///////////////////////////////////////////////////////
  public native void setupNative();
  public native void refresh();
  public native void refresh(int col);
  public native void finish();
  public native int  readInput();
  public native void changeColor(int textColor);

  ///////////////////////////////////////////////////////
  ///// Constants
  ///////////////////////////////////////////////////////
  public static int QUIT_KEY='q';
  public static volatile boolean RUNNING=false;

  ///////////////////////////////////////////////////////
  ///// Variables
  ///////////////////////////////////////////////////////
  private Thread uiThread;
  private Thread inputThread;

  // Singleton object
  private static MyNative viewLayer;

  ///////////////////////////////////////////////////////
  ///// Constructor
  ///////////////////////////////////////////////////////
  private MyNative(){
    //setup
    setupThreads();
    setupSignalHooks();
    setupNative();
  }

  ///////////////////////////////////////////////////////
  ///// Public api
  ///////////////////////////////////////////////////////
  public static MyNative getSingleton(){
    if (viewLayer == null)
      viewLayer = new MyNative();
    return viewLayer;
  }

  public void start(){
    RUNNING = true;
    uiThread.start();
    inputThread.start();
  }

  /**
   * Calls method appropriate for user input.
   */
  public void handleUserInput(int input){
    if(input > '0' && input < '8')
      changeColor(input - '0');
    else if(input == 'q')
      quit();
    else
      // hard refresh for unexpected characters so they wont show up on screen
      refresh(0);
  }

  /**
   * If the jvm exits for any reason also cleanup the view.
   */
  public void quit(){
    //Call native method to end ncurses.
    RUNNING = false;
    finish();
  }

  ///////////////////////////////////////////////////////
  ///// Private api
  ///////////////////////////////////////////////////////
  /**
   * Create UI and user input threads via anonymous classes
   */
  private void setupThreads(){
    uiThread = new Thread(){
        public void run(){
          int startupTime = 600;
          int sleepTime = 25;
          while (RUNNING){
            if (startupTime > 0){
              startupTime -= sleepTime;
              MyNative.getSingleton().refresh(1);
            }
            try{
              MyNative.getSingleton().refresh();
              Thread.sleep(sleepTime);
            }catch(Exception e){
              e.printStackTrace(System.out);
            }
          }
        }
      };
    inputThread = new Thread(){
        public void run(){
          while (RUNNING)
            MyNative.getSingleton().handleUserInput(readInput());
        }
      };
  }

  /**
   * Handle signals
   */
  private void setupSignalHooks(){
    Thread shutdownHook = new Thread(){
        public void run(){
          MyNative.getSingleton().quit();
        }
      };
    Runtime.getRuntime().addShutdownHook(shutdownHook);
  }
}
