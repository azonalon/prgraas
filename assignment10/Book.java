class Book {
    String title, ISBN;
    double price;
    
    Book(String title_, String ISBN_, double price_) {
        title = title_;
        ISBN = ISBN_;
        price = price_;
    }
    
    public String toString() {
       return title + ", " + ISBN + ", " + price; 
    } 
    
    public static void main(String[] args) {
        Book book = new Book("Sprechen Sie Java", "978-3-89864-595-9", 29.90);
        System.out.println(book.toString() + "\n");
    }
}