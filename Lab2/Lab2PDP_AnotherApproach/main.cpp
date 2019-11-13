#include <iostream>
#include <thread>

#include "util.h"

#define MATRIX_SIZE 11
#define NUM_THREADS 4
#define MIN_VALUE 0
#define MAX_VALUE 6

using namespace std;
typedef vector<int> VINT;

void matrix_sum(int starting_line, int finish_line, vector<VINT> &matrix1,
                vector<VINT> &matrix2, vector<VINT> &result) {
    for (int i = starting_line; i < finish_line; i++)
        for (int j = 0; j < matrix1.size(); j++)
            result[i][j] = (matrix1[i][j] + matrix2[i][j]);
}

void matrix_product(int starting_line, int finish_line, vector<std::vector<int>> &matrix1,
                    vector<VINT> &matrix2, vector<VINT> &result) {
    for (int i = starting_line; i < finish_line; i++)
        for (int j = 0; j < matrix1.size(); j++)
            for (int k = 0; k < matrix1.size(); k++)
                result[i][j] += matrix1[i][k] * matrix2[k][j];
}


int main() {
    //generate matrix 1
    vector<VINT> matrix1 = Util::generate_matrix(MATRIX_SIZE, MIN_VALUE, MAX_VALUE);
    cout << "Matrix1: " << endl;
    Util::print_matrix(matrix1);

    //generate matrix 2
    vector<VINT> matrix2 = Util::generate_matrix(MATRIX_SIZE, MIN_VALUE, MAX_VALUE);
    cout << "Matrix2: " << endl;
    Util::print_matrix(matrix2);

    //declare the result matrix
    vector<VINT> result(MATRIX_SIZE, vector<int>(MATRIX_SIZE));

    //generate the number of threads that will handle the operations
    vector<thread> threadPool;
    threadPool.reserve(NUM_THREADS);

    //cut the matrix by lines
    vector<std::pair<int, int>> pairs = Util::cut_matrix_into_pieces(MATRIX_SIZE, NUM_THREADS);
    cout << "Starting line - finish line" << endl << '\n';

    for (int i = 0; i < NUM_THREADS; i++)
        cout << "Thread " << i + 1 << ": " << pairs[i].first << " - " << pairs[i].second << endl;

    clock_t start = std::clock();

    //start the threads
    for (int i = 0; i < NUM_THREADS; i++)
        threadPool.emplace_back(matrix_sum, pairs[i].first, pairs[i].second, ref(matrix1), ref(matrix2), ref(result));
//        threadPool.emplace_back(matrix_product, pairs[i].first, pairs[i].second, std::ref(matrix1), std::ref(matrix2),
//                            std::ref(result));

    //join all the threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (threadPool[i].joinable()) {
            threadPool[i].join();
        }
    }

    auto end = clock();

    cout << '\n' << "Time: " << end - start << "ms" << endl << '\n';

    Util::print_matrix(result);

    return 0;
}
