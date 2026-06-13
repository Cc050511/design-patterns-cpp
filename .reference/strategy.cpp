#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

// === Strategy Demo ===
// Defines a family of algorithms, encapsulates each one, and makes them interchangeable.
// Strategy lets the algorithm vary independently from clients that use it.

// Strategy interface
class SortStrategy {
public:
    virtual ~SortStrategy() = default;
    virtual void sort(std::vector<int>& data) const = 0;
    virtual std::string getName() const = 0;
};

// Context: DataProcessor
class DataProcessor {
public:
    explicit DataProcessor(std::unique_ptr<SortStrategy> strategy)
        : strategy_(std::move(strategy)) {}

    void setStrategy(std::unique_ptr<SortStrategy> strategy) {
        strategy_ = std::move(strategy);
    }

    void process(std::vector<int>& data) {
        std::cout << "Using strategy: " << strategy_->getName() << std::endl;
        strategy_->sort(data);
        std::cout << "Result: ";
        for (int val : data) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

private:
    std::unique_ptr<SortStrategy> strategy_;
};

// Concrete Strategy 1: Bubble Sort
class BubbleSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) const override {
        std::cout << "  Performing Bubble Sort..." << std::endl;
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data.size() - i - 1; ++j) {
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]);
                }
            }
        }
    }

    std::string getName() const override { return "Bubble Sort"; }
};

// Concrete Strategy 2: Quick Sort
class QuickSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) const override {
        std::cout << "  Performing Quick Sort..." << std::endl;
        quickSort(data, 0, static_cast<int>(data.size()) - 1);
    }

    std::string getName() const override { return "Quick Sort"; }

private:
    void quickSort(std::vector<int>& data, int low, int high) const {
        if (low < high) {
            int pi = partition(data, low, high);
            quickSort(data, low, pi - 1);
            quickSort(data, pi + 1, high);
        }
    }

    int partition(std::vector<int>& data, int low, int high) const {
        int pivot = data[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (data[j] < pivot) {
                i++;
                std::swap(data[i], data[j]);
            }
        }
        std::swap(data[i + 1], data[high]);
        return i + 1;
    }
};

// Concrete Strategy 3: Merge Sort
class MergeSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) const override {
        std::cout << "  Performing Merge Sort..." << std::endl;
        if (data.size() > 1) {
            mergeSort(data, 0, static_cast<int>(data.size()) - 1);
        }
    }

    std::string getName() const override { return "Merge Sort"; }

private:
    void mergeSort(std::vector<int>& data, int left, int right) const {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(data, left, mid);
            mergeSort(data, mid + 1, right);
            merge(data, left, mid, right);
        }
    }

    void merge(std::vector<int>& data, int left, int mid, int right) const {
        std::vector<int> temp;
        int i = left, j = mid + 1;
        while (i <= mid && j <= right) {
            if (data[i] <= data[j]) {
                temp.push_back(data[i++]);
            } else {
                temp.push_back(data[j++]);
            }
        }
        while (i <= mid) temp.push_back(data[i++]);
        while (j <= right) temp.push_back(data[j++]);
        for (int k = 0; k < static_cast<int>(temp.size()); ++k) {
            data[left + k] = temp[k];
        }
    }
};

// Another example: Payment strategies
class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    virtual bool pay(double amount) = 0;
    virtual std::string getMethod() const = 0;
};

class CreditCardPayment : public PaymentStrategy {
public:
    explicit CreditCardPayment(std::string cardNumber) : cardNumber_(std::move(cardNumber)) {}

    bool pay(double amount) override {
        std::cout << "Paying $" << amount << " using Credit Card ending in "
                  << cardNumber_.substr(cardNumber_.size() - 4) << std::endl;
        return true;
    }

    std::string getMethod() const override { return "Credit Card"; }

private:
    std::string cardNumber_;
};

class PayPalPayment : public PaymentStrategy {
public:
    explicit PayPalPayment(std::string email) : email_(std::move(email)) {}

    bool pay(double amount) override {
        std::cout << "Paying $" << amount << " using PayPal account " << email_ << std::endl;
        return true;
    }

    std::string getMethod() const override { return "PayPal"; }

private:
    std::string email_;
};

class CryptoPayment : public PaymentStrategy {
public:
    explicit CryptoPayment(std::string wallet) : wallet_(std::move(wallet)) {}

    bool pay(double amount) override {
        std::cout << "Paying $" << amount << " using Crypto wallet " << wallet_.substr(0, 6) << "..." << std::endl;
        return true;
    }

    std::string getMethod() const override { return "Cryptocurrency"; }

private:
    std::string wallet_;
};

class ShoppingCart {
public:
    void setPaymentStrategy(std::unique_ptr<PaymentStrategy> strategy) {
        strategy_ = std::move(strategy);
    }

    void checkout(double total) {
        if (strategy_) {
            std::cout << "Selected payment: " << strategy_->getMethod() << std::endl;
            strategy_->pay(total);
        } else {
            std::cout << "No payment method selected" << std::endl;
        }
    }

private:
    std::unique_ptr<PaymentStrategy> strategy_;
};

int main() {
    std::cout << "=== Strategy Demo ===" << std::endl;

    // Sorting strategies
    std::cout << "--- Sorting Strategies ---" << std::endl;
    std::vector<int> data = {64, 34, 25, 12, 22, 11, 90};

    DataProcessor processor(std::make_unique<BubbleSort>());
    auto data1 = data;
    processor.process(data1);
    std::cout << std::endl;

    processor.setStrategy(std::make_unique<QuickSort>());
    auto data2 = data;
    processor.process(data2);
    std::cout << std::endl;

    processor.setStrategy(std::make_unique<MergeSort>());
    auto data3 = data;
    processor.process(data3);
    std::cout << std::endl;

    // Payment strategies
    std::cout << "--- Payment Strategies ---" << std::endl;
    ShoppingCart cart;

    cart.setPaymentStrategy(std::make_unique<CreditCardPayment>("1234567890123456"));
    cart.checkout(100.50);
    std::cout << std::endl;

    cart.setPaymentStrategy(std::make_unique<PayPalPayment>("user@example.com"));
    cart.checkout(50.25);
    std::cout << std::endl;

    cart.setPaymentStrategy(std::make_unique<CryptoPayment>("0x1234567890abcdef"));
    cart.checkout(200.00);

    std::cout << std::endl;
    std::cout << "Strategy pattern makes algorithms interchangeable at runtime" << std::endl;
    std::cout << "=== End Strategy Demo ===" << std::endl;
    return 0;
}
