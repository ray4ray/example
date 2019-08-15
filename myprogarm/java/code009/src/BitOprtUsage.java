public class BitOprtUsage {
    public static void main(String[] args){
        int base = 1;
        int is_student_mask = base << 1;
        int is_programmer_mask = base << 2;
        int is_driver_mask = base << 3;
        int is_painter_mask = base << 4;

        int data = 5;
        boolean isStudent = (data & is_student_mask) != 0;
        System.out.println(isStudent);
        boolean isProgrammer = (data & is_programmer_mask) != 0;
        System.out.println(isProgrammer);
        boolean isdriver = (data & is_driver_mask) != 0;
        System.out.println(isdriver);
        boolean isPainter = (data & is_painter_mask) != 0;
        System.out.println(isPainter);
    }
}
