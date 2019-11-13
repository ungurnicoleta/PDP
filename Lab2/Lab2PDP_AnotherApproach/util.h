//
// Created by Nicoleta Ungur on 22/10/2019.
//

#ifndef LAB2PDP_ANOTHERAPPROACH_UTIL_H
#define LAB2PDP_ANOTHERAPPROACH_UTIL_H

#include <vector>
#include <iostream>

using namespace std;

typedef vector<int> VINT;

class Util {
public:

    //functions returns a matrix of the specified size, containing integers in the interval (min, max)
    static std::vector<VINT> generate_matrix(int size, int min, int max) {
        std::vector<VINT> matrix(size, VINT(size));

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                matrix[i][j] = getRandom(min, max);

        return matrix;
    }


    //generates a random integer number in the range (a,b)
    static int getRandom(int a, int b) {
        return rand() % (b - a) + a;
    }


    //returns a vector containing the "starting line" and the "finish line" for the threads
    //the pairs are intervals of the form [starting_line ; finish_line) - exclusive
    static std::vector<std::pair<int, int>> cut_matrix_into_pieces(int matrix_size, int threads_number) {
        std::vector<std::pair<int, int>> matrix_pieces(threads_number);
        int lines_per_thread = matrix_size / threads_number;
        int starting_line = 0;

        for (int i = 0; i < threads_number - 1; i++) {
            matrix_pieces[i] = std::make_pair(starting_line, starting_line + lines_per_thread);
            starting_line += lines_per_thread;
        }

        matrix_pieces[threads_number - 1] = std::make_pair(starting_line, matrix_size);
        return matrix_pieces;
    }

    static void print_matrix(std::vector<VINT> matrix) {
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix.size(); j++)
                std::cout << matrix[i][j] << " ";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

#endif //LAB2PDP_ANOTHERAPPROACH_UTIL_H
