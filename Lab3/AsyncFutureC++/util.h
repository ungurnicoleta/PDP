//
// Created by Nicoleta Ungur on 28/10/2019.
//

#ifndef ASYNCFUTUREC___UTIL_H
#define ASYNCFUTUREC___UTIL_H


#include <vector>
#include <iostream>


using namespace std;

class Util {
public:

    //functions returns a matrix of the specified size, containing integers in the interval (min, max)
    static vector<vector<int>> generate_matrix(int size, int min, int max) {
        vector<vector<int>> matrix(size, vector<int>(size));

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
    static vector<pair<int, int>> cut_matrix_into_pieces(int matrix_size, int threads_number) {
        vector<pair<int, int>> matrix_pieces(threads_number);
        int lines_per_thread = matrix_size / threads_number;
        int starting_line = 0;

        for (int i = 0; i < threads_number - 1; i++) {
            matrix_pieces[i] = make_pair(starting_line, starting_line + lines_per_thread);
            starting_line += lines_per_thread;
        }

        matrix_pieces[threads_number - 1] = make_pair(starting_line, matrix_size);
        return matrix_pieces;
    }

    static void print_matrix(vector<vector<int>> matrix) {
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix.size(); j++)
                cout << matrix[i][j] << " ";
            cout << endl;
        }
        cout << endl;
    }

    static string matrix_sum(int starting_line, int finish_line, vector<vector<int>> matrix1,
                             vector<vector<int>> matrix2, shared_ptr<vector<vector<int>>> result) {
        for (int i = starting_line; i < finish_line; i++)
            for (int j = 0; j < matrix1.size(); j++)
                (*result)[i][j] = (matrix1[i][j] + matrix2[i][j]);
        return "Finished" + to_string(starting_line) + " - " + to_string(finish_line) + "";
    }

    static string matrix_product(int starting_line, int finish_line, vector<vector<int>> matrix1,
                                 vector<vector<int>> matrix2, shared_ptr<vector<vector<int>>> result) {
        for (int i = starting_line; i < finish_line; i++)
            for (int j = 0; j < matrix1.size(); j++)
                for (int k = 0; k < matrix1.size(); k++)
                    (*result)[i][j] += matrix1[i][k] * matrix2[k][j];
        return "Finished" + to_string(starting_line) + " - " + to_string(finish_line) + "";
    }
};


#endif //ASYNCFUTUREC___UTIL_H
