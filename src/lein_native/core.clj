(ns lein-native.core
  (:import (com.example MyNative))
  (:gen-class))

(defn -main []
  ""
  ;; Load the library libMyNative.so from somewhere on the java library path.
  (clojure.lang.RT/loadLibrary "MyNative")

  (let [;; create java object as our view
        view-wrapper (com.example.MyNative/getSingleton)
        ]
    ;; start the view layer to display and accept user input
    (doto view-wrapper (.start))
    ;;...do other clojure things...
    ))
