(defproject lein-native "0.1.0-SNAPSHOT"
  :description "FIXME: write description"
  :url "http://example.com/FIXME"
  :license {:name "Eclipse Public License"
            :url "http://www.eclipse.org/legal/epl-v10.html"}
  :dependencies [[org.clojure/clojure "1.5.1"]]
  :native-path "src/native" ;;this is not where leiningen expects to find native libraries for that see jvm-opts below. This is where native libraries in jar dependencies will be extracted to
  :native-dependencies [[MyNative "libMyNative.so"]]
  :main lein-native.core
  :java-source-paths ["src/java"]
  :jvm-opts ["-Djava.library.path=src/native"];;specify the root native path as a jvm option, this could also be set with the environment variable $LD_LIBRARY_PATH, within this directory java expects a path like "linux/x86_64/libFoo.so"
  )
