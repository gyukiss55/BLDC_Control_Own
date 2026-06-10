// FibonacciTest.cpp

#include "FibonacciTest.h"

uint64_t fib(uint32_t n) {
    if (n < 2) {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}

void FibonacciTest()
{
    uint64_t fibonacci = 1;
    //log_d("Starting fibonacci calculation");
    Serial.print("Runs:");
    Serial.println(N_RUNS);

    Serial.print("N: ");
    Serial.println(FIB_N);
    //Serial.flush();
    for (int i = 0; i < N_RUNS; i++) {
        Serial.print("Run ");
        Serial.println(i);
        unsigned long start = millis();
        fibonacci = fib(FIB_N);
        unsigned long elapsed = millis() - start;
        Serial.print("Fibonacci(N): ");
        Serial.println(fibonacci);
        Serial.print("Time: ");
        Serial.print(elapsed / 1000);
        Serial.print(".");
        Serial.print(elapsed % 1000);
        Serial.println(" seconds");
        //Serial.flush();
    }

    //log_d("Fibonacci calculation test done");
}

void FibonacciTest(int n_run, int n_fib, String& log)
{
    uint64_t fibonacci = 1;
    //log_d("Starting fibonacci calculation");
    log = "Runs:" + String(n_run) + " N: " + String(n_fib) + "\n";
    for (int i = 0; i < N_RUNS; i++) {
        log += "Run " + String(i);
        unsigned long start = millis();
        fibonacci = fib(FIB_N);
        unsigned long elapsed = millis() - start;
        log += " Fibonacci(N):" + String(fibonacci) + "Time:" + String(elapsed / 1000) + "." + String(elapsed % 1000) + " seconds\n";

    }

    //log_d("Fibonacci calculation test done");
}
