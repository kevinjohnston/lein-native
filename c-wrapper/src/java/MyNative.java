package com.test;

/**
 *  Java wrapper class for native methods. Once created via getSingleton, the start method will begin the viewlayer display.
 */
public class MyNative {
    //NATIVE METHODS
    public native void setupNative();
    public native void refresh();
    public native void refresh(int col);
    public native void finish();
    public native int readInput();
    public native void resetScreenTest(int testColor);

    //CONSTANTS
    public static int QUIT_KEY='q';
    public static volatile boolean RUNNING=false;

    private Thread uiThread;
    private Thread inputThread;

    //Singleton object
    private static MyNative viewLayer;

    public static MyNative getSingleton(){
        if (viewLayer == null)
            viewLayer = new MyNative();
        return viewLayer;
    }

    private MyNative(){
        //setup
        setupThreads();
        setupSignalHooks();
        setupNative();
    }

    public void start(){
        RUNNING = true;
        uiThread.start();
        inputThread.start();
    }

    /**
     *  Calls method appropriate for user input.
     */
    public void handleUserInput(int input){
        if(input > '0' && input < '8')
            resetScreenTest(input - '0');
        else if(input == 'q')
            quit();
        else //hard refresh for unexpected characters so the wont show up on screen
            refresh(0);
    }

    /**
     *  Handle closing view layer.
     */
    public void quit(){
        //Call native method to end ncurses.
        RUNNING = false;
        try{
            Thread.sleep(200);
        }catch(Exception e){
            e.printStackTrace(System.out);
        }
	finish();
    }

    /**
     * Create UI and user input threads via anonymous classes
     */
    private void setupThreads(){
        uiThread = new Thread(){
                public void run(){
                    while (RUNNING){
                        try{
                            Thread.sleep(25);
                        }catch(Exception e){
                            e.printStackTrace(System.out);
                        }
                        MyNative.getSingleton().refresh();
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
     * Handle kill signal
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
