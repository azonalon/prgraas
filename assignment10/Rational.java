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
    
    private int num, denom;

    public Rational(int numerator, int denominator) {
        if (denominator == 0) {
            throw new RuntimeException("zero denominator");
        }
        num = numerator / greatestCommonDivisor(numerator, denominator);
        denom = denominator / greatestCommonDivisor(numerator, denominator);
    }
    
    public static Rational r(int numerator, int denominator) {
        return new Rational(numerator, denominator);
    }

    @Override
    public String toString() {
        if(denom == 1) {
            return Integer.toString(num);
        } else {
            return num + "/" + denom;
        }
    }
    
    @Override
    public boolean equals(Object o) {
        if (o == null) return false;
        if (o instanceof Integer) {
            if(num == (int) o && denom == 1) return true;
        }
        if (o instanceof Rational) {
            if(num == ((Rational) o).num && denom == ((Rational) o).denom) return true;
        }
        return false;
    }

    public Rational plus(Rational r) {
        return r(num * r.denom + denom * r.num, denom * r.denom);
    }

    public Rational minus(Rational r) {
        return plus(r(-r.num,r.denom));
    }

    public Rational times(Rational r) {
        return r(num * r.num, denom * r.denom);
    }

    public Rational dividedBy(Rational r) {
        return times(r.inverse());
    }
    
    public Rational inverse() {
        return r(denom, num);
    }

    public Rational plus(int i) {
        return plus(r(i, 1));
    }

    public Rational minus(int i) {
        return minus(r(i, 1));
    }

    public Rational times(int i) {
        return times(r(i, 1));
    }

    public Rational dividedBy(int i) {
        return dividedBy(r(i, 1));
    }
    
    private static int greatestCommonDivisor(int x, int y) {
        if(x * y >= 0) {
            if(x >= 0) {
                if(x == 0) {
                    return y;
                } else {
                    while(y != 0) {
                        if(x > y) {
                            x = x - y;
                        } else {
                            y = y - x;
                        }
                    }
                    return x;
                }
            } else {
                return -greatestCommonDivisor(-x, -y);
            }
        } else if(x < 0) {
            return greatestCommonDivisor(-x, y);
        } else {
            return -greatestCommonDivisor(x, -y);
        }
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
        
        // (1/2) + 1 = 3/2
        Base.checkExpect(r(1, 2).plus(1), r(3, 2));
        
        // (1/2) - 1 = -1/2
        Base.checkExpect(r(1, 2).minus(1), r(-1, 2));
        
        // (1/2) * 2 = 1/1
        Base.checkExpect(r(1, 2).times(2), r(1, 1));
        
        // (1/2) / 2 = 1/4
        Base.checkExpect(r(1, 2).dividedBy(2), r(1, 4));
    }

    public static void main(String[] args) {
        rationalTest();
        Base.summary();
    }

}
