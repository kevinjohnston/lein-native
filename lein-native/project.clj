(defproject lein-native "0.1.0-SNAPSHOT"
  :description "Test project to showcase running native code from a clojure project"
  :url "http://example.com/FIXME"
  :license {:name "Eclipse Public License"
            :url "http://www.eclipse.org/legal/epl-v10.html"}
  :dependencies [[org.clojure/clojure "1.5.1"]]

  ;; this is not where leiningen expects to find native libraries for that see
  ;; jvm-opts below. This is where native libraries in jar dependencies will be
  ;; extracted to
  :native-path "%s/bin/"

  ;; build c code, then run normal compilation code
  :prep-tasks [["shell" "./build"] "javac" "compile"]

  :native-dependencies [[MyNative "libMyNative.so"]]
  :main lein-native.core

  ;; ensure compiled native binary gets added to jars (this folder and binary
  ;; will exist due to the build shell script creating the directory and the
  ;; :prep-tasks option above running that script before compilation)
  :resource-paths ["./target/bin/"]

  :java-source-paths ["src/java"]

  ;; specify the root native path as a jvm option, this could also be set with
  ;; the environment variable $LD_LIBRARY_PATH, within this directory java
  ;; expects a path like "linux/x86_64/libFoo.so"
  :jvm-opts ["-Djava.library.path=/target/bin/"]

  ;; add lein shell as dependency to hook in shell build script to lein
  :plugins [[lein-shell "0.5.0"]]
  )
