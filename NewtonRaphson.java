import java.text.*;

public class NewtonRaphson {
  
  public static DecimalFormat form = new DecimalFormat("0.#####");

  public static double newtonRaphson(double x)
  {
    double f, fp, f1;
    // f =  5sin(x) - x^2 - 1
    f = 5 * Math.sin(x) - Math.pow(x,2) -1;
    // f1 = 5cos(x) - 2x
    fp = 5 * Math.cos(x) - 2 * x;
    // newtons method
    f1 = x - (f/fp);

    if(Math.abs(f1 - x) < .0001)
      return x;
    else
      return newtonRaphson(f1);
  }

  public static void main(String [] args) {
    double answer = newtonRaphson(0.9);
    System.out.println(form.format(answer));
  }

}