using System;
using System.Threading;

using Lab3;

namespace Lab3
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            Thread T1 = new Thread(new ThreadStart(FlowFunctions.F1));
            Thread T2 = new Thread(new ThreadStart(FlowFunctions.F2));
            Thread T3 = new Thread(new ThreadStart(FlowFunctions.F3));
            Thread T4 = new Thread(new ThreadStart(FlowFunctions.F4));
            Thread T5 = new Thread(new ThreadStart(FlowFunctions.F5));
            Thread T6 = new Thread(new ThreadStart(FlowFunctions.F6));

            T1.Start();
            T2.Start();
            T3.Start();
            T4.Start();
            T5.Start();
            T6.Start();

            Thread.Sleep(5000);
        }
    }
}