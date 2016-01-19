import static prog1.graphics.Graphics.*;
import prog1.graphics.Image;
import prog1.graphics.MouseFunction;

public class Card {

    private final static int SIZE = 60;
    private final static Image empty = makeImage(' ');

    private final int codePoint; // Unicode code point
    private final Image front; // front side of card
    private final Image back; // back side of card

    public enum State { FRONT, BACK, EMPTY };
    private State state; // whether front or back of card is showing (or field is empty)
    
    public Card(int codePoint, State state) {
        this.codePoint = codePoint;
        front = makeImage(codePoint);
        back  = makeImage(0x26c6);
        this.state = state;
    }

    private static Image makeImage(int codePoint) {
        // for nicer Emojis: install the font at (also works without this font):
        // https://github.com/MorbZ/OpenSansEmoji
        int[] codepoints = { codePoint };
        String emoji = new String(codepoints, 0, codepoints.length);
        Image background = square(70, pen("white", 0));
        Image bounding = square(SIZE, pen("black", 1));
        Image emojiImage = text(emoji, 36, "black");
        return overlay(emojiImage, overlay(bounding, background));
    }
    
    public void setState(State state) {
        this.state = state;
    }

    public Image getImage() {
        switch(state) {
            case FRONT:
                return front;
            case BACK:
                return back;
            default:
                return empty;
        }
    }
    
    public void setFrontClickFunction(MouseFunction cf, Object target) {
        front.setOnMouseClicked(cf, target);
    }
    
    public void setBackClickFunction(MouseFunction cf, Object target) {
        back.setOnMouseClicked(cf, target);
    }
    
    public static void setEmptyClickFunction(MouseFunction cf, Object target) {
        empty.setOnMouseClicked(cf, target);
    }
    
    @Override
    public boolean equals(Object o) {
        if (o == null) return false;
        if (getClass() != o.getClass()) return false;
        Card c = (Card) o;
        if (codePoint == c.codePoint) return true;
        return false;
    }

}
