import prog1graphics.ApplicationBase;
import prog1graphics.Image;
import static prog1graphics.Graphics.*;

// Windows: ;
// Mac:     :
// javac -cp .:prog1javalib.jar StopWatch.java
// java -cp .:prog1javalib.jar StopWatch

public class StopWatch extends javafx.application.Application {
    
    private double time;
    
    public StopWatch() {
    }
    
    @Override
    public void start(javafx.stage.Stage stage) throws Exception {
        ApplicationBase.start("Stop Watch", 110, 80, stage, this::onDraw);
        ApplicationBase.setOnTick(this::onTick); // register tick function
    }
    
    private Image onDraw() {
        int r = 30;
        Image sign = circle(30, "transparent", pen("black", 2));
        Image big_hand = overlay(-12.5, 0, rectangle(25, 1, "black"), sign);
        Image small_hand = overlay(-10, 0, rectangle(20, 3, "black"), sign);
        Image sign_single_marker = overlay(-25,0,rectangle(10, 2, "black"), sign);
        int angle = 0;
        for(int phi = 0; phi < 360; phi += 30) {
            sign = overlay(rotate(phi, sign_single_marker), sign); // time-based phi rotation
        }
        
        Image clock = overlay(rotate(90 - time * 360/60, big_hand), sign); // time-based sign rotation
        clock = overlay(rotate(90 - time * 360/60/60, small_hand), clock); // time-based sign rotation
        clock = overlay(0, -10, text(String.format("%.2f", time), 8, pen("black", 1)),clock);
        Image highlight = ellipse(100, 30, "white", 0.5);
        //sign = overlay(5, 25, highlight, sign);
        return clock;
    }
    
    private void onTick(double time) { // time in seconds
        this.time = time;
    }
}
