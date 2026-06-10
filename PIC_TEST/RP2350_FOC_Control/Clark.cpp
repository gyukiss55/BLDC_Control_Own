static void Clarke(
    float ia,
    float ib,
    float* alpha,
    float* beta)
{
    *alpha = ia;

    *beta =
        -(2.0f * ib + ia)
        * INV_SQRT3;
}
