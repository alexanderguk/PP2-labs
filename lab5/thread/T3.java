package thread;

import static monitor.ResourceMonitor.*;
import static monitor.SynchronizeMonitor.*;
import static main.Data.*;
import static monitor.SynchronizeMonitor.signalCalculate2;

public class T3 extends T {

    public T3(int id) {
        super(id);
    }

    @Override
    public void processCommand() {
        waitInput();

        int maxh = calculateMaxH(BEGIN_CALC_IND, END_CALC_IND);
        setMax(maxh);
        int BCh = calculateBCh(BEGIN_CALC_IND, END_CALC_IND);
        setT(BCh);

        signalCalculate1();
        waitCalculate1();

        int max3 = getCopymax();
        int t3 = getCopyt();
        int[][] MT3 = getCopyMT();
        calculateMAh(max3, t3, MT3, BEGIN_CALC_IND, END_CALC_IND);

        signalCalculate2();
    }

}

