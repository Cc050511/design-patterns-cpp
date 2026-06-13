#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <cmath>

// === Visitor Demo ===
// Represents an operation to be performed on the elements of an object structure.
// Visitor lets you define a new operation without changing the classes of the elements on which it operates.

// Forward declarations
class Circle;
class Rectangle;
class Triangle;

// Visitor interface
class ShapeVisitor {
public:
    virtual ~ShapeVisitor() = default;
    virtual void visitCircle(Circle& circle) = 0;
    virtual void visitRectangle(Rectangle& rectangle) = 0;
    virtual void visitTriangle(Triangle& triangle) = 0;
};

// Element interface
class Shape {
public:
    virtual ~Shape() = default;
    virtual void accept(ShapeVisitor& visitor) = 0;
    virtual std::string getName() const = 0;
};

// Concrete Element 1: Circle
class Circle : public Shape {
public:
    explicit Circle(double radius) : radius_(radius) {}

    void accept(ShapeVisitor& visitor) override {
        visitor.visitCircle(*this);
    }

    std::string getName() const override { return "Circle"; }
    double getRadius() const { return radius_; }
    double getArea() const { return 3.14159 * radius_ * radius_; }

private:
    double radius_;
};

// Concrete Element 2: Rectangle
class Rectangle : public Shape {
public:
    Rectangle(double width, double height) : width_(width), height_(height) {}

    void accept(ShapeVisitor& visitor) override {
        visitor.visitRectangle(*this);
    }

    std::string getName() const override { return "Rectangle"; }
    double getWidth() const { return width_; }
    double getHeight() const { return height_; }
    double getArea() const { return width_ * height_; }

private:
    double width_, height_;
};

// Concrete Element 3: Triangle
class Triangle : public Shape {
public:
    Triangle(double base, double height) : base_(base), height_(height) {}

    void accept(ShapeVisitor& visitor) override {
        visitor.visitTriangle(*this);
    }

    std::string getName() const override { return "Triangle"; }
    double getBase() const { return base_; }
    double getHeight() const { return height_; }
    double getArea() const { return 0.5 * base_ * height_; }

private:
    double base_, height_;
};

// Concrete Visitor 1: Area Calculator
class AreaCalculator : public ShapeVisitor {
public:
    void visitCircle(Circle& circle) override {
        double area = circle.getArea();
        totalArea_ += area;
        std::cout << "Circle area: " << area << std::endl;
    }

    void visitRectangle(Rectangle& rectangle) override {
        double area = rectangle.getArea();
        totalArea_ += area;
        std::cout << "Rectangle area: " << area << std::endl;
    }

    void visitTriangle(Triangle& triangle) override {
        double area = triangle.getArea();
        totalArea_ += area;
        std::cout << "Triangle area: " << area << std::endl;
    }

    double getTotalArea() const { return totalArea_; }

private:
    double totalArea_ = 0.0;
};

// Concrete Visitor 2: XML Exporter
class XmlExporter : public ShapeVisitor {
public:
    void visitCircle(Circle& circle) override {
        std::cout << "  <circle radius=\"" << circle.getRadius() << "\" />" << std::endl;
    }

    void visitRectangle(Rectangle& rectangle) override {
        std::cout << "  <rectangle width=\"" << rectangle.getWidth()
                  << "\" height=\"" << rectangle.getHeight() << "\" />" << std::endl;
    }

    void visitTriangle(Triangle& triangle) override {
        std::cout << "  <triangle base=\"" << triangle.getBase()
                  << "\" height=\"" << triangle.getHeight() << "\" />" << std::endl;
    }
};

// Concrete Visitor 3: Perimeter Calculator (approximate)
class PerimeterCalculator : public ShapeVisitor {
public:
    void visitCircle(Circle& circle) override {
        double perimeter = 2 * 3.14159 * circle.getRadius();
        totalPerimeter_ += perimeter;
        std::cout << "Circle perimeter: " << perimeter << std::endl;
    }

    void visitRectangle(Rectangle& rectangle) override {
        double perimeter = 2 * (rectangle.getWidth() + rectangle.getHeight());
        totalPerimeter_ += perimeter;
        std::cout << "Rectangle perimeter: " << perimeter << std::endl;
    }

    void visitTriangle(Triangle& triangle) override {
        // Simplified: assuming right triangle for demo
        double hypotenuse = std::sqrt(triangle.getBase() * triangle.getBase() +
                                       triangle.getHeight() * triangle.getHeight());
        double perimeter = triangle.getBase() + triangle.getHeight() + hypotenuse;
        totalPerimeter_ += perimeter;
        std::cout << "Triangle perimeter: " << perimeter << std::endl;
    }

    double getTotalPerimeter() const { return totalPerimeter_; }

private:
    double totalPerimeter_ = 0.0;
};

// Object structure
class Drawing {
public:
    void addShape(std::shared_ptr<Shape> shape) {
        shapes_.push_back(shape);
    }

    void accept(ShapeVisitor& visitor) {
        for (auto& shape : shapes_) {
            shape->accept(visitor);
        }
    }

    size_t getShapeCount() const { return shapes_.size(); }

private:
    std::vector<std::shared_ptr<Shape>> shapes_;
};

int main() {
    std::cout << "=== Visitor Demo ===" << std::endl;

    // Create a drawing with various shapes
    Drawing drawing;
    drawing.addShape(std::make_shared<Circle>(5.0));
    drawing.addShape(std::make_shared<Rectangle>(10.0, 20.0));
    drawing.addShape(std::make_shared<Triangle>(8.0, 12.0));
    drawing.addShape(std::make_shared<Circle>(3.0));

    std::cout << "Drawing contains " << drawing.getShapeCount() << " shapes" << std::endl;
    std::cout << std::endl;

    // Apply different visitors
    std::cout << "--- Area Calculation ---" << std::endl;
    AreaCalculator areaCalc;
    drawing.accept(areaCalc);
    std::cout << "Total area: " << areaCalc.getTotalArea() << std::endl;
    std::cout << std::endl;

    std::cout << "--- Perimeter Calculation ---" << std::endl;
    PerimeterCalculator perimCalc;
    drawing.accept(perimCalc);
    std::cout << "Total perimeter: " << perimCalc.getTotalPerimeter() << std::endl;
    std::cout << std::endl;

    std::cout << "--- XML Export ---" << std::endl;
    std::cout << "<drawing>" << std::endl;
    XmlExporter xmlExporter;
    drawing.accept(xmlExporter);
    std::cout << "</drawing>" << std::endl;

    std::cout << std::endl;
    std::cout << "Visitor pattern adds operations without modifying element classes" << std::endl;
    std::cout << "=== End Visitor Demo ===" << std::endl;
    return 0;
}
