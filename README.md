lein-native
==========

Example of using native code and ncurses in clojure with a leiningen project via JNI.

## Project layout

```
/lein-native
|--build ---- script to compile c code; set JAVA_HOME as needed to compile on other machines
|--/doc
|--/resources
|--/src
|  |--/java
|  |  `--MyNative.java ---- wrapper for C code
|  |--/lein_native ---- clojure code
|  |  `--core.clj ---- contains main, imports the java code and dynamically loads the native shared library
|  `--native ---- native source code
|     `--/linux
|        `--/x86_64
|           `--MyNative.c -- native code calling ncurses
|           `--MyNative.h
`--/target
   `--/bin
      `--/linux
         `--/x86_64
            `--libMyNative.so ---- Java requires native libaries be named in this format (extension will vary by OS)
```

## Running the project

execute `lein run` to compile (everything) and run

OR
```
lein uberjar
java -Djava.library.path=./target/bin/linux/x86_64/ -jar ./target/lein-native-0.1.0-SNAPSHOT-standalone.jar
```

## Compiling
#### Clojure:
run "lein compile"
##### note
this will also compile the java and c code
#### C:
run "build"
#### Java:
run "lein javac"

## Dependencies

 Name    |(Version)      | Notes
:--------|:--------------|:-----------
 ncurses |(5.9)          | needed to compile c code
 lein    |(2.3.4)        |
 clojure |(1.6)          |
 JDK     |(1.7)          |
 g++     |(4.9)          |
 debian  |(7.2)          |

