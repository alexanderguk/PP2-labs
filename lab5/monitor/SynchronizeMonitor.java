package monitor;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import static main.InputParameters.*;

public class SynchronizeMonitor {
    private static int flagInput = 0;
    private static int flagCalculate1 = 0;
    private static int flagCalculate2 = 0;


    private final static int NUM_OF_INPUTS = 3;
    private final static int NUM_OF_CALCS_1 = 6;
    private final static int NUM_OF_CALCS_2 = 5;


    private static Lock aLock = new ReentrantLock();
    private static Condition inputed = aLock.newCondition();
    private static Condition calculated1 = aLock.newCondition();
    private static Condition calculated2 = aLock.newCondition();


    public static void signalInput() {
        aLock.lock();

        try {
            flagInput++;

            if (flagInput == NUM_OF_INPUTS) {
                inputed.signalAll();
            }
        } finally {
            aLock.unlock();
        }
    }

    public static void waitInput() {
        aLock.lock();

        try {
            while (flagInput < NUM_OF_INPUTS) {
                inputed.await();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            aLock.unlock();
        }
    }


    public static void signalCalculate1() {
        aLock.lock();

        try {
            flagCalculate1++;

            if (flagCalculate1 == NUM_OF_CALCS_1) {
                calculated1.signalAll();
            }

        } finally {
            aLock.unlock();
        }
    }

    public static void waitCalculate1() {
        aLock.lock();

        try {
            while (flagCalculate1 < NUM_OF_CALCS_1) {
                calculated1.await();
            }

        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            aLock.unlock();
        }
    }

    public static void signalCalculate2() {
        aLock.lock();

        try {
            flagCalculate2++;

            if (flagCalculate2 == NUM_OF_CALCS_2) {
                calculated2.signalAll();
            }

        } finally {
            aLock.unlock();
        }
    }

    public static void waitCalculate2() {
        aLock.lock();

        try {
            while (flagCalculate2 < NUM_OF_CALCS_2) {
                calculated2.await();
            }

        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            aLock.unlock();
        }
    }

}
