
To compile with support for Java use the following commands:
```bash
cd InterSpec/external_libs/SpecUtils
mkdir build
cd build
cmake -DSpecUtils_JAVA_SWIG=ON ..
make -j4
```

To then run the example Java executable, do:
```bash
cp ../swig/java_example/* .
javac -classpath .:jcommon-1.0.21.jar:jfreechart-1.0.17.jar:joda-time-2.9.jar *.java
java -Djava.library.path="./lib" -classpath .:jcommon-1.0.21.jar:jfreechart-1.0.17.jar:joda-time-2.9.jar Main
```