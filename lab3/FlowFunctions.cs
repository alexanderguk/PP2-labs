using System;
using System.Threading;

using C = Lab3.Params;
using D = Lab3.Data;

namespace Lab3
{
    public static class FlowFunctions
    {
        private static EventWaitHandle e_Z = new ManualResetEvent(false);
        private static Semaphore sem_MR = new Semaphore(0, 5);
        private static Semaphore sem_MT = new Semaphore(0, 5);
        private static Semaphore sem_MK = new Semaphore(0, 5);
        private static Mutex mut_p = new Mutex();
        private static EventWaitHandle e_p1 = new ManualResetEvent(false);
        private static EventWaitHandle e_p2 = new ManualResetEvent(false);
        private static EventWaitHandle e_p3 = new ManualResetEvent(false);
        private static EventWaitHandle e_p4 = new ManualResetEvent(false);
        private static EventWaitHandle e_p5 = new ManualResetEvent(false);
        private static EventWaitHandle e_p6 = new ManualResetEvent(false);
        private static EventWaitHandle e_MAh2 = new ManualResetEvent(false);
        private static EventWaitHandle e_MAh3 = new ManualResetEvent(false);
        private static EventWaitHandle e_MAh4 = new ManualResetEvent(false);
        private static EventWaitHandle e_MAh5 = new ManualResetEvent(false);
        private static EventWaitHandle e_MAh6 = new ManualResetEvent(false);
        private static Object lockCS = new object();
        private static Object lockCS2 = new object();

        public static void F1()
        {
            Console.WriteLine("Thread 1 has started");

            int BEGIN_IND = 0;
            int END_IND = C.H;
            long p1;
            int a1;
            int[,] MK1;

            D.input(D.Z);
            e_Z.Set();
            D.input(D.MR);
            sem_MR.Release(5);

            int t1 = D.findMax(D.Z, BEGIN_IND, END_IND);
            mut_p.WaitOne();
            if (t1 > D.p) D.p = t1;
            mut_p.ReleaseMutex();

            e_p1.Set();

            e_p2.WaitOne();
            e_p3.WaitOne();
            e_p4.WaitOne();
            e_p5.WaitOne();
            e_p6.WaitOne();

            sem_MT.WaitOne();
            sem_MK.WaitOne();

            p1 = Interlocked.Read(ref D.p);
            a1 = D.a;
            lock (lockCS2)
            { 
                MK1 = D.MK;
            }

            calculateMAh(BEGIN_IND, END_IND, (int)p1, a1, MK1);

            e_MAh2.WaitOne();
            e_MAh3.WaitOne();
            e_MAh4.WaitOne();
            e_MAh5.WaitOne();
            e_MAh6.WaitOne();

            D.output(D.MA);

            Console.WriteLine("Thread 1 has finished");
        }

        public static void F2()
        {
            Console.WriteLine("Thread 2 has started");

            int BEGIN_IND = C.H;
            int END_IND = BEGIN_IND + C.H;
            long p2;
            int a2;
            int[,] MK2;

            e_Z.WaitOne();

            int t2 = D.findMax(D.Z, BEGIN_IND, END_IND);
            mut_p.WaitOne();
            if (t2 > D.p) D.p = t2;
            mut_p.ReleaseMutex();

            e_p2.Set();

            e_p1.WaitOne();
            e_p3.WaitOne();
            e_p4.WaitOne();
            e_p5.WaitOne();
            e_p6.WaitOne();

            sem_MR.WaitOne();
            sem_MT.WaitOne();
            sem_MK.WaitOne();

            Monitor.Enter(lockCS);
            p2 = D.p;
            Monitor.Exit(lockCS);
            a2 = D.a;
            lock (lockCS2)
            {
                MK2 = D.MK;
            }

            calculateMAh(BEGIN_IND, END_IND, p2, a2, MK2);

            e_MAh2.Set();

            Console.WriteLine("Thread 2 has finished");
        }

        public static void F3()
        {
            Console.WriteLine("Thread 3 has started");

            int BEGIN_IND = 2 * C.H;
            int END_IND = BEGIN_IND + C.H;
            long p3;
            int a3;
            int[,] MK3;

            D.input(D.MT);
            D.a = 1;

            sem_MT.Release(5);

            e_Z.WaitOne();

            int t3 = D.findMax(D.Z, BEGIN_IND, END_IND);
            mut_p.WaitOne();
            if (t3 > D.p) D.p = t3;
            mut_p.ReleaseMutex();

            e_p3.Set();

            e_p1.WaitOne();
            e_p2.WaitOne();
            e_p4.WaitOne();
            e_p5.WaitOne();
            e_p6.WaitOne();

            sem_MR.WaitOne();
            sem_MK.WaitOne();

            Monitor.Enter(lockCS);
            p3 = D.p;
            Monitor.Exit(lockCS);
            a3 = D.a;
            lock (lockCS2)
            {
                MK3 = D.MK;
            }

            calculateMAh(BEGIN_IND, END_IND, p3, a3, MK3);

            e_MAh3.Set();

            Console.WriteLine("Thread 3 has finished");
        }

