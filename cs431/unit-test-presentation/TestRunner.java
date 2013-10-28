import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

public class TestRunner {
  public static void main(String[] args) {
    Result result = JUnitCore.runClasses(ExampleClassTest.class);
    if(result.getFailures().size() != 0){

	    for (Failure failure : result.getFailures()) {
	    	System.out.println();
	     	System.out.println(failure.getTestHeader() + " failed");
	      	System.out.println(failure.getMessage());
	      	System.out.println();
	    }
	    System.out.println();
	} else {
		System.out.println();
		System.out.println(result.getRunCount() + " Tests Passed!");
		System.out.println();
	}
  }
} 