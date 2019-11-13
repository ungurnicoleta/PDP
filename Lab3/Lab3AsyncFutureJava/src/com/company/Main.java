package com.company;

import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {

    private static final int SIZE = 11;
    private static final int NUM_THREADS = 3;
    private static final int MIN = 10;
    private static final int MAX = 20;

    public static void main(String[] args) throws InterruptedException {
        int[][] a = Util.generateMatrix(SIZE, MIN, MAX);
        int[][] b = Util.generateMatrix(SIZE, MIN, MAX);
        int[][] result = new int[SIZE][SIZE];

        Util.printMatrix(a);
        Util.printMatrix(b);

        ArrayList<Pair<Integer, Integer>> pairs = Util.cutMatrixIntoPieces(SIZE, NUM_THREADS);

        //create the thread pool
        ExecutorService pool = Executors.newFixedThreadPool(NUM_THREADS);

        long start = System.nanoTime();

        for (int i = 0; i < pairs.size(); i++) {
            Operation op = new MatrixProduct(pairs.get(i).getFirst(), pairs.get(i).getSecond(), a, b, result);
            try {
                System.out.println(pool.submit(op).get());
            } catch (Exception e) {
                throw new RuntimeException();
            }
        }

        long end = System.nanoTime();

        System.out.println();
        Util.printMatrix(result);
        System.out.println("Time:");
        System.out.println((end - start) / 1e6);
    }
}
