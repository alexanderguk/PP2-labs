package thread;

import static monitor.ResourceMonitor.*;
import static monitor.SynchronizeMonitor.*;
import static main.Data.*;
import static monitor.SynchronizeMonitor.signalCalculate2;

public class T4 extends T {

    public T4(int id) {
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

        int max4 = getCopymax();
        int t4 = getCopyt();
        int[][] MT4 = getCopyMT();
        calculateMAh(max4, t4, MT4, BEGIN_CALC_IND, END_CALC_IND);

        signalCalculate2();
    }

}

