#include <iostream>
#include <memory>
#include <string>
#include <vector>

// === Builder Demo ===
// Separates the construction of a complex object from its representation, allowing the same construction process to create different representations.

// Product: Computer
class Computer {
public:
    void setCPU(const std::string& cpu) { cpu_ = cpu; }
    void setRAM(const std::string& ram) { ram_ = ram; }
    void setStorage(const std::string& storage) { storage_ = storage; }
    void setGPU(const std::string& gpu) { gpu_ = gpu; }
    void setOS(const std::string& os) { os_ = os; }

    void showSpecs() const {
        std::cout << "Computer Specifications:" << std::endl;
        std::cout << "  CPU: " << cpu_ << std::endl;
        std::cout << "  RAM: " << ram_ << std::endl;
        std::cout << "  Storage: " << storage_ << std::endl;
        std::cout << "  GPU: " << gpu_ << std::endl;
        std::cout << "  OS: " << os_ << std::endl;
    }

private:
    std::string cpu_;
    std::string ram_;
    std::string storage_;
    std::string gpu_;
    std::string os_;
};

// Builder interface
class ComputerBuilder {
public:
    virtual ~ComputerBuilder() = default;
    virtual ComputerBuilder& setCPU(const std::string& cpu) = 0;
    virtual ComputerBuilder& setRAM(const std::string& ram) = 0;
    virtual ComputerBuilder& setStorage(const std::string& storage) = 0;
    virtual ComputerBuilder& setGPU(const std::string& gpu) = 0;
    virtual ComputerBuilder& setOS(const std::string& os) = 0;
    virtual std::unique_ptr<Computer> build() = 0;
};

// Concrete Builder
class DesktopBuilder : public ComputerBuilder {
public:
    DesktopBuilder() : computer_(std::make_unique<Computer>()) {}

    ComputerBuilder& setCPU(const std::string& cpu) override {
        computer_->setCPU(cpu);
        return *this;
    }
    ComputerBuilder& setRAM(const std::string& ram) override {
        computer_->setRAM(ram);
        return *this;
    }
    ComputerBuilder& setStorage(const std::string& storage) override {
        computer_->setStorage(storage);
        return *this;
    }
    ComputerBuilder& setGPU(const std::string& gpu) override {
        computer_->setGPU(gpu);
        return *this;
    }
    ComputerBuilder& setOS(const std::string& os) override {
        computer_->setOS(os);
        return *this;
    }

    std::unique_ptr<Computer> build() override {
        return std::move(computer_);
    }

private:
    std::unique_ptr<Computer> computer_;
};

// Director - defines the construction steps
class ComputerDirector {
public:
    explicit ComputerDirector(ComputerBuilder& builder) : builder_(builder) {}

    std::unique_ptr<Computer> buildGamingPC() {
        std::cout << "Building Gaming PC..." << std::endl;
        return builder_
            .setCPU("Intel Core i9-13900K")
            .setRAM("32GB DDR5")
            .setStorage("2TB NVMe SSD")
            .setGPU("NVIDIA RTX 4090")
            .setOS("Windows 11")
            .build();
    }

    std::unique_ptr<Computer> buildOfficePC() {
        std::cout << "Building Office PC..." << std::endl;
        return builder_
            .setCPU("Intel Core i5-13400")
            .setRAM("16GB DDR4")
            .setStorage("512GB SSD")
            .setGPU("Integrated Graphics")
            .setOS("Windows 11")
            .build();
    }

    std::unique_ptr<Computer> buildDeveloperPC() {
        std::cout << "Building Developer PC..." << std::endl;
        return builder_
            .setCPU("AMD Ryzen 9 7950X")
            .setRAM("64GB DDR5")
            .setStorage("4TB NVMe SSD")
            .setGPU("NVIDIA RTX 4070")
            .setOS("Linux Ubuntu")
            .build();
    }

private:
    ComputerBuilder& builder_;
};

int main() {
    std::cout << "=== Builder Demo ===" << std::endl;

    DesktopBuilder builder;
    ComputerDirector director(builder);

    auto gamingPC = director.buildGamingPC();
    gamingPC->showSpecs();
    std::cout << std::endl;

    // Reuse the same builder pattern with manual construction
    DesktopBuilder manualBuilder;
    auto customPC = manualBuilder
        .setCPU("Apple M3 Max")
        .setRAM("36GB Unified")
        .setStorage("1TB SSD")
        .setGPU("Integrated 40-core GPU")
        .setOS("macOS Sonoma")
        .build();
    std::cout << "Building Custom Laptop..." << std::endl;
    customPC->showSpecs();
    std::cout << std::endl;

    auto officePC = director.buildOfficePC();
    officePC->showSpecs();
    std::cout << std::endl;

    auto devPC = director.buildDeveloperPC();
    devPC->showSpecs();

    std::cout << "Builder pattern separates construction from representation" << std::endl;
    std::cout << "=== End Builder Demo ===" << std::endl;
    return 0;
}
