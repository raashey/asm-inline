# asm-inline

This is program which I had to write on Computer Architecture laboratory. 
It required knowledge about SIMD architecture and SISD architecture. 
I did my tests on float type data, because it was a bit easier to implement on
SISD architecture. Measurement of time of different functions was executed by clock_t type from time.h library. It returns number of clock ticks
elapsed since the program was launched. After dividing it by constant 
CLOCK_PER_SEC, you'll get time in seconds unit.
