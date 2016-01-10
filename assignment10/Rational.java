import prog1javalib.Base;

/*
Windows:
Compile: javac -cp .;prog1javalib.jar Rational.java
Run: java -cp .;prog1javalib.jar Rational

OS X:
Compile: javac -cp .:prog1javalib.jar Rational.java
Run: java -cp .:prog1javalib.jar Rational
*/

public class Rational {

    public Rational(int numerator, int denominator) {
        if (denominator == 0) {
            throw new RuntimeException("zero denominator");
        }
        // todo: implement
    }
    
    public static Rational r(int numerator, int denominator) {
        return new Rational(numerator, denominator);
    }

    @Override
    public String toString() {
        // todo: implement
        return "";
    }
    
    @Override
    public boolean equals(Object o) {
        // todo: implement
        if (o == null) return false;
        if (o instanceof Integer) {
            // ...
        }
        // ...
        if (o instanceof Rational) {
            // ...
        }
        // ...
        return false;
    }

    public Rational plus(Rational r) {
        // todo: implement
        return r(1, 1);
    }

    public Rational minus(Rational r) {
        // todo: implement
        return r(1, 1);
    }

    public Rational times(Rational r) {
        // todo: implement
        return r(1, 1);
    }

    public Rational dividedBy(Rational r) {
        // todo: implement
        return r(1, 1);
    }
    
    public Rational inverse() { 
        // todo: implement
        return r(1, 1);
    }

    public Rational plus(int i) {
        // todo: implement
        return r(1, 1);
    }

    public Rational minus(int i) {
        // todo: implement
        return r(1, 1);
    }

    public Rational times(int i) {
        // todo: implement
        return r(1, 1);
    }

    public Rational dividedBy(int i) {
        // todo: implement
        return r(1, 1);
    }
    
    private static int greatestCommonDivisor(int x, int y) {
        // todo: implement
        return 0;
    }
    
    public static void rationalTest() {
        // 6/8 --> 3/4
        Base.checkExpect(r(6, 8), r(3, 4));
        Base.checkExpect(r(6, 8).toString(), "3/4");

        // 6/-8 --> -3/4
        Base.checkExpect(r(6, -8), r(3, -4));
        Base.checkExpect(r(6, -8).toString(), "-3/4");

        // 1/-2 --> -1/2
        Base.checkExpect(r(1,-2), r(-1, 2));
        Base.checkExpect(r(1,-2).toString(), "-1/2");

        // 1/2 + 3/4 = 5/4
        Base.checkExpect(r(1, 2).plus(r(3, 4)), r(5, 4));
        Base.checkExpect(r(1, 2).plus(r(3, 4)).toString(), "5/4");

        // 1/2 - 3/4 = -1/4
        Base.checkExpect(r(1, 2).minus(r(3, 4)), r(-1, 4));
        Base.checkExpect(r(1, 2).minus(r(3, 4)).toString(), "-1/4");

        // 1/3 + 2/3 = 1
        Base.checkExpect(r(1, 3).plus(r(2, 3)), 1);
        Base.checkExpect(r(1, 3).plus(r(2, 3)).toString(), "1");
                
        // 1/3 - 1/3 = 0
        Base.checkExpect(r(1, 3).minus(r(1, 3)), 0);
        Base.checkExpect(r(1, 3).minus(r(1, 3)).toString(), "0");
                
        // 1/3 - 4/3 = -1
        Base.checkExpect(r(1, 3).minus(r(4, 3)), -1);
        Base.checkExpect(r(1, 3).minus(r(4, 3)).toString(), "-1");
                
        // 1/2 * 4/3 = 2/3
        Base.checkExpect(r(1, 2).times(r(4, 3)), r(2, 3));
                
        // -1/2 * 4/3 = -2/3
        Base.checkExpect(r(-1, 2).times(r(4, 3)), r(-2, 3));
                
        // (1/2) / (4/3) = 3/8
        Base.checkExpect(r(1, 2).dividedBy(r(4, 3)), r(3, 8));
                
        // (-1/2) / (4/3) = -3/8
        Base.checkExpect(r(-1, 2).dividedBy(r(4, 3)), r(-3, 8));
        
    }

    public static void main(String[] args) {
        rationalTest();
        Base.summary();
    }

}
