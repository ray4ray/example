public class AutoConvert {
    public static void main(String[] args){
        int intVal = 99;
        long longValue = intVal;
        long longValue2 = intVal + 1;
        System.out.println(longValue2);

        float floatVal = 11.32f;
        double doubleVal = floatVal;
        double doubleVal2 = floatVal * 2;
        System.out.println(doubleVal2);

        doubleVal = longValue;
        doubleVal = intVal;

        floatVal  = intVal;
        floatVal  = longValue;

        int a  = 99;
        double b = 5;
        System.out.println(a/b);

        char ch = 'A';
        int chNum = ch;
        int chNumCalc = ch + 10;
        System.out.println(ch);
        System.out.println(chNum);
        System.out.println(chNumCalc);
    }
}
