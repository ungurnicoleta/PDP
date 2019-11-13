package com.company;

public class MatrixProduct implements Operation {

    private int startingLine;
    private int endingLine;
    private int[][] matrixA;
    private int[][] matrixB;
    private int[][] matrixSum;

    MatrixProduct(int startingLine, int endingLine, int[][] matrixA, int[][] matrixB, int[][] matrixSum) {
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
                for (int k = 0; k < matrixA.length; k++)
                    matrixSum[i][j] += matrixA[i][k] * matrixB[k][j];
        return "Computing product for lines " + startingLine + " - " + endingLine + " finished successfully!";
    }
}
