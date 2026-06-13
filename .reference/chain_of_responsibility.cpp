#include <iostream>
#include <memory>
#include <string>
#include <vector>

// === Chain of Responsibility Demo ===
// Avoids coupling the sender of a request to its receiver by giving more than one object a chance to handle the request.

// Handler interface
class SupportHandler {
public:
    virtual ~SupportHandler() = default;

    void setNext(std::shared_ptr<SupportHandler> next) {
        next_ = next;
    }

    void handle(const std::string& request) {
        if (canHandle(request)) {
            process(request);
        } else if (next_) {
            std::cout << "Passing to next handler..." << std::endl;
            next_->handle(request);
        } else {
            std::cout << "No handler available for: " << request << std::endl;
        }
    }

protected:
    virtual bool canHandle(const std::string& request) const = 0;
    virtual void process(const std::string& request) const = 0;

    std::shared_ptr<SupportHandler> next_;
};

// Concrete Handler 1: Basic Support
class BasicSupport : public SupportHandler {
protected:
    bool canHandle(const std::string& request) const override {
        return request.find("password") != std::string::npos ||
               request.find("login") != std::string::npos;
    }

    void process(const std::string& request) const override {
        std::cout << "[Basic Support] Handling request: " << request << std::endl;
        std::cout << "  -> Reset password or verify login credentials" << std::endl;
    }
};

// Concrete Handler 2: Technical Support
class TechnicalSupport : public SupportHandler {
protected:
    bool canHandle(const std::string& request) const override {
        return request.find("bug") != std::string::npos ||
               request.find("crash") != std::string::npos ||
               request.find("error") != std::string::npos;
    }

    void process(const std::string& request) const override {
        std::cout << "[Technical Support] Handling request: " << request << std::endl;
        std::cout << "  -> Investigating technical issue and collecting logs" << std::endl;
    }
};

// Concrete Handler 3: Billing Support
class BillingSupport : public SupportHandler {
protected:
    bool canHandle(const std::string& request) const override {
        return request.find("billing") != std::string::npos ||
               request.find("payment") != std::string::npos ||
               request.find("refund") != std::string::npos;
    }

    void process(const std::string& request) const override {
        std::cout << "[Billing Support] Handling request: " << request << std::endl;
        std::cout << "  -> Processing billing inquiry or refund request" << std::endl;
    }
};

// Concrete Handler 4: Manager (escalation)
class ManagerSupport : public SupportHandler {
protected:
    bool canHandle(const std::string& request) const override {
        return request.find("escalate") != std::string::npos ||
               request.find("complaint") != std::string::npos;
    }

    void process(const std::string& request) const override {
        std::cout << "[Manager] Handling escalated request: " << request << std::endl;
        std::cout << "  -> Reviewing case and providing resolution" << std::endl;
    }
};

int main() {
    std::cout << "=== Chain of Responsibility Demo ===" << std::endl;

    // Build the chain
    auto basic = std::make_shared<BasicSupport>();
    auto technical = std::make_shared<TechnicalSupport>();
    auto billing = std::make_shared<BillingSupport>();
    auto manager = std::make_shared<ManagerSupport>();

    basic->setNext(technical);
    technical->setNext(billing);
    billing->setNext(manager);

    // Test various requests
    std::vector<std::string> requests = {
        "I forgot my password",
        "The app crashes on startup",
        "I need a refund for my payment",
        "I want to escalate my complaint",
        "I need help with something random"
    };

    for (const auto& request : requests) {
        std::cout << std::endl << "Request: \"" << request << "\"" << std::endl;
        basic->handle(request);
    }

    std::cout << std::endl;
    std::cout << "Chain of Responsibility passes requests along a chain of handlers" << std::endl;
    std::cout << "=== End Chain of Responsibility Demo ===" << std::endl;
    return 0;
}
