static void Park(
    float alpha,
    float beta,
    float theta,
    float* d,
    float* q)
{
    float s = sinf(theta);
    float c = cosf(theta);

    *d =
        alpha * c +
        beta * s;

    *q =
        -alpha * s +
        beta * c;
}