        public static void F4()
        {
            Console.WriteLine("Thread 4 has started");

            int BEGIN_IND = 3 * C.H;
            int END_IND = BEGIN_IND + C.H;
            long p4;
            int a4;
            int[,] MK4;

            D.input(D.MK);
            sem_MK.Release(5);

            e_Z.WaitOne();

            int t4 = D.findMax(D.Z, BEGIN_IND, END_IND);
            mut_p.WaitOne();
            if (t4 > D.p) D.p = t4;
            mut_p.ReleaseMutex();

            e_p4.Set();

            e_p1.WaitOne();
            e_p2.WaitOne();
            e_p3.WaitOne();
            e_p5.WaitOne();
            e_p6.WaitOne();

            sem_MR.WaitOne();
            sem_MT.WaitOne();

            Monitor.Enter(lockCS);
            p4 = D.p;
            Monitor.Exit(lockCS);
            a4 = D.a;
            lock (lockCS2)
            {
                MK4 = D.MK;
            }

            calculateMAh(BEGIN_IND, END_IND, p4, a4, MK4);

            e_MAh4.Set();

            Console.WriteLine("Thread 4 has finished");
        }

        public static void F5()
        {
            Console.WriteLine("Thread 5 has started");

            int BEGIN_IND = 4 * C.H;
            int END_IND = BEGIN_IND + C.H;
            long p5;
            int a5;
            int[,] MK5;

            e_Z.WaitOne();

            int t5 = D.findMax(D.Z, BEGIN_IND, END_IND);
            mut_p.WaitOne();
            if (t5 > D.p) D.p = t5;
            mut_p.ReleaseMutex();

            e_p5.Set();

            e_p1.WaitOne();
            e_p2.WaitOne();
            e_p3.WaitOne();
            e_p4.WaitOne();
            e_p6.WaitOne();

            sem_MR.WaitOne();
            sem_MT.WaitOne();
            sem_MK.WaitOne();

            Monitor.Enter(lockCS);
            p5 = D.p;
            Monitor.Exit(lockCS);
            a5 = D.a;
            lock (lockCS2)
            {
                MK5 = D.MK;
            }

            calculateMAh(BEGIN_IND, END_IND, p5, a5, MK5);

            e_MAh5.Set();

            Console.WriteLine("Thread 5 has finished");

        }

        public static void F6()
        {
            Console.WriteLine("Thread 6 has started");

            int BEGIN_IND = 5 * C.H;
            int END_IND = BEGIN_IND + C.H;
            long p6;
            int a6;
            int[,] MK6;

            e_Z.WaitOne();

            int t6 = D.findMax(D.Z, BEGIN_IND, END_IND);
            mut_p.WaitOne();
            if (t6 > D.p) D.p = t6;
            mut_p.ReleaseMutex();

            e_p6.Set();

            e_p1.WaitOne();
            e_p2.WaitOne();
            e_p3.WaitOne();
            e_p4.WaitOne();
            e_p5.WaitOne();

            sem_MR.WaitOne();
            sem_MT.WaitOne();
            sem_MK.WaitOne();

            Monitor.Enter(lockCS);
            p6 = D.p;
            Monitor.Exit(lockCS);
            a6 = D.a;
            lock (lockCS2)
            {
                MK6 = D.MK;
            }

            calculateMAh(BEGIN_IND, END_IND, p6, a6, MK6);
            e_MAh6.Set();
            Console.WriteLine("Thread 6 has finished");
        }

        private static void calculateMAh(int BEGIN_IND, int END_IND, long p, int a, int[,] MK)
        {
	        for (int iH = BEGIN_IND; iH < END_IND; iH++) {
		        for (int jH = 0; jH < C.N; jH++) {
			        int a_mki_MRj = 0;
                    for (int ind = 0; ind < C.N; ind++)
                    {
                        a_mki_MRj += D.MK[iH, ind] * D.MR[ind,iH];
			        }
                    int MAij = (int)p * D.MT[iH,jH] + a * a_mki_MRj;
                    D.MA[jH,iH] = MAij;
		        }
	        }
        }
    }
}