public class RefAndNull {
    public static void main(String[] args) {
        Merchandise[] merchandises = new Merchandise[9];
        for(int i = 0; i < merchandises.length; i++) {
            if(i%2 == 0) {
                merchandises[i] = new Merchandise();
            }
        }
        for(int i = 0; i < merchandises.length; i++) {
                System.out.println("index "+ i + ": " + merchandises[i]);
        }
        for(int i = 0; i < merchandises.length; i++) {
            if(i%2 == 0) {
                System.out.println("++++++ index: " + i);
                System.out.println(merchandises[i].name);
                System.out.println(merchandises[i].id);
                System.out.println(merchandises[i].count);
                System.out.println(merchandises[i].price);
            }
        }
    }
}
