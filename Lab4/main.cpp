#include <utility>

#include <iostream>
#include <thread>
#include <future>

#include "Util.h"
#include "Queue.h"

#define MATRIX_SIZE 10
#define NUM_THREADS 8
#define MIN_VALUE 0
#define MAX_VALUE 2

#define matrix std::vector<std::vector<int>>

void runConsumer(Queue &queue, matrix &result) {
    Task task;
    while (queue.dequeue(task)) {
        task.execute(result);
    }
}

void runProducer(Queue &queue, int starting_line, int finish_line, matrix &matrix1, matrix &matrix2, matrix &matrix3,
                 matrix &result) {
    Util::matrix_product(starting_line, finish_line, matrix1, matrix2, result);
    Task task(starting_line, finish_line, result, matrix3);
    queue.enqueue(task);

}

int main() {
    //generate matrix 1
    matrix matrix1 = Util::generate_matrix(MATRIX_SIZE, MIN_VALUE, MAX_VALUE);
    std::cout << "Matrix1: " << std::endl;
    Util::print_matrix(matrix1);

    //generate matrix 2
    matrix matrix2 = Util::generate_matrix(MATRIX_SIZE, MIN_VALUE, MAX_VALUE);
    std::cout << "Matrix2: " << std::endl;
    Util::print_matrix(matrix2);

    //generate matrix 3
    matrix matrix3 = Util::generate_matrix(MATRIX_SIZE, MIN_VALUE, MAX_VALUE);
    std::cout << "Matrix3: " << std::endl;
    Util::print_matrix(matrix3);

    //declare the intermediary_result matrix
    matrix intermediary_result(MATRIX_SIZE, std::vector<int>(MATRIX_SIZE));

    //declare the final result matrix
    matrix result(MATRIX_SIZE, std::vector<int>(MATRIX_SIZE));

    //generate the number of threads that will handle the operations
    std::vector<std::thread> threadPool;
    threadPool.reserve(NUM_THREADS * 2);

    //create the Queue
    Queue queue;

    //cut the matrix by lines
    std::vector<std::pair<int, int>> pairs = Util::cut_matrix_into_pieces(MATRIX_SIZE, NUM_THREADS);
    std::cout << "Starting line - finish line" << std::endl;
    for (int i = 0; i < NUM_THREADS; i++)
        std::cout << "Thread " << i + 1 << ": " << pairs[i].first << " - " << pairs[i].second << std::endl;

    std::clock_t start = std::clock();

    //start Consumers (from NUM_THREADS to NUM_THREADS*2-1)
    for (int i = 0; i < NUM_THREADS; i++)
        threadPool.emplace_back(std::thread(runConsumer, std::ref(queue), std::ref(result)));

    //start Producers (from 0 to NUM_THREADS - 1)
    for (int i = 0; i < NUM_THREADS; i++)
        threadPool.emplace_back(std::thread(runProducer, std::ref(queue), pairs[i].first, pairs[i].second,
                                            std::ref(matrix1), std::ref(matrix2), std::ref(matrix3),
                                            std::ref(intermediary_result)));

    std::cout << "\n";
    for (int i = 0; i < intermediary_result.size(); i++) {
        std::cout << "\t";
        for (int j = 0; j < intermediary_result.size(); j++)
            if (intermediary_result[i][j] < 10)
                std::cout <<intermediary_result[i][j] << "    ";
            else
                std::cout <<intermediary_result[i][j] << "   ";
        std::cout << std::endl;
    }
    std::cout << std::endl;

    //join producers
    for (int i = NUM_THREADS; i < NUM_THREADS * 2; i++)
        threadPool[i].join();
    queue.close();
    std::cout << "\n" <<"The queue is: "<< queue.is_closed() << " (1-true, 0-false) " << std::endl;

    //join consumers
    for (int i = 0; i < NUM_THREADS; i++)
        threadPool[i].join();

    auto end = std::clock();

    std::cout << "Time: " << (end - start) / (double) CLOCKS_PER_SEC << std::endl;

   // Util::print_matrix(result);

   std::cout << "\n";
    for (int i = 0; i < result.size(); i++) {
        std::cout << "\t";
        for (int j = 0; j < result.size(); j++)
            if (result[i][j] < 10)
                std::cout <<result[i][j] << "    ";
            else
                std::cout <<result[i][j] << "   ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return 0;
}