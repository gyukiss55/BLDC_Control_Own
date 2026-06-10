// MorseLed.h


class MorseLed
{
	int ledPin;
public:
	MorseLed();
	~MorseLed();
	void setLedPin(int pin);
	void execute(const String& message) const;

private:
	const String* getMorse(char c) const;
	void dot() const;
	void dash() const;
	void sendMorseChar(const String& morse) const;
};

