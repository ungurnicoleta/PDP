#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

typedef vector<int> VINT;
#define N 1500
#define NR_THREADS 4

vector<VINT> A(N, VINT(N,0));
vector<VINT> B(N, VINT(N, 0));
vector<VINT> C(N, VINT(N, 0));
vector<VINT> D(N, VINT(N, 0));

void multiplicationInThread(int const &pos) {
    int total = N * N;
    for (int crt = pos; crt < total; crt += NR_THREADS) {
        int i = crt / N;
        int j = crt % N;
        for (int k = 0; k < N; k++)
            C[i][j] = A[i][k] * B[k][j];
    }
}


int main() {
    // Initialise the matrix with some numbers
    int nr = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            nr++;
            A[i][j] = nr;
            B[i][j] = nr;
        }

    // Start the time
    typedef chrono::high_resolution_clock Time;
    typedef chrono::milliseconds ms;
    typedef chrono::duration<float> FSEC;
    auto t0 = Time::now();


    // Start the threads
    vector<thread> threads;
    threads.reserve(NR_THREADS);
    for (int i = 0; i < NR_THREADS; i++) {
        threads.emplace_back(thread(multiplicationInThread, i));
    }

    // Wait for all threads to finish
    for (auto &thread: threads) {
        thread.join();;
    }

    // Stop the time
    auto t1 = Time::now();
    FSEC fs = t1 - t0;

    ms timed = std::chrono::duration_cast<ms>(fs);
    std::cout << timed.count() << "ms\n";

    // Compute the result of the multiplication (to check for the threads result)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int h = 0; h < N; h++) {
                D[i][j] += A[i][h] * A[h][j];
            }
        }
    }
    // Check to see if the results are ok
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            if (D[i][j] != C[i][j]) {
                throw std::runtime_error("Something was wrong with this multiplication");
            }
        }
}