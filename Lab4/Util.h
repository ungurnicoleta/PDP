//
// Created by Nicoleta Ungur on 04/11/2019.
//

#ifndef LAB4_UTIL_H
#define LAB4_UTIL_H


#include <vector>
#include <iostream>

#define matrix std::vector<std::vector<int>>

class Util {
public:

    //functions returns a matrix of the specified size, containing integers in the interval (min, max)
    static std::vector<std::vector<int>> generate_matrix(int size, int min, int max) {
        std::vector<std::vector<int>> matrix_g(size, std::vector<int>(size));

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                matrix_g[i][j] = getRandom(min, max);

        return matrix_g;
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

    static void print_matrix(std::vector<std::vector<int>> matrix_g) {
        for (int i = 0; i < matrix_g.size(); i++) {
            for (int j = 0; j < matrix_g.size(); j++)
                std::cout << matrix_g[i][j] << " ";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    static void matrix_product(int starting_line, int finish_line, matrix &matrix1,
                               matrix &matrix2, matrix &result) {
        for (int i = starting_line; i < finish_line; i++)
            for (int j = 0; j < matrix1.size(); j++)
                for (int k = 0; k < matrix1.size(); k++)
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
    }
};

#endif //LAB4_UTIL_H
