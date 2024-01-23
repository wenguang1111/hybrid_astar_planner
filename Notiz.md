1. Change double and float to int16 to check if runtime optimized. Hier need check the data range and potenzielle calculation which can create overflow. One way to prevent an overflow is to use higher bit data for computation and convert the value back. However, it lost its performance. What if we analysis the data range by running different szenario and then define the data type for each variable individuelly.
   So my frist task is to find a tool to record data during calculation and analysis it.
2. i created recorder.cpp in to save and write data to csv. Its singlton pattern so call the static variable like :

```cpp
Recorder::getInstance()->saveData `<double>`("Dubins::calcRSL()::e_prime[1]",e_prime[1]);
```
