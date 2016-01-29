import prog1.base.Base;

// Windows:
// javac -cp .;prog1javalib.jar BinarySearchTree.java
// java -cp .;prog1javalib.jar BinarySearchTree

// OS X:
// javac -cp .:prog1javalib.jar BinarySearchTree.java
// java -cp .:prog1javalib.jar BinarySearchTree


public class BinarySearchTree {
    
    private class Node {
        private int value;
        private Node left, right;
        
        private Node(int value, Node left, Node right) {
            this.left = left;
            this.value = value;
            this.right = right;
        }

        private void add(int i) {
            if (i < value) {
                if (left == null) {
                    left = new Node(i, null, null); 
                } else {
                    left.add(i);
                }
            } else { // n >= value
                if (right == null) {
                    right = new Node(i, null, null); 
                } else {
                    right.add(i);
                }
            }
        }
        
        private int size() {
            if( this.left == null && 
                this.right == null )
                return 1;
            else if(this.left == null) 
                return right.size() + 1; 
            else if(this.right == null)
                return left.size() + 1;
            else 
                return right.size() + left.size() + 1;
        }
        
        private boolean contains(int i) {
            if (this.value == i)
                return true;
            if(this.right != null && i > this.value)
                return this.right.contains(i);
            if(this.left != null && i < this.value)
                return this.left.contains(i); 
            return false;
        }
        
        private int numberOfLeaves() {
            if( this.left == null && 
                this.right == null )
                return 1;
            else if(this.left == null) 
                 return right.numberOfLeaves(); 
            else if(this.right == null)
                return left.numberOfLeaves();
            else 
                return right.numberOfLeaves() + left.numberOfLeaves();
        }
        
        private int abs(int i) {
            return i < 0 ? -i : i;
        }
        
        private int nearest(int target, int nearestSoFar) {
            int valueDistance = abs(this.value - target);
            int nearestNow = this.value;
            if(valueDistance > abs(nearestSoFar - target))
                nearestNow = nearestSoFar;
                
            if(this.right != null && target > this.value)
                return this.right.nearest(target, nearestNow);
            if(this.left != null && target < this.value)
                return this.left.nearest(target, nearestNow);
            
            return nearestNow;
        }
        
        public String toString() { 
            if (left == null && right == null) {
                return String.valueOf(value);
            }
            return "(" + (left != null ? left : "_") + 
                    "," + value + "," + 
                    (right != null ? right : "_") + ")";
        }

    } // class Node
    
    private Node root = null;

    public void add(int i) {
        if (root == null) {
            root = new Node(i, null, null); 
        } else {
            root.add(i);
        }
    }   
    
    public int size() { 
        if (root == null) {
            return 0;
        } else {
            return root.size();
        }
    }
    
    public boolean contains(int i) { 
        if (root == null) {
            return false;
        } else {
            return root.contains(i); 
        }
    }
    
    public int numberOfLeaves() {
        if (root == null) {
            return 0;
        } else {
            return root.numberOfLeaves();
        }
    }

    public String toString() {
        if (root == null) {
            return "()";
        } else {
            return root.toString();
        }
    }

    public int nearest(int value) {
        if (root == null) {
            return Integer.MAX_VALUE;
        } else {
            return root.nearest(value, Integer.MAX_VALUE);
        }
    }
    
    private static void test() {
        BinarySearchTree tree = new BinarySearchTree();
        int[] values = {1, 3, -3, -64, 11, 50, -52, 24, -43, 37};
        for (int v  : values) {
            tree.add(v);
        }
        Base.println(tree);
        Base.checkExpect(tree.contains(values[2]), true);
        Base.checkExpect(tree.contains(values[2] + 1000), false);
        Base.checkExpect(tree.size(), values.length);
        Base.checkExpect(tree.numberOfLeaves(), 2);
        Base.checkExpect(tree.nearest(3), 3);
        Base.checkExpect(tree.nearest(36), 37);
        Base.checkExpect(tree.nearest(0), 1);
        Base.checkExpect(tree.nearest(-100), -64);
        Base.summary();
    }
    
    public static void main(String[] args) {
        test();
    }
}
