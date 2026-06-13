#include <iostream>
#include <memory>
#include <string>
#include <vector>

// === Composite Demo ===
// Composes objects into tree structures to represent part-whole hierarchies.
// Lets clients treat individual objects and compositions uniformly.

// Component interface
class Graphic {
public:
    virtual ~Graphic() = default;
    virtual void draw() const = 0;
    virtual void move(int x, int y) = 0;
    virtual std::string getName() const = 0;
};

// Leaf 1: Circle
class Dot : public Graphic {
public:
    Dot(const std::string& name, int x, int y) : name_(name), x_(x), y_(y) {}

    void draw() const override {
        std::cout << "  Drawing Dot '" << name_ << "' at (" << x_ << "," << y_ << ")" << std::endl;
    }

    void move(int x, int y) override {
        x_ += x;
        y_ += y;
        std::cout << "  Moved Dot '" << name_ << "' to (" << x_ << "," << y_ << ")" << std::endl;
    }

    std::string getName() const override { return name_; }

private:
    std::string name_;
    int x_, y_;
};

// Leaf 2: Circle
class CircleGraphic : public Graphic {
public:
    CircleGraphic(const std::string& name, int x, int y, int radius)
        : name_(name), x_(x), y_(y), radius_(radius) {}

    void draw() const override {
        std::cout << "  Drawing Circle '" << name_ << "' at (" << x_ << "," << y_ << ") radius " << radius_ << std::endl;
    }

    void move(int x, int y) override {
        x_ += x;
        y_ += y;
        std::cout << "  Moved Circle '" << name_ << "' to (" << x_ << "," << y_ << ")" << std::endl;
    }

    std::string getName() const override { return name_; }

private:
    std::string name_;
    int x_, y_, radius_;
};

// Composite: can contain other Graphics (both leaves and composites)
class CompoundGraphic : public Graphic {
public:
    explicit CompoundGraphic(const std::string& name) : name_(name) {}

    void add(std::shared_ptr<Graphic> graphic) {
        children_.push_back(graphic);
    }

    void remove(const std::string& name) {
        children_.erase(
            std::remove_if(children_.begin(), children_.end(),
                [&name](const auto& child) { return child->getName() == name; }),
            children_.end()
        );
    }

    void draw() const override {
        std::cout << "Drawing Compound Graphic '" << name_ << "' with " << children_.size() << " children:" << std::endl;
        for (const auto& child : children_) {
            child->draw();
        }
    }

    void move(int x, int y) override {
        std::cout << "Moving Compound Graphic '" << name_ << "' by (" << x << "," << y << "):" << std::endl;
        for (auto& child : children_) {
            child->move(x, y);
        }
    }

    std::string getName() const override { return name_; }

private:
    std::string name_;
    std::vector<std::shared_ptr<Graphic>> children_;
};

int main() {
    std::cout << "=== Composite Demo ===" << std::endl;

    // Create individual leaf objects
    auto dot1 = std::make_shared<Dot>("Dot1", 10, 10);
    auto dot2 = std::make_shared<Dot>("Dot2", 20, 20);
    auto circle1 = std::make_shared<CircleGraphic>("Circle1", 50, 50, 25);

    // Create a composite (group) of simple shapes
    auto group1 = std::make_shared<CompoundGraphic>("Group1");
    group1->add(dot1);
    group1->add(dot2);

    // Create another composite containing a leaf and another composite
    auto mainGroup = std::make_shared<CompoundGraphic>("MainGroup");
    mainGroup->add(circle1);
    mainGroup->add(group1);

    // Draw everything - same interface for leaves and composites
    std::cout << "--- Initial Draw ---" << std::endl;
    mainGroup->draw();
    std::cout << std::endl;

    // Move everything - same interface for leaves and composites
    std::cout << "--- Move All ---" << std::endl;
    mainGroup->move(5, 5);
    std::cout << std::endl;

    // Draw again to see new positions
    std::cout << "--- After Move ---" << std::endl;
    mainGroup->draw();
    std::cout << std::endl;

    // Can also work with individual elements
    std::cout << "--- Individual Element ---" << std::endl;
    dot1->draw();
    dot1->move(100, 100);
    dot1->draw();

    std::cout << std::endl;
    std::cout << "Composite pattern treats individual objects and compositions uniformly" << std::endl;
    std::cout << "=== End Composite Demo ===" << std::endl;
    return 0;
}
