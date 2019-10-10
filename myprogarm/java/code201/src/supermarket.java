public class supermarket {
    public static void main(String[] args) {
        merchandise m1 = new merchandise();
        System.out.println("默认值");
        System.out.println("m1 name: " + m1.name + "; m1 id: " + m1.id);
        System.out.println("m1 count: " + m1.count + "; m1 price: " + m1.price);
        m1.name  = "茉莉花茶包 20 包";
        m1.id    = "00099518";
        m1.count = 1000;
        m1.price = 99.9;

        merchandise m2 = new merchandise();
        m2.name  = "可口可乐 330ml";
        m2.id    = "00099519";
        m2.count = 1000;
        m2.price = 3.0;

        //卖出一个m1
        int m1ToSold = 1;
        System.out.println("感谢购买" + m1ToSold + "个" + m1.name +"。 商品单价为" + m1.price + "。 消费总额为" + m1.price * m1ToSold + "。" );
        m1.count -= m1ToSold;
        System.out.println(m1.id + "剩余库存为" + m1.count + "。");

        //卖出三个m2
        int m2ToSold = 3;
        System.out.println("感谢购买" + m2ToSold + "个" + m2.name +"。 商品单价为" + m2.price + "。 消费总额为" + m2.price * m2ToSold + "。" );
        m2.count -= m2ToSold;
        System.out.println(m2.id + "剩余库存为" + m2.count + "。");
    }
}
