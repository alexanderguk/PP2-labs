package thread;

import static monitor.ResourceMonitor.*;
import static monitor.SynchronizeMonitor.*;
import static main.Data.*;
import static monitor.SynchronizeMonitor.signalCalculate2;

public class T5 extends T {

    public T5(int id) {
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

        int max5 = getCopymax();
        int t5 = getCopyt();
        int[][] MT5 = getCopyMT();
        calculateMAh(max5, t5, MT5, BEGIN_CALC_IND, END_CALC_IND);

        signalCalculate2();
    }

}

