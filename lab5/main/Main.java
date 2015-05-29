/**
 ** PP-2. Lab 5. Java. Monitors
 ** MA = max(Z)*MO+(B*C)(MT*MR)
 ** Author: Alexander Guk, IP-22
 ** Date: 07.05.2015
 **/

package main;

import thread.*;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {
    public static void main(String[] args) {
        ExecutorService executor = Executors.newFixedThreadPool(6);

        executor.execute(new T1(0));
        executor.execute(new T2(1));
        executor.execute(new T3(2));
        executor.execute(new T4(3));
        executor.execute(new T5(4));
        executor.execute(new T6(5));

        // This will make the executor accept no new threads
        // and finish all existing threads in the queue
        executor.shutdown();
        // Wait until all threads are finish
        while (!executor.isTerminated()) {
            // pass
        }

        System.out.println("All threads have been finished");
    }
}
