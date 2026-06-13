#include <iostream>
#include <memory>
#include <string>

// === Proxy Demo ===
// Provides a surrogate or placeholder for another object to control access to it.

// Subject interface
class Image {
public:
    virtual ~Image() = default;
    virtual void display() const = 0;
    virtual std::string getFilename() const = 0;
};

// RealSubject: Heavy image object
class RealImage : public Image {
public:
    explicit RealImage(const std::string& filename) : filename_(filename) {
        loadFromDisk();
    }

    void display() const override {
        std::cout << "Displaying image: " << filename_ << std::endl;
    }

    std::string getFilename() const override { return filename_; }

private:
    void loadFromDisk() const {
        std::cout << "Loading heavy image from disk: " << filename_ << std::endl;
    }

    std::string filename_;
};

// Proxy: Virtual Proxy - delays loading until needed
class ProxyImage : public Image {
public:
    explicit ProxyImage(const std::string& filename) : filename_(filename) {}

    void display() const override {
        if (!realImage_) {
            realImage_ = std::make_unique<RealImage>(filename_);
        }
        realImage_->display();
    }

    std::string getFilename() const override { return filename_; }

private:
    mutable std::unique_ptr<RealImage> realImage_;
    std::string filename_;
};

// Another example: Protection Proxy
class Document {
public:
    virtual ~Document() = default;
    virtual void read() const = 0;
    virtual void write(const std::string& content) = 0;
};

class RealDocument : public Document {
public:
    explicit RealDocument(const std::string& content) : content_(content) {}

    void read() const override {
        std::cout << "Document content: " << content_ << std::endl;
    }

    void write(const std::string& content) override {
        content_ = content;
        std::cout << "Document updated" << std::endl;
    }

private:
    std::string content_;
};

class ProtectedDocument : public Document {
public:
    ProtectedDocument(const std::string& content, const std::string& userRole)
        : realDoc_(std::make_unique<RealDocument>(content)), userRole_(userRole) {}

    void read() const override {
        realDoc_->read();
    }

    void write(const std::string& content) override {
        if (userRole_ == "admin") {
            realDoc_->write(content);
        } else {
            std::cout << "Access denied: " << userRole_ << " cannot write to document" << std::endl;
        }
    }

private:
    std::unique_ptr<RealDocument> realDoc_;
    std::string userRole_;
};

// Another example: Smart Reference (logging proxy)
class BankAccount {
public:
    virtual ~BankAccount() = default;
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual double getBalance() const = 0;
};

class RealBankAccount : public BankAccount {
public:
    explicit RealBankAccount(double initial) : balance_(initial) {}

    void deposit(double amount) override {
        balance_ += amount;
    }

    void withdraw(double amount) override {
        if (amount <= balance_) {
            balance_ -= amount;
        }
    }

    double getBalance() const override { return balance_; }

private:
    double balance_;
};

class LoggingBankAccount : public BankAccount {
public:
    explicit LoggingBankAccount(double initial) : account_(std::make_unique<RealBankAccount>(initial)) {}

    void deposit(double amount) override {
        std::cout << "[LOG] Depositing $" << amount << std::endl;
        account_->deposit(amount);
        std::cout << "[LOG] New balance: $" << account_->getBalance() << std::endl;
    }

    void withdraw(double amount) override {
        std::cout << "[LOG] Withdrawing $" << amount << std::endl;
        account_->withdraw(amount);
        std::cout << "[LOG] New balance: $" << account_->getBalance() << std::endl;
    }

    double getBalance() const override { return account_->getBalance(); }

private:
    std::unique_ptr<RealBankAccount> account_;
};

int main() {
    std::cout << "=== Proxy Demo ===" << std::endl;

    // Virtual Proxy example
    std::cout << "--- Virtual Proxy (Lazy Loading) ---" << std::endl;
    std::cout << "Creating proxy images (no loading yet):" << std::endl;
    ProxyImage image1("photo1.jpg");
    ProxyImage image2("photo2.jpg");
    ProxyImage image3("photo3.jpg");
    std::cout << std::endl;

    std::cout << "Displaying images (loaded on demand):" << std::endl;
    image1.display();
    image2.display();
    image1.display(); // Already loaded, no reload
    std::cout << std::endl;

    // Protection Proxy example
    std::cout << "--- Protection Proxy ---" << std::endl;
    ProtectedDocument adminDoc("Secret Data", "admin");
    ProtectedDocument userDoc("Secret Data", "user");

    std::cout << "Admin access:" << std::endl;
    adminDoc.read();
    adminDoc.write("Updated Secret Data");
    adminDoc.read();
    std::cout << std::endl;

    std::cout << "User access:" << std::endl;
    userDoc.read();
    userDoc.write("Hacked Data");
    std::cout << std::endl;

    // Logging Proxy example
    std::cout << "--- Logging Proxy ---" << std::endl;
    LoggingBankAccount account(1000.0);
    account.deposit(500.0);
    account.withdraw(200.0);
    std::cout << "Final balance: $" << account.getBalance() << std::endl;

    std::cout << std::endl;
    std::cout << "Proxy pattern controls access to an object through a surrogate" << std::endl;
    std::cout << "=== End Proxy Demo ===" << std::endl;
    return 0;
}
