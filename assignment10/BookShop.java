import prog1javalib.*;

class BookShop {
    Book[] books = null;
    int max_book_number;
    private int current_book_number = 0;
    
    void printBooks() {
        for(int i = 0; i < current_book_number; i++) {
            System.out.println(books[i].toString());
        }
    }
    
    BookShop(int max_book_number_) {
        max_book_number = max_book_number_;
        books = new Book[max_book_number_];
    }
    
    Book getBook(String title) {
        for(int i = 0; i < current_book_number; i++) {
           if(title.equals(books[i].title)) {
               return books[i];
           } 
        }
        return null;
    }
    
    void addBook(String title, String isbn, Double price) {
        if (getBook(title) != null) {
            return;
        }
        
        if(current_book_number < max_book_number) {
            books[current_book_number] = new Book(title, isbn, price); 
            current_book_number += 1;
        } 
    }
    public static void main(String[] args){
        BookShop book_shop = new BookShop(5);
        book_shop.addBook("Grundkurs Theoretische Physik 3", "978-3-540-20509-8", 39.99);
        book_shop.addBook("Grundkurs Theoretische Physik 1", "978-3-540-21474-8", 39.99);
        book_shop.addBook("Grundkurs Theoretische Physik 2", "978-3-642-12949-0", 39.99);
        book_shop.addBook("Analysis II", "978-3-76105-0", 29.95);
        book_shop.addBook("Sprechen Sie Java", "978-3-89864-595-9", 29.90);
        
        System.out.println("Enter a book Name:");
        while(true) {
        String s = Base.stringInput();
        Book b = book_shop.getBook(s);
        if (b == null) {
            System.out.println("Book not found!");
        }
        else{
            System.out.println("Book found!");
            System.out.println(b.toString());
        }
        }

    }
}
