#include <immintrin.h>
#include <iostream>
#include <chrono>
using namespace std;

int main() {
    const int N = 512;
    const int tile_size = 64;

    float A[N][N];
    float B[N][N];
    float C[N][N];

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            A[i][j] = j + 1;
            B[i][j] = 1.0f;
            C[i][j] = 0.0f;
        }
    }

    auto st = chrono::high_resolution_clock::now();

    for(int ii=0;ii<N;ii+=tile_size){
        for(int jj=0;jj<N;jj+=tile_size){
            for(int kk=0;kk<N;kk+=tile_size){

                for (int i = ii; i < min(ii+tile_size,N); i++) {
                    for (int k = kk; k < min(kk+tile_size,N); k++) {

                        __m256 a_val = _mm256_set1_ps(A[i*N + k]);

                        for (int j = jj; j < min(jj+tile_size,N); j += 8) {

                            __m256 b_vec = _mm256_loadu_ps(&B[k*N + j]);
                            __m256 c_vec = _mm256_loadu_ps(&C[i*N + j]);

                            __m256 prod = _mm256_mul_ps(a_val, b_vec);
                            c_vec = _mm256_add_ps(c_vec, prod);

                            _mm256_storeu_ps(&C[i*N + j], c_vec);
                        }
                    }
                }

            }
        }
    }

    // for(int i=0;i<N;i++){
    //     for(int k=0;k<N;k++){

    //         __m256 a_val = _mm256_set1_ps(A[i][k]);

    //         for(int j=0;j<N;j+=8){

    //             __m256 b_vec = _mm256_loadu_ps(&B[k][j]);
    //             __m256 c_vec = _mm256_loadu_ps(&C[i][j]);

    //             __m256 result = _mm256_mul_ps(a_val, b_vec);
    //             c_vec = _mm256_add_ps(c_vec, result);

    //             _mm256_storeu_ps(&C[i][j], c_vec);
    //         }
    //     }
    // }

    auto ed = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<chrono::microseconds>(ed - st);
    cout << "Time taken: " << time.count() << " microseconds\n";

    // for(int i=0;i<N;i++){
    //     for(int j=0;j<N;j++)
    //         cout << C[i][j] << " ";
    //     cout << endl;
    // }
}