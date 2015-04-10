using System;
using C = Lab3.Params;

namespace Lab3
{
    public static class Data
    {
        public static volatile int a;
        public static long p = long.MinValue;
        public static int[] Z = new int[C.N];
        public static int[,] MA = new int[C.N, C.N];
        public static int[,] MT = new int[C.N, C.N];
        public static int[,] MK = new int[C.N, C.N];
        public static int[,] MR = new int[C.N, C.N];

        public static void input(int[,] MM)
        {
            for (int i = 0; i < C.N; i++)
                for (int j = 0; j < C.N; j++)
                    MM[i, j] = C.FILL_VALUE;
        }

        public static void input(int[] V)
        {
            for (int i = 0; i < C.N; i++)
                V[i] = C.FILL_VALUE;
        }

        public static void output(int[,] MM)
        {
            for (int i = 0; i < C.N; i++)
            {
                for (int j = 0; j < C.N; j++)
                {
                    Console.Write(MM[i, j] + " ");
                }
                Console.WriteLine();
            }
        }

        public static void output(int[] V)
        {
            for (int i = 0; i < C.N; i++)
            {
                Console.Write(V[i] + " ");
            }
            Console.WriteLine();
        }

        public static int findMax(int[] V, int begin, int end)
        {
            int maxElem = V[begin];
            for (int i = begin + 1; i < end; i++)
            {
                if (V[i] > maxElem) maxElem = V[i];
            }
            return maxElem;
        }
    }
}