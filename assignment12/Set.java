public class Set {
    private class Item {
        public String value;
        public Item next;
        public Item(String value, Item next) {
            this.value = value;
            this.next = next;
        }
    }
    
    public class Iterator {
        private int curBucket = -1;
        private Item curItem = null;
        
        private Iterator() {}
        
        public boolean hasNext() {
            if(curItem != null && curItem.next != null) {
                return true;
            }

            for(int bucketNr = curBucket + 1; bucketNr < N; ++bucketNr) {
                if(buckets[bucketNr] != null) {
                    return true;
                }
            }
            return false;
        }
        
        public String next() {
            if(curItem != null && curItem.next != null) {
                curItem = curItem.next;
                return curItem.value;
            }
            
            for(int bucketNr = curBucket + 1; bucketNr < N; ++bucketNr) {
                if(buckets[bucketNr] != null) {
                    curBucket = bucketNr;
                    curItem = buckets[bucketNr];
                    return curItem.value;
                }
            }
            
            return null;
        }
    }
    
    private final int N;
    private Item[] buckets;
    private int n = 0;
    
    public Set() {
        this(4); // calls the other constructor
    }
    
    private Set(int bucketCount) {
        N = bucketCount;
        buckets = new Item[bucketCount];
    }
    
    private int hash(String value) {
        int hash = 0;
        for(char c : value.toCharArray()) {
            hash = hash * 31 + c;
        }
        return Math.abs(hash);
    }
    
    public void add(String s) {
        if(this.contains(s)) {
            return;
        }
        
        int bucketNr = hash(s) % N;
        if(buckets[bucketNr] == null) {
            buckets[bucketNr] = new Item(s, null);
        } else {
            Item i = buckets[bucketNr];
            while(i.next != null) {
                i = i.next;
            }
            i.next = new Item(s, null);
        }
        
        n++;
    }
    
    public void remove(String s) {
        if(!this.contains(s)) {
            return;
        }
        
        int bucketNr = hash(s) % N;
        boolean foundS = false;
        for(Item i = buckets[bucketNr]; i != null; i = i.next) {
            if(i.value.equals(s)) {
                foundS = true;
                if(i.next == null) {
                    buckets[bucketNr] = null;
                    return;
                } else if(i.next.next == null) {
                    i.value = i.next.value;
                    i.next = null;
                    return;
                } else {
                    i.value = i.next.value;
                }
            }
            if(foundS) {
                if(i.next.next == null) {
                    i.value = i.next.value;
                    i.next = null;
                    return;
                } else {
                    i.value = i.next.value;
                }
            }
        }
    }
    
    public boolean contains(String s) {
        int bucketNr = hash(s) % N;
        for(Item i = buckets[bucketNr]; i != null; i = i.next) {
            if(i.value.equals(s)) {
                return true;
            }
        }
        
        return false;
    }
    
    public boolean isEmpty() {
        return n == 0;
    }
    
    public int size() {
        return n;
    }
    
    public Iterator getIterator() {
        return new Iterator();
    }
    
    public Set union(Set other) {
        Set result = new Set();
        
        Iterator iter1 = this.getIterator();
        while(iter1.hasNext()) {
            String s = iter1.next();
            result.add(s);
        }
        
        Iterator iter2 = other.getIterator();
        while(iter2.hasNext()) {
            String s = iter2.next();
            result.add(s);
        }
        
        return result;
    }

    public Set intersection(Set other) {
        Set result = new Set();
        
        Iterator iter = other.getIterator();
        while(iter.hasNext()) {
            String s = iter.next();
            if(this.contains(s)) {
                result.add(s);
            }
        }
        
        return result;
    }   

    public Set difference(Set other) {
        Set result = new Set();
        
        Iterator iter = this.getIterator();
        while(iter.hasNext()) {
            String s = iter.next();
            if(!other.contains(s)) {
                result.add(s);
            }
        }
        
        return result;
    }
    
    public boolean isSubsetOf(Set other) {
        boolean result = true;
        
        Iterator iter = this.getIterator();
        while(iter.hasNext()) {
            String s = iter.next();
            if(!other.contains(s)) {
                result = false;
                break;
            }
        }
        
        return result;
    }
    
    public String toString() {
        String out = "Set(";
        Iterator iter = getIterator();
        while(iter.hasNext()) {
            out += iter.next();
            if(iter.hasNext()) {
                out += ", ";
            }
        }
        out += ")";
        return out;
    }
    
    public static void main(String[] args) {
        Set set = new Set();
        
        String[] testWordsA = {"there", "which", "picture", "their", "other", "small", "large"};
        String[] testWordsB = {"there", "which", "picture", "change", "spell", "animal", "house"};
        
        System.out.println("Creating set:");
        for(String s : testWordsA) {
            set.add(s);
            System.out.println("Added '" + s + "' to set");
        }
        System.out.println("\nSet size (should be " + testWordsA.length + "): " + set.size());
    
        for(String s : testWordsA) {
            System.out.println("Check if '" + s + "' is indeed in set: " + set.contains(s));
        }

        System.out.println("\nSet contains:");
        Set.Iterator iter = set.getIterator();
        while(iter.hasNext()) {
            System.out.print(iter.next());
            if(iter.hasNext()) {
                System.out.print(", ");
            } else {
                System.out.println("");
            }
        }

        System.out.println("\nCreating other set:");
        Set otherSet = new Set();
        for(String s : testWordsB) {
            otherSet.add(s);
            System.out.println("Added '" + s + "' to other set");
        }

        System.out.println("\nSet A: " + set);
        System.out.println("Set B: " + otherSet);
        
        Set intersection = set.intersection(otherSet);
        System.out.println("\nIntersection contains:");
        System.out.println(intersection);
        
        Set union = set.union(otherSet);
        System.out.println("\nUnion contains:");
        System.out.println(union);
        
        Set difference = set.difference(otherSet);
        System.out.println("\nDifference contains:");
        System.out.println(difference);
        
        // Set subsetA = new Set();
        // subsetA.add(testWordsA[5]);
        // subsetA.add(testWordsA[6]);
        
        // Set subsetB = new Set();
        // subsetB.add(testWordsB[5]);
        // subsetB.add(testWordsB[6]);

        // System.out.println("\nTesting subsets:");
        // System.out.println("Is " + subsetA + " subset of " + set + ": " + subsetA.isSubsetOf(set));
        // System.out.println("Is " + subsetB + " subset of " + set + ": " + subsetB.isSubsetOf(set));
        

        System.out.println("\nRemoving element (" + testWordsA[2] + "):");
        System.out.println("Before: " + set);
        set.remove(testWordsA[2]);
        System.out.println("After: " + set);

    }
}
