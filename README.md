lein-native

Example of using native code and ncurses in clojure with a leiningen project.

 
#Purpose
 
This project shows how to use JNI to call c methods in clojure.
This is done by creating a Java class, MyNative.java, that uses JNI to call c methods. Clojure then calls these java methods pernormal java interop.
The c code in this example uses ncurses to act as a viewlayer for the command line, displaying a simple screen to the terminal and handling some user inputs.

 
#Project layout

``` 
|--/c-wrapper ---- contains the c and java source code<br>
|  |--fakemake ---- script to compile c code; Change variable JDK_HOME as needed to compile on other machines<br>
|  |--/native<br>
|  |  `--/linux<br>
|  |     `--/x86_64<br>
|  |       `--libMyNative.so ---- Java requires native libaries be named in this format (extension will vary by OS)<br>
|  `--/src<br>
|     |--/native<br>
|     |  `--/linux<br>
|     |     `--/x86_64<br>
|     |        `--MyNative.c<br>
|     |        `--MyNative.h<br>
|     `--/java<br>
|        `--MyNative.java ---- in package com.test even though src folder doesn't reflect that<br>
|<br>
|--/lein-native<br>
|  |--/doc<br>
|  |--/resources<br>
|  `--/src<br>
|     |--/java ---- link to c-wrapper/src/java<br>
|     |--/lein_native ---- clojure code<br>
|     |  `--core.clj ---- the clojure code, contains the main method, imports the java code and dynamically loads the native shared library<br>
|     `--native ---- link to c-wrapper/src/native<br>
```
 
#Running the project
 
execute "lein run" in the folder lein-native

 
#Compiling C code
 
run the file "fakemake" in c-wrapper directory, some variables such as JDK_HOME will likely need to be changed

 
#Compiling Java and clojure code
 
Java: run "lein javac" in lein-native directory
Clojure: run "lein compile" in lein-native directory
or
run "lein run" in lein-native directory to compile both and run the app


 
#Dependencies
 
Name    |(Version)      | Notes
:--------|:---------------|:-----------
ncurses |(5.9)          | needed to compile c code
lein    |(2.3.4)        |  
clojure |(1.6)          | 
JDK     |(1.7)          |
g++     |(4.9)          | 
debian  |(7.2)          | 

These are versions I'm using, earlier versions for some/all will work.
