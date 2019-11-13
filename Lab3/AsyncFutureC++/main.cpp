#include <iostream>
#include <thread>
#include <future>

#include "util.h"

#define MATRIX_SIZE 10
#define NUM_THREADS 1
#define MIN_VALUE 0
#define MAX_VALUE 2
using namespace std;
int main() {


    //generate matrix 1
    vector<vector<int>> matrix1 = Util::generate_matrix(MATRIX_SIZE, MIN_VALUE, MAX_VALUE);
    cout << "Matrix1: " << endl;
    Util::print_matrix(matrix1);

    //generate matrix 2
    vector<vector<int>> matrix2 = Util::generate_matrix(MATRIX_SIZE, MIN_VALUE, MAX_VALUE);
    cout << "Matrix2: " << endl;
    Util::print_matrix(matrix2);

    //declare the result matrix
    vector<vector<int>> result(MATRIX_SIZE, vector<int>(MATRIX_SIZE));
    shared_ptr<vector<vector<int>>> result_ptr = make_shared<vector<vector<int>>>(result);

    //generate the number of threads that will handle the operations
    vector<thread> threadPool;
    threadPool.reserve(NUM_THREADS);

    //cut the matrix by lines
    vector<pair<int, int>> pairs = Util::cut_matrix_into_pieces(MATRIX_SIZE, NUM_THREADS);
    cout << "Starting line - finish line" << endl;
    for (int i = 0; i < NUM_THREADS; i++)
        cout << "Thread " << i + 1 << ": " << pairs[i].first << " - " << pairs[i].second << endl;

    clock_t start = clock();

    vector<future<string>> futures;

    for (unsigned i = 0; i < NUM_THREADS; i++) {
        futures.emplace_back(
                async(launch::async, Util::matrix_product, pairs[i].first, pairs[i].second, matrix1, matrix2,
                           result_ptr));
    }

    auto end = clock();

    for (auto & future : futures)
        cout << future.get() << endl;

    cout << "Time: " << end - start << endl;
    cout << "\n\n";

    //Util::print_matrix(result);
    for (int i = 0; i < (*result_ptr).size(); i++) {
        for (int j = 0; j < (*result_ptr).size(); j++)
            cout << (*result_ptr)[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    return 0;
}
