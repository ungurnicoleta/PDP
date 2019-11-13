//
// Created by Nicoleta Ungur on 04/11/2019.
//

#ifndef LAB4_TASK_H
#define LAB4_TASK_H

#include <memory>
#include <vector>

#define matrix std::vector<std::vector<int>>

class Task {
public:
    Task() {}

    Task(int starting_line, int finish_line, matrix matrix1, matrix matrix2) :
            starting_line(starting_line),
            finish_line(finish_line),
            matrix1(matrix1),
            matrix2(matrix2) {}

    Task(const Task &job) {
        starting_line = job.starting_line;
        finish_line = job.finish_line;
        matrix1 = job.matrix1;
        matrix2 = job.matrix2;
    }

private:
    int starting_line;
    int finish_line;
    matrix matrix1;
    matrix matrix2;

public:
    void execute(matrix &result) {
        for (int i = starting_line; i < finish_line; i++)
            for (int j = 0; j < matrix1.size(); j++)
                for (int k = 0; k < matrix1.size(); k++)
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
    }
};


#endif //LAB4_TASK_H
