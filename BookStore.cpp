#include <iostream>
using namespace std;

enum class SortType { Title, Author, Year };

class Book {
public:
    string title;
    string author;
    int year;
    double price;

    // конструктор
    Book(string b_title, string b_author, int b_year, double b_price) {
        title = b_title;
        author = b_author;
        year = b_year;
        price = b_price;
    }
    // конструктор по умолчанию
    Book() : title(""), author(""), year(0), price(0.0) {}
};

class BookStore {
private:
    static const int MAX = 100;
    Book books[MAX];
    int count = 0;

public:
    void addBook(Book new_book) {
        if (count < MAX) {
            books[count] = new_book;
            count++;
        }
        else {
            cout << "The store is full. Remove some books to add new ones.\n";
        }
    }
    void removeBook(string title) {
        for (int i = 0; i < count; i++) {
            if (books[i].title == title) {
                for (int j = i; j < count - 1; j++) {
                    books[j] = books[j + 1];
                }
                count--;
                cout << "The book successfully removed\n";
                return;
            }
        }
        cout << "Book not found\n";
    }
    Book* findBook(string title) {
        for (int i = 0; i < count; i++) {
            if (books[i].title == title) {
                return &books[i];
            }
        }
        return 0;
    }

    void listBooks(SortType sortType) {
        Book tempBooks[MAX];
        for (int i = 0; i < count; i++) {
            tempBooks[i] = books[i];
        }
        // пузырьковая сортировка
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                bool shouldSwap = false;
                if (sortType == SortType::Title &&
                    tempBooks[j].title > tempBooks[j + 1].title) {
                    shouldSwap = true;
                }
                else if (sortType == SortType::Author &&
                    tempBooks[j].author > tempBooks[j + 1].author) {
                    shouldSwap = true;
                }
                else if (sortType == SortType::Year &&
                    tempBooks[j].year > tempBooks[j + 1].year) {
                    shouldSwap = true;
                }
                if (shouldSwap) {

                    Book temp = tempBooks[j];
                    tempBooks[j] = tempBooks[j + 1];
                    tempBooks[j + 1] = temp;
                }
            }
        }

        // вывод отсортированных книг
        for (int i = 0; i < count; ++i) {
            cout << "Title: " << tempBooks[i].title << "\n";
            cout << "Author: " << tempBooks[i].author << "\n";
            cout << "Year: " << tempBooks[i].year << "\n";
            cout << "Price: " << tempBooks[i].price << "\n";
        }
    }
    void findBooksInPriceRange(double minPrice, double maxPrice) {
        for (int i = 0; i < count; i++) {
            if (books[i].price >= minPrice && books[i].price <= maxPrice) {
                cout << "Title: " << books[i].title << "\n";
                cout << "Author: " << books[i].author << "\n";
                cout << "Year: " << books[i].year << "\n";
                cout << "Price: " << books[i].price << "\n";
            }
        }
    }
};
void Menu() {
    cout << "\tMenu\n";
    cout << "1. Add a book\n";
    cout << "2. Remove a book\n";
    cout << "3. Find a book by title\n";
    cout << "4. List all books (sorted by title/author/year)\n";
    cout << "5. Find books in price range\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    BookStore bookStore;
    int choice;

    while (true) {
        Menu();
        cin >> choice;

        switch (choice) {
        case 1: {
            string title, author;
            int year;
            double price;
            cout << "Enter the title of the book: ";
            cin >> title;
            cout << "Enter the author of the book: ";
            cin >> author;
            cout << "Enter the year of publication: ";
            cin >> year;
            cout << "Enter the price of the book: ";
            cin >> price;
            bookStore.addBook(Book(title, author, year, price));
            cout << "Book successfully added\n";
            break;
        }
        case 2: {
            string title;
            cout << "Enter the title of the book to remove: ";
            cin >> title;
            bookStore.removeBook(title);
            break;
        }
        case 3: {
            string title;
            cout << "Enter the title of the book to find: ";
            cin >> title;
            Book* book = bookStore.findBook(title);
            if (book) {
                cout << "Title: " << book->title << "\n";
                cout << "Author: " << book->author << "\n";
                cout << "Year: " << book->year << "\n";
                cout << "Price: " << book->price << "\n";
            }
            else {
                cout << "Book not found!\n";
            }
            break;
        }
        case 4: {
            int sortChoice;
            cout << "1. Sort by title\n";
            cout << "2. Sort by author\n";
            cout << "3. Sort by year\n";
            cout << "Enter your choice: ";
            cin >> sortChoice;
            SortType sortType;
            if (sortChoice == 1) {
                sortType = SortType::Title;
            }
            else if (sortChoice == 2) {
                sortType = SortType::Author;
            }
            else if (sortChoice == 3) {
                sortType = SortType::Year;
            }
            bookStore.listBooks(sortType);
            break;
        }
        case 5: {
            double minPrice, maxPrice;
            cout << "Enter the min price: ";
            cin >> minPrice;
            cout << "Enter the max price: ";
            cin >> maxPrice;
            bookStore.findBooksInPriceRange(minPrice, maxPrice);
            break;
        }
        case 6: {
            return 0;
        }
        default: {
            cout << "Please try again.\n";
            break;
        }
        }
    }
    return 0;
}
