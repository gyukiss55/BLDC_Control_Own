// SVPWM.cpp


static void SVPWM(
    float alpha,
    float beta,
    float vbus,
    float* da,
    float* db,
    float* dc)
{
    float va = alpha;

    float vb =
        -0.5f * alpha +
        0.8660254f * beta;

    float vc =
        -0.5f * alpha -
        0.8660254f * beta;

    float vmax = va;
    float vmin = va;

    if (vb > vmax) vmax = vb;
    if (vc > vmax) vmax = vc;

    if (vb < vmin) vmin = vb;
    if (vc < vmin) vmin = vc;

    float offset =
        (vmax + vmin) * 0.5f;

    va -= offset;
    vb -= offset;
    vc -= offset;

    *da = 0.5f + va / vbus;
    *db = 0.5f + vb / vbus;
    *dc = 0.5f + vc / vbus;

    if (*da < 0) *da = 0;
    if (*da > 1) *da = 1;

    if (*db < 0) *db = 0;
    if (*db > 1) *db = 1;

    if (*dc < 0) *dc = 0;
    if (*dc > 1) *dc = 1;
}
