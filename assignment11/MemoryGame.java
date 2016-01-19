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
        if(openCardsCount == 2) {
            evaluateOpenCards();
            // check whether the open cards are similar and update the game accordingly
        }
        updateField();
    }
    
    private void onBackClicked(MouseEvent event, Object target) {
        System.out.println("back clicked");
        if(openCardsCount == 0) {
            ((Card) target).setState(Card.State.FRONT);
            openCards[0] = (Card) target;
            openCardsCount++;
            // turn the clicked card around
        } else if(openCardsCount == 1) {
            ((Card) target).setState(Card.State.FRONT);
            openCards[1] = (Card) target;
            openCardsCount++;
            // turn the clicked card around
        } else if(openCardsCount == 2) {
            evaluateOpenCards();
            // check whether the open cards are similar and update the game accordingly
        }
        updateField();
    }
    
    private void evaluateOpenCards() {
        if(openCards[0].equals(openCards[1])) {
            openCards[0].setState(Card.State.EMPTY);
            openCards[1].setState(Card.State.EMPTY);
            openCardsCount = 0;
            // clear similar cards
            pairsFound++;
            pairsTried++;
        } else {
            openCards[0].setState(Card.State.BACK);
            openCards[1].setState(Card.State.BACK);
            openCardsCount = 0;
            // turn different cards around again
            pairsTried++;
        }
    }
    
    private void swapCards(Card[][] a, int y1, int x1, int y2, int x2) {
        Card tmp = a[y1][x1];
        a[y1][x1] = a[y2][x2];
        a[y2][x2] = tmp;
    }
    
    private void shuffleField() {
        Random rnd = new Random(System.currentTimeMillis());
        for (int y = 0; y < ROWS; y++) {
            for (int x = 0; x < COLUMNS; x++) {
                swapCards(field, y, x, rnd.nextInt(ROWS), rnd.nextInt(COLUMNS));
                // swap with a random card on the field
            }
        }
    }
    
    private void updateField() {
        for (int y = 0; y < ROWS; y++) {
            for (int x = 0; x < COLUMNS; x++) {
                fieldImages[y][x] = field[y][x].getImage();
            }
        }
    }

    private Image onDraw() {
        Image grid = grid(fieldImages);
        // arrange cards in a grid
        Image statusBar = text(pairsFound + " pairs found in " + pairsTried + " tries.", 12, "black");
        // show status bar
        return above(grid, statusBar);
    }

    @Override
    public void start(javafx.stage.Stage stage) {
        ApplicationBase.start("Memory", WIDTH, HEIGHT, stage, this::onDraw);
    }

}
