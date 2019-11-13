package com.company;

public class MatrixSum implements Operation {

    private int startingLine;
    private int endingLine;
    private int[][] matrixA;
    private int[][] matrixB;
    private int[][] matrixSum;

    MatrixSum(int startingLine, int endingLine, int[][] matrixA, int[][] matrixB, int[][] matrixSum) {
        this.startingLine = startingLine;
        this.endingLine = endingLine;
        this.matrixA = matrixA;
        this.matrixB = matrixB;
        this.matrixSum = matrixSum;
    }

    @Override
    public String call() {
        for (int i = startingLine; i < endingLine; i++)
            for (int j = 0; j < matrixA.length; j++)
                matrixSum[i][j] = matrixA[i][j] + matrixB[i][j];
        return "Computing sum for lines " + startingLine + " - " + endingLine + " finished successfully!";
    }
}
