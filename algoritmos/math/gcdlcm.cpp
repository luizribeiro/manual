template<class _T> _T gcd(_T a, _T b) {
    return a ? gcd(b%a, a) : b;
}

template<class _T> _T lcm(_T a, _T b) {
    return a * b / gcd(a, b);
}
