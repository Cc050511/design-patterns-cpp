/**
 * Chain Of Responsibility — 请求沿链传递
 * 意图: 请求沿链传递
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/chain_of_responsibility.cpp
 */

#include <memory>
#include <string>
#include <iostream>

// TODO: 完成以下类实现

class Handler {
public:
    virtual ~Handler() = default;
    void setNext(std::shared_ptr<Handler> next) {
        next_ = next;
    }
    virtual void handle(const std::string& request) const {
        // TODO: Handle request or pass to next
        if (next_) {
            next_->handle(request);
        }
    }
protected:
    std::shared_ptr<Handler> next_;
};

class ConcreteHandler : public Handler {
public:
    void handle(const std::string& request) const override {
        // TODO: Check if can handle, otherwise pass to next
        if (canHandle(request)) {
            // Process request
        } else {
            Handler::handle(request);
        }
    }
private:
    bool canHandle(const std::string& request) const {
        // TODO: Check condition
        return false;
    }
};

