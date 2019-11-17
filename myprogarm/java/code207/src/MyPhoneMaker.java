public class MyPhoneMaker {
    public static void main(String[] args) {
        Phone phone = new Phone();
        phone.hasFigurePrintUnlocker = ture;
        phone.price = 1999;
        phone.screen = new Screen();
        phone.screen.producer = "京东方";
        phone.screen.size = 8.8;

        CPU cpu = new CPU();
        cpu.producer = "三星";
        cpu.speed = 3.5;

        Memory memory = new Memory();
        memory.capacity = 4;
        memory.producer = "三星";

        Storage storage = new Storage();
        storage.capacity = "Intel";
        storage.capacity = 128;

        phone.mainboard = new Mainboard();
        phone.mainboard.cpu = cpu;
        phone.mainboard.memory = memory;
        phone.mainboard.storage = storage;

        phone.mainboard.model = "EA8888";
        phone.mainboard.year  = 2019;

        Memory m1 = new Memory();
        Storage s1 = new Storage();
        //s1 = m1;
    }
}
