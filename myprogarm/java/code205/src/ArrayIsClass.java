public class ArrayIsClass {
    public static void main(String[] args) {
        int[]  intArr;
        intArr = new int[1];
        intArr = new int[2];

        double[][][]  double3DArray = new double[2][2][4];

        int[] a1 = new int[9];
        int[] a2 = new int[0];
        a2 = a1;
        System.out.println("a2.length=" + a2.length);
        double[] a3 = new double[5];
        double3DArray[1][1] = a3;
    }
}
