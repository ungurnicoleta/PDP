package com.company;

import java.util.ArrayList;
import java.util.Random;

public class Util {

    //generates a random number between (min, max)
    static int generateRandom(int min, int max) {
        Random ran = new Random();
        return (min + ran.nextInt(max - min));
    }

    //function that prints a matrix
    static void printMatrix(int [][] matrix) {
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix.length; j++)
                System.out.print(Integer.toString(matrix[i][j]) + " ");
            System.out.print("\n");
        }
        System.out.print("\n");
        System.out.print("\n");
    }

    //functions returns a matrix of the specified size, containing integers in the interval [min, max)
    static int[][] generateMatrix(int size, int min, int max) {
        int[][] matrix = new int[size][size];
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                matrix[i][j] = generateRandom(min, max);
        return matrix;
    }


    static ArrayList<Pair<Integer, Integer>> cutMatrixIntoPieces(int matrixSize, int threadNumber) {
        ArrayList<Pair<Integer, Integer>> matrixPieces = new ArrayList<>(threadNumber);

        int startingLine = 0;
        int linesPerThread = matrixSize / threadNumber;

        for (int i = 0; i <= threadNumber - 1; i++) {
            matrixPieces.add(Pair.createPair(startingLine, startingLine + linesPerThread));
            startingLine += linesPerThread;
        }

        matrixPieces.add(Pair.createPair(startingLine, matrixSize));
        return matrixPieces;
    }
}
