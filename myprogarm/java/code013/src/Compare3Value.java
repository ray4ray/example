public class Compare3Value {
    public static void main(String[] args){
        int a = 66;
        int b = 66;
        int c = 33;

        if(a == b && b == c ){
            System.out.println("a 和 b c 相等" + a);
        } else if (a > b && a > c){
            System.out.println("a 最大" + a);
        } else if (b > a && b > c) {
            System.out.println("b 最大" + b);
        } else if (c > a && c > b ){
            System.out.println("c 最大" + c);
        } else if (a == b && b > c){
            System.out.println("a 和b 相等且最大" + a);
        } else if (a == c && a> b){
            System.out.println("a 和c 相等且最大" + a);
        }  else if (b == c && a < b) {
            System.out.println("b 和c 相等且最大" + b);
        }
    }
}
