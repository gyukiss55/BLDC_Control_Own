#include <Arduino.h>

typedef struct {
    float ax, ay, az;
    float gx, gy, gz;
    float mx, my, mz;
    float temperature1;
    float temperature2;
    float pressure;
    float altitude;
    bool ok;
} GAM_Data;

typedef struct {
    float lat;
    float lon;
    int sats;
    bool fix;
} GPS_Data;

extern GPS_Data gps;

extern GAM_Data gam;
