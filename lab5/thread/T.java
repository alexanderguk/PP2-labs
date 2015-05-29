package thread;

import static main.Data.*;
import static main.InputParameters.*;

public abstract class T implements Runnable {

    int BEGIN_CALC_IND;
    int END_CALC_IND;

    public T(int id) {
        BEGIN_CALC_IND = id * H;
        END_CALC_IND = BEGIN_CALC_IND + H;
    }

    @Override
    public void run() {
        System.out.println("Thread " + (BEGIN_CALC_IND / H + 1) + " has started");
        processCommand();
        System.out.println("Thread " + (BEGIN_CALC_IND / H + 1) + " has finished");
    }

    public void processCommand() {

    }

}
