
/**
 * @brief Fast D&C Power Modulo Function. `x**p % M`
 * @param x Target
 * @param p Power
 * @param M modulo
 */
unsigned int fastpowmod(unsigned x, unsigned p, unsigned int M)
{
    unsigned int result = 1;
    unsigned int base = x;

    while (p != 0)
    {
        if (p & 1)
            result = result * base % M;
        base = base * base % M;
        p >>= 1;
    }
    return result;
}

/**
 * @brief Euclidean Algorithm
 */
unsigned int gcd(unsigned int a, unsigned int h)
{
    unsigned int temp;
    while (1)
    {
        temp = a % h;
        if (temp == 0)
            return h;
        a = h;
        h = temp;
    }

    return 1;
}