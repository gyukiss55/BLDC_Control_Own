// FibonacciTest.h
#include <Arduino.h>

// Number of runs to average
#define N_RUNS 3

#define LED_PIN 8

// Fibonacci number to calculate. Keep between 35 and 45.
#define FIB_N 35

uint64_t fib(uint32_t n);
void FibonacciTest();
void FibonacciTest(int n_run, int n_fib, String& log);