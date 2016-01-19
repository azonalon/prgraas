import java.util.Random;
import javafx.scene.input.MouseEvent;
import prog1.graphics.ApplicationBase;
import prog1.graphics.Image;
import static prog1.graphics.Graphics.*;
import static prog1.functional.Functional.*;

// Windows:
// javac -cp .;prog1javalib.jar BarChart.java
// java -cp .;prog1javalib.jar BarChart

// OS X:
// javac -cp .:prog1javalib.jar BarChart.java
// java -cp .:prog1javalib.jar BarChart

public class BarChart extends javafx.application.Application {
    
    private final int[] data = new int[10];
    private int selected = -1;
    private String status = "status";
    private final int PLOT_HEIGHT = 270;
    private final int STATUSLINE_HEIGHT = 30;
    
    public BarChart() {
        Random rnd = new Random();
        for (int i = 0; i < data.length; i++) {
            data[i] = rnd.nextInt(200);
        }
    }
    
    private int barSum(int index) {
        // sums the bars until and excluding index 
        int sum = 0;
        for(int x = 0; x < index; x++) {
            sum += data[x];
        }
        return sum; 
    }
    
    private Image statuslineImage() {
        if (selected != -1) 
            return overlay("center", "center",
                           text(String.format("sum = %d", barSum(selected)), 16.0, "black"),
                           rectangle(300,30, "white", 0.0)
            );
        else
            return rectangle(300,30, "white", 0.0);
    }
    
    private Image barImage(int value, int index) {
        // todo: implement
        // int bar_height = round(value/PLOT_HEIGHT) *  ;
        Image background = rectangle(50, 270, "white", 0.0);
        // transparent background
        String bar_color = index > selected ? "grey" : "green";
        
        Image bar = rectangle(40, value, bar_color, 1.0);
        
        bar.setOnMouseMoved(
            (event, target) -> { 
                this.selected = index; 
            }
            , null);
        
        background.setOnMouseMoved(
            (event, target) -> { 
                this.selected = -1; 
            }
            , null);
        
        Image result = overlay("middle", "bottom", 0, 30, bar, background);
        result = overlay("center", "bottom", 0, 15, text(String.format("%d", value), 12.0, "black"), result);
        return result;
    }
    
    private Image onDraw() {
        Image[] bars = map(data, this::barImage);
        Image background = rectangle(500, 270, color(245, 255, 250), pen("black"));
        Image result = beside(bars, 0, 9);
        result = overlay(result, background);
        result = above(result, statuslineImage());
        //result = above(result, )
        return result;
        // todo: implement
    }
    
    @Override
    public void start(javafx.stage.Stage stage) {
        ApplicationBase.start("Bar Chart", 500, 300, stage, this::onDraw);
    }
    
}
