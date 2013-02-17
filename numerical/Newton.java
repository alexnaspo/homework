import java.text.*;
public class Newton {
        public static DecimalFormat form = new DecimalFormat("0.##");
        public static void main(String [] args) {
                double answer = newt(0.01);
                System.out.println("Monthly rate: " + answer);
                System.out.println("APR: %" + form.format((answer * 1200)) );
        }

        public static double newt(double x)
        {
                //break down fx into sub parts for readability
                double y = Math.pow((1 + x), 360);
                double z = (1 - (100 * x));
                double n = Math.pow((1 + x), 359);

                //calculate fx
                double fx = (y * z) - 1;
                //calculate fpx
                double fpx = (360 * z * n) - (100 * y);

                //newtons method
                double gx = x - (fx/fpx);

                if(Math.abs(gx - x) < .00000001)
                        return x;
                else
                        return newt(gx);
        }

}
