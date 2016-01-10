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
		Image sign = circle(30, "navy", pen("red", 9));
		sign = overlay(rectangle(60, 9, "red"), sign);
		sign = rotate(-45 - time * 100, sign); // time-based sign rotation
		Image highlight = ellipse(100, 30, "white", 0.5);
		sign = overlay(5, 25, highlight, sign);
		return sign;
	}

	private void onTick(double time) { // time in seconds
		this.time = time;
	}
}
