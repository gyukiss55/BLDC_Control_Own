// InvPark.cpp
#include <math.h>

static void InvPark(
    float d,
    float q,
    float theta,
    float* alpha,
    float* beta)
{
    float s = sinf(theta);
    float c = cosf(theta);

    *alpha =
        d * c -
        q * s;

    *beta =
        d * s +
        q * c;
}
