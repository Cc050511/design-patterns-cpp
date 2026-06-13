#include <iostream>
#include <memory>
#include <string>

// === Abstract Factory Demo ===
// Provides an interface for creating families of related or dependent objects without specifying concrete classes.

// Abstract Product A: Button
class Button {
public:
    virtual ~Button() = default;
    virtual void render() const = 0;
    virtual void onClick() const = 0;
};

// Abstract Product B: Checkbox
class Checkbox {
public:
    virtual ~Checkbox() = default;
    virtual void render() const = 0;
    virtual void toggle() = 0;
};

// Concrete Product A1: WindowsButton
class WindowsButton : public Button {
public:
    void render() const override {
        std::cout << "Rendering Windows-style button" << std::endl;
    }
    void onClick() const override {
        std::cout << "Windows button clicked!" << std::endl;
    }
};

// Concrete Product A2: MacButton
class MacButton : public Button {
public:
    void render() const override {
        std::cout << "Rendering Mac-style button" << std::endl;
    }
    void onClick() const override {
        std::cout << "Mac button clicked!" << std::endl;
    }
};

// Concrete Product B1: WindowsCheckbox
class WindowsCheckbox : public Checkbox {
public:
    void render() const override {
        std::cout << "Rendering Windows-style checkbox [" << (checked_ ? "X" : " ") << "]" << std::endl;
    }
    void toggle() override {
        checked_ = !checked_;
        std::cout << "Windows checkbox toggled to: " << (checked_ ? "checked" : "unchecked") << std::endl;
    }
private:
    bool checked_ = false;
};

// Concrete Product B2: MacCheckbox
class MacCheckbox : public Checkbox {
public:
    void render() const override {
        std::cout << "Rendering Mac-style checkbox [" << (checked_ ? "●" : "○") << "]" << std::endl;
    }
    void toggle() override {
        checked_ = !checked_;
        std::cout << "Mac checkbox toggled to: " << (checked_ ? "checked" : "unchecked") << std::endl;
    }
private:
    bool checked_ = false;
};

// Abstract Factory
class GUIFactory {
public:
    virtual ~GUIFactory() = default;
    virtual std::unique_ptr<Button> createButton() const = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() const = 0;
};

// Concrete Factory 1: WindowsFactory
class WindowsFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<WindowsButton>();
    }
    std::unique_ptr<Checkbox> createCheckbox() const override {
        return std::make_unique<WindowsCheckbox>();
    }
};

// Concrete Factory 2: MacFactory
class MacFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<MacButton>();
    }
    std::unique_ptr<Checkbox> createCheckbox() const override {
        return std::make_unique<MacCheckbox>();
    }
};

// Client code - works with any factory
void buildUI(const GUIFactory& factory) {
    auto button = factory.createButton();
    auto checkbox = factory.createCheckbox();
    button->render();
    checkbox->render();
    button->onClick();
    checkbox->toggle();
    checkbox->render();
}

int main() {
    std::cout << "=== Abstract Factory Demo ===" << std::endl;

    std::cout << "--- Building Windows UI ---" << std::endl;
    WindowsFactory windowsFactory;
    buildUI(windowsFactory);

    std::cout << "--- Building Mac UI ---" << std::endl;
    MacFactory macFactory;
    buildUI(macFactory);

    std::cout << "Abstract Factory ensures UI components are consistent within each family" << std::endl;
    std::cout << "=== End Abstract Factory Demo ===" << std::endl;
    return 0;
}
