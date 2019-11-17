public class CheckBeforeUse {
    public static void main(String[] args) {
        Merchandise[] merchandises = new Merchandise[9];
        for(int i = 0; i < merchandises.length; i++) {
            if(i%2 == 0) {
                merchandises[i] = new Merchandise();
            }
        }

        //merchandises[7].name = "不存在的商品，不存在的名字";
        for(int i = 0; i < merchandises.length; i++) {
            if(null != merchandises[i]) {
                merchandises[i].name = "商品" + i;
            }
        }
        for(int i = 0; i < merchandises.length; i++) {
            if(null != merchandises[i]) {
                System.out.println("index " + i + ": " + merchandises[i].name);
            }
        }
    }
}
