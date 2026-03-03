#include <iostream>
#include <vector>
#include <immintrin.h>
using namespace std;

void sub_avx(const float* a, const float* b, float* c, int n) {
    int i = 0;
    for (; i <= n - 8; i += 8) {
        __m256 va = _mm256_loadu_ps(a + i);
        __m256 vb = _mm256_loadu_ps(b + i);
        __m256 vc = _mm256_sub_ps(va, vb);
        _mm256_storeu_ps(c + i, vc);
    }
    for (; i < n; ++i)
        c[i] = a[i] - b[i];
}


void sub_scalar(const float* a, const float* b, float* c, int n) {
    for (int i = 0; i < n; ++i)
        c[i] = a[i] - b[i];
}

int main() {
    int n = 16;
    vector<float> a(n, 5.0f), b(n, 2.0f), c(n);

    sub_scalar(a.data(), b.data(), c.data(), n);

    for (int i = 0; i < n; ++i)
        cout << c[i] << " ";
}