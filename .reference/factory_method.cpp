#include <iostream>
#include <memory>
#include <string>

// === Factory Method Demo ===
// Defines an interface for creating an object, but lets subclasses decide which class to instantiate.

// Product interface
class Document {
public:
    virtual ~Document() = default;
    virtual void open() const = 0;
    virtual void save() const = 0;
    virtual std::string getType() const = 0;
};

// Concrete Products
class PdfDocument : public Document {
public:
    void open() const override {
        std::cout << "Opening PDF document" << std::endl;
    }
    void save() const override {
        std::cout << "Saving PDF document" << std::endl;
    }
    std::string getType() const override { return "PDF"; }
};

class WordDocument : public Document {
public:
    void open() const override {
        std::cout << "Opening Word document" << std::endl;
    }
    void save() const override {
        std::cout << "Saving Word document" << std::endl;
    }
    std::string getType() const override { return "Word"; }
};

class TextDocument : public Document {
public:
    void open() const override {
        std::cout << "Opening Text document" << std::endl;
    }
    void save() const override {
        std::cout << "Saving Text document" << std::endl;
    }
    std::string getType() const override { return "Text"; }
};

// Creator (Factory) with factory method
class DocumentCreator {
public:
    virtual ~DocumentCreator() = default;

    // Factory Method - subclasses override this
    virtual std::unique_ptr<Document> createDocument() const = 0;

    // Business logic that uses the product
    void newDocument() const {
        auto doc = createDocument();
        std::cout << "Creating new " << doc->getType() << " document" << std::endl;
        doc->open();
    }
};

// Concrete Creators
class PdfCreator : public DocumentCreator {
public:
    std::unique_ptr<Document> createDocument() const override {
        return std::make_unique<PdfDocument>();
    }
};

class WordCreator : public DocumentCreator {
public:
    std::unique_ptr<Document> createDocument() const override {
        return std::make_unique<WordDocument>();
    }
};

class TextCreator : public DocumentCreator {
public:
    std::unique_ptr<Document> createDocument() const override {
        return std::make_unique<TextDocument>();
    }
};

int main() {
    std::cout << "=== Factory Method Demo ===" << std::endl;

    // Create different document types through their factories
    std::unique_ptr<DocumentCreator> creators[] = {
        std::make_unique<PdfCreator>(),
        std::make_unique<WordCreator>(),
        std::make_unique<TextCreator>()
    };

    for (const auto& creator : creators) {
        creator->newDocument();
        std::cout << "---" << std::endl;
    }

    // Direct factory method usage
    PdfCreator pdfFactory;
    auto pdf = pdfFactory.createDocument();
    pdf->save();
    std::cout << "Document type: " << pdf->getType() << std::endl;

    std::cout << "Factory Method decouples object creation from usage" << std::endl;
    std::cout << "=== End Factory Method Demo ===" << std::endl;
    return 0;
}
