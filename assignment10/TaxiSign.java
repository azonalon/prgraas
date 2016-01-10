import prog1graphics.ApplicationBase;
import prog1graphics.Image;
import static prog1graphics.Graphics.*;

// Windows: ;
// Mac: :

// .class dirs:
// jar cf prog1javalib.jar prog1graphics prog1javalib
// .java dirs:
// javac -cp .:prog1javalib.jar TaxiSign.java
// java -cp .:prog1javalib.jar TaxiSign

/**
 *
 * @author michaelrohs
 */
public class TaxiSign extends javafx.application.Application {
	
	public TaxiSign() {
	}

	@Override
	public void start(javafx.stage.Stage stage) throws Exception {
		ApplicationBase.start("Sign", 200, 300, stage, this::onDraw);
	}

	private Image onDraw() {
		Image sign = circle(30, "navy", pen("red", 9));
		sign = overlay(rectangle(60, 9, "red"), sign);
		sign = rotate(-45, sign);
		return sign;
	}

}
