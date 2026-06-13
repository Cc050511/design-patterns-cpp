#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

// === Prototype Demo ===
// Creates new objects by copying existing ones (cloning).

// Prototype interface
class Shape {
public:
    virtual ~Shape() = default;
    virtual std::unique_ptr<Shape> clone() const = 0;
    virtual void draw() const = 0;
    virtual void setPosition(int x, int y) = 0;
    virtual std::string getInfo() const = 0;
};

// Concrete Prototype 1: Circle
class Circle : public Shape {
public:
    Circle() : x_(0), y_(0), radius_(10) {}
    Circle(int x, int y, double radius, const std::string& color)
        : x_(x), y_(y), radius_(radius), color_(color) {}

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this);
    }

    void draw() const override {
        std::cout << "Drawing Circle at (" << x_ << "," << y_ << ") with radius "
                  << radius_ << " and color " << color_ << std::endl;
    }

    void setPosition(int x, int y) override {
        x_ = x;
        y_ = y;
    }

    std::string getInfo() const override {
        return "Circle(r=" + std::to_string(static_cast<int>(radius_)) + ", c=" + color_ + ")";
    }

    void setRadius(double r) { radius_ = r; }

private:
    int x_, y_;
    double radius_;
    std::string color_;
};

// Concrete Prototype 2: Rectangle
class Rectangle : public Shape {
public:
    Rectangle() : x_(0), y_(0), width_(20), height_(10) {}
    Rectangle(int x, int y, double w, double h, const std::string& color)
        : x_(x), y_(y), width_(w), height_(h), color_(color) {}

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Rectangle>(*this);
    }

    void draw() const override {
        std::cout << "Drawing Rectangle at (" << x_ << "," << y_ << ") with size "
                  << width_ << "x" << height_ << " and color " << color_ << std::endl;
    }

    void setPosition(int x, int y) override {
        x_ = x;
        y_ = y;
    }

    std::string getInfo() const override {
        return "Rectangle(" + std::to_string(static_cast<int>(width_)) + "x" +
               std::to_string(static_cast<int>(height_)) + ", c=" + color_ + ")";
    }

private:
    int x_, y_;
    double width_, height_;
    std::string color_;
};

// Prototype registry
class ShapeRegistry {
public:
    void registerPrototype(const std::string& name, std::unique_ptr<Shape> prototype) {
        prototypes_[name] = std::move(prototype);
    }

    std::unique_ptr<Shape> create(const std::string& name) {
        auto it = prototypes_.find(name);
        if (it != prototypes_.end()) {
            return it->second->clone();
        }
        return nullptr;
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Shape>> prototypes_;
};

int main() {
    std::cout << "=== Prototype Demo ===" << std::endl;

    // Create original prototypes
    Circle originalCircle(0, 0, 50, "Red");
    Rectangle originalRectangle(0, 0, 100, 50, "Blue");

    std::cout << "Original objects:" << std::endl;
    originalCircle.draw();
    originalRectangle.draw();
    std::cout << std::endl;

    // Clone the prototypes
    auto circle1 = originalCircle.clone();
    auto circle2 = originalCircle.clone();
    auto rect1 = originalRectangle.clone();

    // Modify clones independently
    circle1->setPosition(10, 20);
    circle2->setPosition(30, 40);
    rect1->setPosition(50, 60);

    std::cout << "Cloned and modified objects:" << std::endl;
    circle1->draw();
    circle2->draw();
    rect1->draw();
    std::cout << std::endl;

    // Verify originals are unchanged
    std::cout << "Originals remain unchanged:" << std::endl;
    originalCircle.draw();
    originalRectangle.draw();
    std::cout << std::endl;

    // Using registry
    ShapeRegistry registry;
    registry.registerPrototype("circle", std::make_unique<Circle>(0, 0, 25, "Green"));
    registry.registerPrototype("rectangle", std::make_unique<Rectangle>(0, 0, 80, 40, "Yellow"));

    auto regCircle = registry.create("circle");
    auto regRect = registry.create("rectangle");
    regCircle->setPosition(100, 100);
    regRect->setPosition(200, 200);

    std::cout << "Objects from registry:" << std::endl;
    regCircle->draw();
    regRect->draw();

    std::cout << "Prototype pattern creates objects by cloning existing ones" << std::endl;
    std::cout << "=== End Prototype Demo ===" << std::endl;
    return 0;
}
