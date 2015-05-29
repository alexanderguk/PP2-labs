package main;

import static main.InputParameters.*;

public class Data {
    public static int[][] MA = new int[N][N];
    public static int[] Z = new int[N];
    public static int[][] MO = new int[N][N];
    public static int[] B = new int[N];
    public static int[] C = new int[N];
    public static int[][] MT = new int[N][N];
    public static int[][] MR = new int[N][N];
    public static int max = Integer.MIN_VALUE;
    public static int t = 0;

    public static int calculateMaxH(int begin, int end) {
        int max = Z[begin];
        for (int i = begin; i < end; ++i) {
            if (Z[i] > max)
            {
                max = Z[i];
            }
        }
        return max;
    }

    public static int calculateBCh(int begin, int end) {
        int result = 0;
        for (int i = begin; i < end; ++i) {
            result += B[i] * C[i];
        }
        return result;
    }

    public static void calculateMAh(int maxx, int tx, int[][] MTx, int begin, int end) {
        int[][] tmpM = new int[N][N];
        for (int i = begin; i < end; ++i) {
            for (int j = 0; j < N; ++j) {
                tmpM[j][i] = MO[j][i] * maxx;
            }
        }

        for (int i = begin; i < end; ++i) {
            for (int j = 0; j < N; ++j) {
                MA[j][i] = 0;
                for (int k = 0; k < N; ++k) {
                    MA[j][i] += MTx[j][k] * MR[k][i];
                }
                MA[j][i] *= tx;
                MA[j][i] += tmpM[j][i];
            }
        }
    }

    public static int[] generateVector() {
        int[] V = new int[N];
        for (int i = 0; i < N; i++) {
            V[i] = FILL_VALUE;
        }
        return V;
    }

    public static int[][] generateMatrix() {
        int[][] MM = new int[N][N];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                MM[i][j] = FILL_VALUE;

        return MM;
    }


    public static void printMA() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                System.out.print(MA[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static void inputZ() {
        Z = generateVector();
    }

    public static void inputMO() {
        MO = generateMatrix();
    }

    public static void inputB() {
        B = generateVector();
    }

    public static void inputC() {
        C = generateVector();
    }

    public static void inputMT() {
        MT = generateMatrix();
    }

    public static void inputMR() {
        MR = generateMatrix();
    }

}
