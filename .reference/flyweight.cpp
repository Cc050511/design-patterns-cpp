#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// === Flyweight Demo ===
// Uses sharing to support large numbers of fine-grained objects efficiently.

// Intrinsic state (shared)
class TreeType {
public:
    TreeType(const std::string& name, const std::string& color, const std::string& texture)
        : name_(name), color_(color), texture_(texture) {}

    void draw(int x, int y, int height) const {
        std::cout << "Drawing " << name_ << " tree (" << color_ << ", " << texture_
                  << ") at (" << x << "," << y << ") height=" << height << std::endl;
    }

    std::string getName() const { return name_; }

private:
    std::string name_;    // Intrinsic
    std::string color_;   // Intrinsic
    std::string texture_; // Intrinsic
};

// Flyweight Factory
class TreeFactory {
public:
    std::shared_ptr<TreeType> getTreeType(const std::string& name,
                                          const std::string& color,
                                          const std::string& texture) {
        std::string key = name + "_" + color + "_" + texture;
        auto it = treeTypes_.find(key);
        if (it != treeTypes_.end()) {
            return it->second;
        }
        auto type = std::make_shared<TreeType>(name, color, texture);
        treeTypes_[key] = type;
        return type;
    }

    size_t getTypeCount() const { return treeTypes_.size(); }

private:
    std::unordered_map<std::string, std::shared_ptr<TreeType>> treeTypes_;
};

// Extrinsic state (not shared)
class Tree {
public:
    Tree(int x, int y, int height, std::shared_ptr<TreeType> type)
        : x_(x), y_(y), height_(height), type_(type) {}

    void draw() const {
        type_->draw(x_, y_, height_);
    }

private:
    int x_, y_;                    // Extrinsic
    int height_;                   // Extrinsic
    std::shared_ptr<TreeType> type_; // Shared intrinsic state
};

// Forest manages many trees
class Forest {
public:
    void plantTree(int x, int y, const std::string& name,
                   const std::string& color, const std::string& texture,
                   int height) {
        auto type = factory_.getTreeType(name, color, texture);
        trees_.emplace_back(x, y, height, type);
    }

    void draw() const {
        std::cout << "Drawing forest with " << trees_.size() << " trees ("
                  << factory_.getTypeCount() << " unique types):" << std::endl;
        for (const auto& tree : trees_) {
            tree.draw();
        }
    }

    size_t getTreeCount() const { return trees_.size(); }
    size_t getTypeCount() const { return factory_.getTypeCount(); }

private:
    TreeFactory factory_;
    std::vector<Tree> trees_;
};

// Another example: Character flyweight
class CharacterStyle {
public:
    CharacterStyle(const std::string& font, int size, const std::string& color)
        : font_(font), size_(size), color_(color) {}

    void render(char c, int x, int y) const {
        std::cout << "Render '" << c << "' at (" << x << "," << y << ") using "
                  << font_ << " " << size_ << "pt " << color_ << std::endl;
    }

private:
    std::string font_;
    int size_;
    std::string color_;
};

class CharacterStyleFactory {
public:
    std::shared_ptr<CharacterStyle> getStyle(const std::string& font, int size, const std::string& color) {
        std::string key = font + "_" + std::to_string(size) + "_" + color;
        auto it = styles_.find(key);
        if (it != styles_.end()) {
            return it->second;
        }
        auto style = std::make_shared<CharacterStyle>(font, size, color);
        styles_[key] = style;
        return style;
    }

    size_t getStyleCount() const { return styles_.size(); }

private:
    std::unordered_map<std::string, std::shared_ptr<CharacterStyle>> styles_;
};

int main() {
    std::cout << "=== Flyweight Demo ===" << std::endl;

    // Forest example
    Forest forest;

    // Plant many trees but only a few unique types
    forest.plantTree(10, 20, "Oak", "Green", "Rough", 50);
    forest.plantTree(30, 40, "Oak", "Green", "Rough", 45);
    forest.plantTree(50, 60, "Oak", "Green", "Rough", 55);
    forest.plantTree(70, 80, "Pine", "Dark Green", "Smooth", 70);
    forest.plantTree(90, 100, "Pine", "Dark Green", "Smooth", 65);
    forest.plantTree(110, 120, "Birch", "White", "Smooth", 40);
    forest.plantTree(130, 140, "Oak", "Green", "Rough", 48);
    forest.plantTree(150, 160, "Pine", "Dark Green", "Smooth", 72);

    forest.draw();
    std::cout << std::endl;
    std::cout << "Total trees: " << forest.getTreeCount() << std::endl;
    std::cout << "Unique tree types: " << forest.getTypeCount() << std::endl;
    std::cout << std::endl;

    // Character rendering example
    std::cout << "--- Character Rendering ---" << std::endl;
    CharacterStyleFactory styleFactory;

    auto headingStyle = styleFactory.getStyle("Arial", 24, "Black");
    auto bodyStyle = styleFactory.getStyle("Times", 12, "Black");
    auto linkStyle = styleFactory.getStyle("Arial", 12, "Blue");

    headingStyle->render('H', 0, 0);
    bodyStyle->render('a', 0, 30);
    bodyStyle->render('b', 10, 30);
    linkStyle->render('L', 0, 50);
    linkStyle->render('I', 10, 50);

    std::cout << std::endl;
    std::cout << "Unique character styles: " << styleFactory.getStyleCount() << std::endl;

    std::cout << std::endl;
    std::cout << "Flyweight pattern shares intrinsic state to minimize memory usage" << std::endl;
    std::cout << "=== End Flyweight Demo ===" << std::endl;
    return 0;
}
