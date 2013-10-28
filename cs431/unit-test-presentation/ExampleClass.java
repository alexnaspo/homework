public class ExampleClass {
    // returns the index of value if found
    int binarySearch(int[] array, int value, int left, int right) {
        if (left > right)
            return -1;
        int middle = (left + right) / 2;
        if (array[middle] == value)
            return middle;
        else if (array[middle] > value)
            return binarySearch(array, value, left, middle - 1);
        else
            return binarySearch(array, value, middle + 1, right);           
    }

    int sum(int a, int b){
        return a + b;
    }
}