void kernel shortcut(global float * const dst, global float const * const src, unsigned const n)
{
    size_t const row = get_global_id(0);
    size_t const col = get_global_id(1);

    if (row >= n || col >= n)
    {
        return;
    }

    float minimum = FLT_MAX;

    for (size_t k = 0; k < n; ++k)
    {
        minimum = min(minimum, src[col * n + k] + src[k * n + row]);
    }

    dst[row * n + col] = minimum;
}