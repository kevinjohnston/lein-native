(ns lein-native.core
  (:import (com.test MyNative)))

(defn -main []
  ""
  ;;Load the library libMyNative.so from somewhere on the java library path above.
  (clojure.lang.RT/loadLibrary "MyNative")

  (let [view-wrapper (com.test.MyNative/getSingleton) ;;create java object as our view
        ]
    (doto view-wrapper (.start)) ;;start the view layer to display and accept user input
    ;;...do other clojure things...
    )
  )
