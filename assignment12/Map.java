import static prog1.functional.Functional.*;
import static prog1.graphics.Graphics.*;
import prog1.graphics.Image;

public class Map {
    
    private final static int N = 10; // should be more buckets in practice
    private final KeyValue[] buckets = new KeyValue[N];
    private final Image arrow = polygon(
        array(-5., -5., -5., 5., 5., 5., 5., 10., 10., 0., 5., -10., 5., -5. ), pen("black")
    );
    

    private int hash(String key) {      
        int n = key.length();
        int hash = 0;
        for (int i = 0; i < n; i++) 
            hash = hash * 31 + key.charAt(i); // compute index from characters
        if (hash < 0) hash = -hash;
        return hash;
    }

    public void put(String key, String value) {
        int h = hash(key) % N;
        // add key-value association to front of list in bucket h
        // (does not check whether key is already in map!)
        buckets[h] = new KeyValue(key, value, buckets[h]);
    }

    public String get(String key) {
        int h = hash(key) % N;
        // walk through list in bucket h
        for (KeyValue kv = buckets[h]; kv != null; kv = kv.next)
            if (key.equals(kv.key))
                return kv.value; // found key, return value
        return null; // key not found, return null
    }
    
    public Image toImage() {
        Image[] bucket_images = new Image[N];
        for(int iBucket = 0; iBucket < N; iBucket++) {
            bucket_images[iBucket] = bucketToImage(iBucket);
        }
        return above("left", bucket_images, 0, N);
        // Todo: may be N, not N - 1
    }
    public Image bucketToImage(int bucket_number) {
        KeyValue node = buckets[bucket_number];
        Image bucket_image = rectangle(
            70,
            30,
            "transparent", pen("black")
        ); 
        
        bucket_image = overlay( "center", "center",
            text(String.format("%d", bucket_number), 12.0, "black"),
            bucket_image
        );
        
        // bucket_image = beside("center", bucket_image,
        //                       arrow);
        
        while(node != null) {
            bucket_image = beside("center", bucket_image,
                                  arrow);
            bucket_image = beside("below", bucket_image, 
                node.toImage()
            );
            node = node.next;
        }
        return bucket_image;
    }
}