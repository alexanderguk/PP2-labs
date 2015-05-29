package thread;

import static monitor.ResourceMonitor.*;
import static monitor.SynchronizeMonitor.*;
import static main.Data.*;
import static monitor.SynchronizeMonitor.signalCalculate2;

public class T2 extends T {

    public T2(int id) {
        super(id);
    }

    @Override
    public void processCommand() {
        inputZ();
        inputB();
        inputMR();

        signalInput();
        waitInput();

        int maxh = calculateMaxH(BEGIN_CALC_IND, END_CALC_IND);
        setMax(maxh);
        int BCh = calculateBCh(BEGIN_CALC_IND, END_CALC_IND);
        setT(BCh);

        signalCalculate1();
        waitCalculate1();

        int max2 = getCopymax();
        int t2 = getCopyt();
        int[][] MT2 = getCopyMT();
        calculateMAh(max2, t2, MT2, BEGIN_CALC_IND, END_CALC_IND);

        signalCalculate2();
    }

}

