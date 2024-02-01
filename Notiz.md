1. Change double and float to int16 to check if runtime optimized. Hier need check the data range and potenzielle calculation which can create overflow. One way to prevent an overflow is to use higher bit data for computation and convert the value back. However, it lost its performance. What if we analysis the data range by running different szenario and then define the data type for each variable individuelly.
   So my frist task is to find a tool to record data during calculation and analysis it.
2. i created recorder.cpp in to save and write data to csv. Its singlton pattern so call the static variable like :

```cpp
Recorder::getInstance()->saveData `<double>`("Dubins::calcRSL()::e_prime[1]",e_prime[1]);
```


## 01.02.2024

I used Recorder class to record value of variables, analyzed value and define the variables with data Type which avoids Overflow problems. I use [CNL Lib](https://github.com/johnmcfarlane/cnl) to deliver fixed point data type, which allow me manuelly define the size of fractional part. I use Tool/CNL_Test.cpp to test the lib. There is coment in this file for command to compile the program. 

Parameter "USE_RECORDER" is defined in CMakeLists to make user ez to turn off/on record function. When the hybrid_astar.s lib is compiled, use HybridAStar/hybrid_astar.py to start the simulation and three markdown files will be created to record data in different data types. Use too/analyzer.py to analyze data range of each variable.
