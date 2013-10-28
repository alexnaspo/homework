import static org.junit.Assert.assertEquals;
import org.junit.Test;

// 1. explanation
//		a. http://junit.org/
// 2. Add junit.jar to class path
// 3. binary search and test
//		a. example of breaking the test
// 4. TDD with simple sum function
// 5. Continuous deployment

public class ExampleClassTest{

	@Test
	public void testBinarySearch() {
		ExampleClass test = new ExampleClass();

		int[] a = {1,3,5,10,12,20,35};		

		int end = 6;
		int start = 0;

		int resultOne = test.binarySearch(a, 5, start, end);
		int resultTwo = test.binarySearch(a, 35, start, end);
		int resultThree = test.binarySearch(a, 1, start, end);
		int resultFour = test.binarySearch(a, 100, start, end);

		//assertEquals(expected, actual)		
		assertEquals(2,resultOne);
		assertEquals(6,resultTwo);
		assertEquals(0,resultThree);
		assertEquals(-1,resultFour);
 	}

 	@Test
 	public void testSum(){
 		ExampleClass test = new ExampleClass();
 		int a = 5;
 		int b = 10;
 		int sum = 15;

 		int answer = test.sum(a,b);

 		assertEquals(sum, answer);

 	}
}
