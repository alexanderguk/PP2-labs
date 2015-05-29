package thread;

import static monitor.ResourceMonitor.*;
import static monitor.SynchronizeMonitor.*;
import static main.Data.*;
import static monitor.SynchronizeMonitor.signalCalculate2;

public class T6 extends T {

    public T6(int id) {
        super(id);
    }

    @Override
    public void processCommand() {
        inputC();
        inputMT();

        signalInput();
        waitInput();

        int maxh = calculateMaxH(BEGIN_CALC_IND, END_CALC_IND);
        setMax(maxh);
        int BCh = calculateBCh(BEGIN_CALC_IND, END_CALC_IND);
        setT(BCh);

        signalCalculate1();
        waitCalculate1();

        int max6 = getCopymax();
        int t6 = getCopyt();
        int[][] MT6 = getCopyMT();
        calculateMAh(max6, t6, MT6, BEGIN_CALC_IND, END_CALC_IND);

        signalCalculate2();
    }

}

