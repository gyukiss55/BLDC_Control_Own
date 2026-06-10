// MorseLed.cpp
#include <Arduino.h>
#include "MorseLed.h"

// Morse timing (ms)
const int dotTime = 300;
const int dashTime = dotTime * 3;
const int symbolGap = dotTime;
const int letterGap = dotTime * 3;
const int wordGap = dotTime * 7;

// Morse table (A-Z, 0-9)
static const String morseTable[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
  "..-", "...-", ".--", "-..-", "-.--", "--..",
  "-----", ".----", "..---", "...--", "....-", ".....",
  "-....", "--...", "---..", "----."
};

static char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

MorseLed::MorseLed() : ledPin(-1)
{
}

MorseLed::~MorseLed()
{
}

void MorseLed::dot() const {
	digitalWrite(ledPin, LOW);
	delay(dotTime);
	digitalWrite(ledPin, HIGH);
	delay(symbolGap);
}

void MorseLed::dash() const {
	digitalWrite(ledPin, LOW);
	delay(dashTime);
	digitalWrite(ledPin, HIGH);
	delay(symbolGap);
}

void MorseLed::setLedPin(int pin) {
	this->ledPin = pin;
	pinMode(pin, OUTPUT);
}

const String* MorseLed::getMorse(char c) const {
    c = toupper(c);

    for (int i = 0; i < sizeof(letters) - 1; i++) {
        if (letters[i] == c) {
            return &morseTable[i];
        }
    }

    return nullptr; // unknown char
}

void MorseLed::execute(const String& text) const {
    for (int i = 0; i < text.length(); i++) {

        char c = text[i];

        if (c >= ' ' && c <= 0x2F) {
            delay(wordGap);
            continue;
        }

        const String* morsePtr = getMorse(c);

        if (morsePtr== nullptr) {
            delay(wordGap);
            continue;
        }

        if (morsePtr != nullptr) {
            sendMorseChar(*morsePtr);
            delay(letterGap);
        }
    }
}

void MorseLed::sendMorseChar(const String& morse) const {
    for (int i = 0; i < morse.length(); i++) {
        if (morse[i] == '.') dot();
        else if (morse[i] == '-') dash();
    }
}


