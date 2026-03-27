// Calculator.cpp
#include <Arduino.h>
#include "Calculator.h"

#include <array>
#include <cmath>

constexpr int calc(int i) {
    return static_cast<int>(1000 * sin(i * M_PI / 180.0));
}

constexpr std::array<int, 90> makeTable() {
    std::array<int, 90> table = {};
    for (int i = 0; i < 90; i++) {
        table[i] = calc(i);
    }
    return table;
}

constexpr auto sinTable = makeTable();

int sinIntDegrees(int degrees) {
	// Convert degrees to radians
	float radians = degrees * (PI / 180.0);
	// Calculate sine value and scale it to an integer range (e.g., -1000 to 1000)
	int sineValue = (int)(sin(radians) * 1000.0);
	return sineValue;
}