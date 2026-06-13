#include <iostream>
#include <memory>
#include <string>
#include <vector>

// === Iterator Demo ===
// Provides a way to access the elements of an aggregate object sequentially without exposing its underlying representation.

// Iterator interface
template<typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() const = 0;
    virtual T next() = 0;
    virtual void reset() = 0;
};

// Aggregate interface
template<typename T>
class IterableCollection {
public:
    virtual ~IterableCollection() = default;
    virtual std::unique_ptr<Iterator<T>> createIterator() = 0;
};

// Concrete Collection: BookCollection
class Book {
public:
    Book(std::string title, std::string author)
        : title_(std::move(title)), author_(std::move(author)) {}

    std::string getTitle() const { return title_; }
    std::string getAuthor() const { return author_; }

private:
    std::string title_;
    std::string author_;
};

class BookCollection : public IterableCollection<Book> {
public:
    void addBook(const Book& book) {
        books_.push_back(book);
    }

    size_t size() const { return books_.size(); }
    Book getBook(size_t index) const { return books_[index]; }

    std::unique_ptr<Iterator<Book>> createIterator() override;

private:
    std::vector<Book> books_;
};

// Concrete Iterator: Forward iterator
class BookIterator : public Iterator<Book> {
public:
    explicit BookIterator(const BookCollection& collection)
        : collection_(collection), index_(0) {}

    bool hasNext() const override {
        return index_ < collection_.size();
    }

    Book next() override {
        return collection_.getBook(index_++);
    }

    void reset() override {
        index_ = 0;
    }

private:
    const BookCollection& collection_;
    size_t index_;
};

std::unique_ptr<Iterator<Book>> BookCollection::createIterator() {
    return std::make_unique<BookIterator>(*this);
}

// Another iterator: Reverse iterator
class ReverseBookIterator : public Iterator<Book> {
public:
    explicit ReverseBookIterator(const BookCollection& collection)
        : collection_(collection), index_(collection.size()) {}

    bool hasNext() const override {
        return index_ > 0;
    }

    Book next() override {
        return collection_.getBook(--index_);
    }

    void reset() override {
        index_ = collection_.size();
    }

private:
    const BookCollection& collection_;
    size_t index_;
};

// Custom collection with different internal structure
class NameList {
public:
    void add(const std::string& name) {
        names_ += name + ",";
        count_++;
    }

    size_t size() const { return count_; }
    std::string getRaw() const { return names_; }

    class NameIterator : public Iterator<std::string> {
    public:
        explicit NameIterator(const NameList& list)
            : list_(list), pos_(0), current_(0) {}

        bool hasNext() const override {
            return pos_ < list_.names_.size() && list_.names_.find(',', pos_) != std::string::npos;
        }

        std::string next() override {
            size_t comma = list_.names_.find(',', pos_);
            std::string name = list_.names_.substr(pos_, comma - pos_);
            pos_ = comma + 1;
            current_++;
            return name;
        }

        void reset() override {
            pos_ = 0;
            current_ = 0;
        }

    private:
        const NameList& list_;
        size_t pos_;
        size_t current_;
    };

    std::unique_ptr<Iterator<std::string>> createIterator() {
        return std::make_unique<NameIterator>(*this);
    }

private:
    std::string names_;
    size_t count_ = 0;
};

int main() {
    std::cout << "=== Iterator Demo ===" << std::endl;

    // Book collection with forward iterator
    std::cout << "--- Forward Iteration ---" << std::endl;
    BookCollection library;
    library.addBook(Book("Design Patterns", "GoF"));
    library.addBook(Book("Clean Code", "Robert Martin"));
    library.addBook(Book("Effective C++", "Scott Meyers"));
    library.addBook(Book("The Pragmatic Programmer", "Hunt & Thomas"));

    auto it = library.createIterator();
    while (it->hasNext()) {
        Book book = it->next();
        std::cout << "Book: \"" << book.getTitle() << "\" by " << book.getAuthor() << std::endl;
    }
    std::cout << std::endl;

    // Reverse iteration
    std::cout << "--- Reverse Iteration ---" << std::endl;
    ReverseBookIterator revIt(library);
    while (revIt.hasNext()) {
        Book book = revIt.next();
        std::cout << "Book: \"" << book.getTitle() << "\" by " << book.getAuthor() << std::endl;
    }
    std::cout << std::endl;

    // Custom collection with comma-separated storage
    std::cout << "--- Custom Collection ---" << std::endl;
    NameList names;
    names.add("Alice");
    names.add("Bob");
    names.add("Charlie");

    std::cout << "Raw storage: " << names.getRaw() << std::endl;
    auto nameIt = names.createIterator();
    while (nameIt->hasNext()) {
        std::cout << "Name: " << nameIt->next() << std::endl;
    }
    std::cout << std::endl;

    // Reset and iterate again
    std::cout << "--- After Reset ---" << std::endl;
    nameIt->reset();
    while (nameIt->hasNext()) {
        std::cout << "Name: " << nameIt->next() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Iterator pattern provides sequential access without exposing internals" << std::endl;
    std::cout << "=== End Iterator Demo ===" << std::endl;
    return 0;
}
