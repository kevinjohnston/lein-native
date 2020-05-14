FROM debian:buster

MAINTAINER Kevin

# Update and install dependencies from debian
RUN apt-get update  && \
  apt-get install -y git default-jdk wget g++ libncurses5-dev libncursesw5-dev

# download github repo
RUN git clone https://bitbucket.org/kljohnston/lein-native.git /root/lein-native

# Install lein (a build tool for clojure)
RUN wget https://raw.githubusercontent.com/technomancy/leiningen/stable/bin/lein \
    -O /bin/lein && chmod +x /bin/lein && /bin/lein

# Set java home, required to find jni c libraries for compilation
ENV JAVA_HOME /usr/lib/jvm/java-11-openjdk-amd64/

# compile lein-native
WORKDIR /root/lein-native/
RUN lein uberjar

# Start in shell
ENTRYPOINT ["java", "-Djava.library.path=./target/bin/linux/x86_64/", "-jar", "./target/lein-native-0.1.0-SNAPSHOT-standalone.jar"]
