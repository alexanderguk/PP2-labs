package monitor;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import static main.Data.*;

public class ResourceMonitor {
    private static final Lock aLock = new ReentrantLock();

    public static int[][] getCopyMT() {
        aLock.lock();

        try {
            return MT;
        } finally {
            aLock.unlock();
        }
    }

    public static int getCopymax() {
        aLock.lock();

        try {
            return max;
        } finally {
            aLock.unlock();
        }
    }

    public static int getCopyt() {
        aLock.lock();

        try {
            return t;
        } finally {
            aLock.unlock();
        }
    }

    public static void setMax(int maxh) {
        aLock.lock();

        try {
            if (maxh > max) {
                max = maxh;
            }
        } finally {
            aLock.unlock();
        }
    }

    public static void setT(int th) {
        aLock.lock();

        try {
            t += th;
        } finally {
            aLock.unlock();
        }
    }
}
