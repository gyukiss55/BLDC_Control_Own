// Pico_UDPserver.h
void setupUDPServer();
void loopUDPServer();
void setupUDPClient();
void loopUDPClient(unsigned int udpPort);
void sendUDPMessage(const String& message);
