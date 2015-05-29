package thread;

import static monitor.ResourceMonitor.*;
import static monitor.SynchronizeMonitor.*;
import static main.Data.*;

public class T1 extends T {

    public T1(int id) {
        super(id);
    }

    @Override
    public void processCommand() {
        inputMO();

        signalInput();
        waitInput();

        int maxh = calculateMaxH(BEGIN_CALC_IND, END_CALC_IND);
        setMax(maxh);
        int BCh = calculateBCh(BEGIN_CALC_IND, END_CALC_IND);
        setT(BCh);

        signalCalculate1();
        waitCalculate1();

        int max1 = getCopymax();
        int t1 = getCopyt();
        int[][] MT1 = getCopyMT();
        calculateMAh(max1, t1, MT1, BEGIN_CALC_IND, END_CALC_IND);

        waitCalculate2();

        printMA();
    }

}

