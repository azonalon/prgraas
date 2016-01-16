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
	
	public BarChart() {
		Random rnd = new Random();
		for (int i = 0; i < data.length; i++) {
			data[i] = rnd.nextInt(200);
		}
	}

	private Image barImage(int value, int index) {
		// todo: implement
		return text("todo", 36, "red");
	}

	private Image onDraw() {
		return barImage(data[0], 0);
		// Image[] bars = map(data, this::barImage);
		// todo: implement
	}

	@Override
	public void start(javafx.stage.Stage stage) {
		ApplicationBase.start("Bar Chart", 500, 300, stage, this::onDraw);
	}

}
