public class IfElseBaozi {
    public static void main(String[] args){
        int baoziNum = 3;
        boolean baoziGangChulong = false;
        //boolean baoziGangChulong = true;
        if(baoziGangChulong){
            baoziNum += 2;
            System.out.println("买了"+ baoziNum + "个肉包子");
        } else {
            System.out.println("买了"+ baoziNum + "个肉包子");
        }
    }
}
