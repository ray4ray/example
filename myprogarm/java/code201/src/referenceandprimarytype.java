public class referenceandprimarytype {
    public static void main(String[] args) {
        merchandise m1;
        m1 = new merchandise();
        merchandise m2 = new merchandise();
        merchandise m3 = new merchandise();
        merchandise m4 = new merchandise();
        merchandise m5 = new merchandise();

        m1 = m5;
        System.out.println("m1 = " + m1);
        System.out.println("m1 = " + m2);
        System.out.println("m1 = " + m3);
        System.out.println("m1 = " + m4);
        System.out.println("m1 = " + m5);

        merchandise m6;hang
        m6 = m5;
        System.out.println("m6 = " + m6);
        m6 = m1;
        System.out.println("m6 = " + m6);

        System.out.println("m1 = " + m1);
        System.out.println("m1 = " + m2);
        System.out.println("m1 = " + m3);
        System.out.println("m1 = " + m4);
        System.out.println("m1 = " + m5);

    }
}
