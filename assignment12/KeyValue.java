import prog1.graphics.Image;
import static prog1.graphics.Graphics.*;

public class KeyValue {
    public String key; // e.g., dog
    public String value; // e.g., Hund
    public KeyValue next; // link to next element in same bucket
    public final int image_width = 150;
    public final int image_height = 30;
    public final int image_font_size = 12;

    public KeyValue(String key, String value, KeyValue next) {
        this.key = key; 
        this.value = value;
        this.next = next;
    }
    
    public Image toImage() {
        
        Image v = rectangle(
            image_width,
            image_height,
            "transparent",
            pen("black")
        );
        
        v = overlay("center", "center",
                    text(key + ", " + value, 12, "black"), 
                    v
                   );
        
        return v;
    }
}
