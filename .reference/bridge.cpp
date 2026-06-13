#include <iostream>
#include <memory>
#include <string>

// === Bridge Demo ===
// Decouples an abstraction from its implementation so that the two can vary independently.

// Implementation interface (the "bridge")
class DrawingAPI {
public:
    virtual ~DrawingAPI() = default;
    virtual void drawCircle(double x, double y, double radius) const = 0;
    virtual void drawRectangle(double x, double y, double w, double h) const = 0;
    virtual std::string getAPIName() const = 0;
};

// Concrete Implementation 1: OpenGL
class OpenGLAPI : public DrawingAPI {
public:
    void drawCircle(double x, double y, double radius) const override {
        std::cout << "OpenGL: Drawing circle at (" << x << "," << y << ") radius " << radius << std::endl;
    }
    void drawRectangle(double x, double y, double w, double h) const override {
        std::cout << "OpenGL: Drawing rectangle at (" << x << "," << y << ") size " << w << "x" << h << std::endl;
    }
    std::string getAPIName() const override { return "OpenGL"; }
};

// Concrete Implementation 2: DirectX
class DirectXAPI : public DrawingAPI {
public:
    void drawCircle(double x, double y, double radius) const override {
        std::cout << "DirectX: Drawing circle at (" << x << "," << y << ") radius " << radius << std::endl;
    }
    void drawRectangle(double x, double y, double w, double h) const override {
        std::cout << "DirectX: Drawing rectangle at (" << x << "," << y << ") size " << w << "x" << h << std::endl;
    }
    std::string getAPIName() const override { return "DirectX"; }
};

// Concrete Implementation 3: Vulkan
class VulkanAPI : public DrawingAPI {
public:
    void drawCircle(double x, double y, double radius) const override {
        std::cout << "Vulkan: Drawing circle at (" << x << "," << y << ") radius " << radius << std::endl;
    }
    void drawRectangle(double x, double y, double w, double h) const override {
        std::cout << "Vulkan: Drawing rectangle at (" << x << "," << y << ") size " << w << "x" << h << std::endl;
    }
    std::string getAPIName() const override { return "Vulkan"; }
};

// Abstraction
class Shape {
public:
    Shape(const std::string& name, std::shared_ptr<DrawingAPI> api)
        : name_(name), drawingAPI_(api) {}
    virtual ~Shape() = default;

    virtual void draw() const = 0;
    virtual void resize(double factor) = 0;

    void setDrawingAPI(std::shared_ptr<DrawingAPI> api) {
        drawingAPI_ = api;
    }

    std::string getName() const { return name_; }
    std::string getCurrentAPI() const { return drawingAPI_->getAPIName(); }

protected:
    std::string name_;
    std::shared_ptr<DrawingAPI> drawingAPI_;
};

// Refined Abstraction 1: CircleShape
class CircleShape : public Shape {
public:
    CircleShape(double x, double y, double radius, std::shared_ptr<DrawingAPI> api)
        : Shape("Circle", api), x_(x), y_(y), radius_(radius) {}

    void draw() const override {
        std::cout << name_ << " using " << getCurrentAPI() << ": ";
        drawingAPI_->drawCircle(x_, y_, radius_);
    }

    void resize(double factor) override {
        radius_ *= factor;
        std::cout << name_ << " resized to radius " << radius_ << std::endl;
    }

private:
    double x_, y_, radius_;
};

// Refined Abstraction 2: RectangleShape
class RectangleShape : public Shape {
public:
    RectangleShape(double x, double y, double w, double h, std::shared_ptr<DrawingAPI> api)
        : Shape("Rectangle", api), x_(x), y_(y), width_(w), height_(h) {}

    void draw() const override {
        std::cout << name_ << " using " << getCurrentAPI() << ": ";
        drawingAPI_->drawRectangle(x_, y_, width_, height_);
    }

    void resize(double factor) override {
        width_ *= factor;
        height_ *= factor;
        std::cout << name_ << " resized to " << width_ << "x" << height_ << std::endl;
    }

private:
    double x_, y_, width_, height_;
};

int main() {
    std::cout << "=== Bridge Demo ===" << std::endl;

    // Create different rendering APIs
    auto opengl = std::make_shared<OpenGLAPI>();
    auto directx = std::make_shared<DirectXAPI>();
    auto vulkan = std::make_shared<VulkanAPI>();

    // Create shapes with different APIs
    CircleShape circle1(10, 20, 30, opengl);
    CircleShape circle2(50, 60, 40, directx);
    RectangleShape rect1(0, 0, 100, 50, vulkan);

    std::cout << "--- Drawing shapes with initial APIs ---" << std::endl;
    circle1.draw();
    circle2.draw();
    rect1.draw();
    std::cout << std::endl;

    // Change API at runtime (the bridge allows this!)
    std::cout << "--- Switching circle1 to Vulkan ---" << std::endl;
    circle1.setDrawingAPI(vulkan);
    circle1.draw();
    std::cout << std::endl;

    // Resize and redraw
    std::cout << "--- Resizing shapes ---" << std::endl;
    circle1.resize(2.0);
    rect1.resize(0.5);
    circle1.draw();
    rect1.draw();

    std::cout << std::endl;
    std::cout << "Bridge pattern decouples abstraction from implementation" << std::endl;
    std::cout << "=== End Bridge Demo ===" << std::endl;
    return 0;
}
