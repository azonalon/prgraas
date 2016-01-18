import java.util.Random;
import javafx.scene.input.MouseEvent;
import prog1.graphics.ApplicationBase;
import prog1.graphics.Image;
import static prog1.graphics.Graphics.*;

// Windows:
// javac -cp .;prog1javalib.jar MemoryGame.java
// java -cp .;prog1javalib.jar MemoryGame

// OS X:
// javac -cp .:prog1javalib.jar MemoryGame.java
// java -cp .:prog1javalib.jar MemoryGame

public class MemoryGame extends javafx.application.Application {

    private final static int COLUMNS = 8;
    private final static int ROWS = 8;
    private final double WIDTH = COLUMNS * 70; // window width
    private final double HEIGHT = ROWS * 70 + 25; // window height
    private final Card[][] field = new Card[ROWS][COLUMNS];
    private final Image[][] fieldImages = new Image[ROWS][COLUMNS];
    
    private final Card[] openCards = new Card[2]; // currently open cards (at most two)
    private int openCardsCount = 0;

    private int pairsFound = 0;
    private int pairsTried = 0;
    
    public MemoryGame() {
        int i = 0;
        for (int y = 0; y < ROWS; y++) {
            for (int x = 0; x < COLUMNS; x++) {
                Card card = new Card(0x2600 + i/2, Card.State.BACK);
                card.setFrontClickFunction(this::onFrontClicked, card);
                card.setBackClickFunction(this::onBackClicked, card);
                field[y][x] = card;
                i++;
            }
        }
        Card.setEmptyClickFunction(this::onFrontClicked, null);
        shuffleField();
        updateField();
    }
    
    private void onFrontClicked(MouseEvent event, Object target) {
        System.out.println("front clicked"); 
        // todo: process the event and update the game accordingly
        ((Card) target).setState(Card.State.BACK);
        updateField();
    }
    
    private void onBackClicked(MouseEvent event, Object target) {
        System.out.println("back clicked"); 
        // todo: process the event and update the game accordingly
        ((Card) target).setState(Card.State.FRONT);
        updateField();
    }
    
    private void evaluateOpenCards() {
        // todo: evaluate the currently open cards (if any) 
        // and change the state of the game accordingly
    }
    
    private void shuffleField() {
        Random rnd = new Random(System.currentTimeMillis());
        // todo: shuffle the field (hint: use rnd.nextInt(UPPER_BOUND) to get a random integer)
    }
    
    private void updateField() {
        for (int y = 0; y < ROWS; y++) {
            for (int x = 0; x < COLUMNS; x++) {
                fieldImages[y][x] = field[y][x].getImage();
            }
        }
    }

    private Image onDraw() {
        // todo: output the field above a status line (hint: use grid to output the field)
        return grid(fieldImages);
    }

    @Override
    public void start(javafx.stage.Stage stage) {
        ApplicationBase.start("Memory", WIDTH, HEIGHT, stage, this::onDraw);
    }

}
