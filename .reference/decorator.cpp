#include <iostream>
#include <memory>
#include <string>

// === Decorator Demo ===
// Attaches additional responsibilities to an object dynamically.
// Provides a flexible alternative to subclassing for extending functionality.

// Component interface
class Coffee {
public:
    virtual ~Coffee() = default;
    virtual double cost() const = 0;
    virtual std::string description() const = 0;
};

// Concrete Component: SimpleCoffee
class SimpleCoffee : public Coffee {
public:
    double cost() const override { return 2.0; }
    std::string description() const override { return "Simple coffee"; }
};

// Base Decorator
class CoffeeDecorator : public Coffee {
public:
    explicit CoffeeDecorator(std::unique_ptr<Coffee> coffee) : coffee_(std::move(coffee)) {}

    double cost() const override {
        return coffee_->cost();
    }

    std::string description() const override {
        return coffee_->description();
    }

protected:
    std::unique_ptr<Coffee> coffee_;
};

// Concrete Decorator 1: Milk
class Milk : public CoffeeDecorator {
public:
    explicit Milk(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {}

    double cost() const override {
        return coffee_->cost() + 0.5;
    }

    std::string description() const override {
        return coffee_->description() + ", milk";
    }
};

// Concrete Decorator 2: Sugar
class Sugar : public CoffeeDecorator {
public:
    explicit Sugar(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {}

    double cost() const override {
        return coffee_->cost() + 0.2;
    }

    std::string description() const override {
        return coffee_->description() + ", sugar";
    }
};

// Concrete Decorator 3: Whip
class Whip : public CoffeeDecorator {
public:
    explicit Whip(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {}

    double cost() const override {
        return coffee_->cost() + 0.7;
    }

    std::string description() const override {
        return coffee_->description() + ", whip";
    }
};

// Concrete Decorator 4: Vanilla
class Vanilla : public CoffeeDecorator {
public:
    explicit Vanilla(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {}

    double cost() const override {
        return coffee_->cost() + 0.8;
    }

    std::string description() const override {
        return coffee_->description() + ", vanilla";
    }
};

// Another example: Text formatting
class Text {
public:
    virtual ~Text() = default;
    virtual std::string render() const = 0;
};

class PlainText : public Text {
public:
    explicit PlainText(std::string text) : text_(std::move(text)) {}
    std::string render() const override { return text_; }
private:
    std::string text_;
};

class TextDecorator : public Text {
public:
    explicit TextDecorator(std::unique_ptr<Text> text) : text_(std::move(text)) {}
    std::string render() const override { return text_->render(); }
protected:
    std::unique_ptr<Text> text_;
};

class Bold : public TextDecorator {
public:
    explicit Bold(std::unique_ptr<Text> text) : TextDecorator(std::move(text)) {}
    std::string render() const override { return "<b>" + text_->render() + "</b>"; }
};

class Italic : public TextDecorator {
public:
    explicit Italic(std::unique_ptr<Text> text) : TextDecorator(std::move(text)) {}
    std::string render() const override { return "<i>" + text_->render() + "</i>"; }
};

class Underline : public TextDecorator {
public:
    explicit Underline(std::unique_ptr<Text> text) : TextDecorator(std::move(text)) {}
    std::string render() const override { return "<u>" + text_->render() + "</u>"; }
};

int main() {
    std::cout << "=== Decorator Demo ===" << std::endl;

    // Coffee example
    std::cout << "--- Coffee Orders ---" << std::endl;

    auto simple = std::make_unique<SimpleCoffee>();
    std::cout << simple->description() << " -> $" << simple->cost() << std::endl;

    auto withMilk = std::make_unique<Milk>(std::make_unique<SimpleCoffee>());
    std::cout << withMilk->description() << " -> $" << withMilk->cost() << std::endl;

    auto withMilkAndSugar = std::make_unique<Sugar>(std::make_unique<Milk>(std::make_unique<SimpleCoffee>()));
    std::cout << withMilkAndSugar->description() << " -> $" << withMilkAndSugar->cost() << std::endl;

    auto fancy = std::make_unique<Vanilla>(std::make_unique<Whip>(std::make_unique<Sugar>(std::make_unique<Milk>(std::make_unique<SimpleCoffee>()))));
    std::cout << fancy->description() << " -> $" << fancy->cost() << std::endl;
    std::cout << std::endl;

    // Text formatting example
    std::cout << "--- Text Formatting ---" << std::endl;
    auto text = std::make_unique<PlainText>("Hello, World!");
    std::cout << "Plain: " << text->render() << std::endl;

    auto boldText = std::make_unique<Bold>(std::make_unique<PlainText>("Hello, World!"));
    std::cout << "Bold: " << boldText->render() << std::endl;

    auto boldItalic = std::make_unique<Italic>(std::make_unique<Bold>(std::make_unique<PlainText>("Hello, World!")));
    std::cout << "Bold+Italic: " << boldItalic->render() << std::endl;

    auto allStyles = std::make_unique<Underline>(std::make_unique<Italic>(std::make_unique<Bold>(std::make_unique<PlainText>("Hello, World!"))));
    std::cout << "All styles: " << allStyles->render() << std::endl;

    std::cout << std::endl;
    std::cout << "Decorator pattern adds responsibilities dynamically without subclassing" << std::endl;
    std::cout << "=== End Decorator Demo ===" << std::endl;
    return 0;
}
