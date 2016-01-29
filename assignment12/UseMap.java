import prog1.base.Base;
import prog1.graphics.*;
import java.util.Random;
import static prog1.graphics.Graphics.*;

// Windows:
// javac -cp .;prog1javalib.jar UseMap.java
// java -cp .;prog1javalib.jar UseMap

// OS X:
// javac -cp .:prog1javalib.jar UseMap.java
// java -cp .:prog1javalib.jar UseMap

public class UseMap extends javafx.application.Application {

    Random generator = new Random();
    private Map map = new Map();

    public UseMap() {
        map.put("dog", "Hund");
        map.put("whale", "Wal");
        map.put("cow", "Kuh");
        map.put("donkey", "Esel");
        // Paare bis bucket.length() == 4
        // 21, 13, 11, 19, 16
        // Sie scheinen nicht gleichverteilt zu sein, 
        // die Einträge sind gefühlt weniger in den buckets
        // 0, 2, 3 und 8 zu finden
    }
    
    @Override
    public void start(javafx.stage.Stage stage) { // entry point
        // window title, width, and height; drawing method
        ApplicationBase.start("UseMap", 400, 400, stage, this::onDraw);
        ApplicationBase.setOnKeyPressed(this::onKeyPress);
    }

    private Image onDraw() {
        return map.toImage();
    }
    
    private void onKeyPress(String event) {
        int randomNumber = generator.nextInt(100);
        map.put(String.format("%d", randomNumber), String.format("%d", 2 * randomNumber));
    }
    
}
