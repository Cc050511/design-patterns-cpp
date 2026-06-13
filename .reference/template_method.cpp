#include <iostream>
#include <memory>
#include <string>

// === Template Method Demo ===
// Defines the skeleton of an algorithm in an operation, deferring some steps to subclasses.
// Template Method lets subclasses redefine certain steps of an algorithm without changing the algorithm's structure.

// Abstract Class with template method
class DataMiner {
public:
    // Template method - defines the algorithm skeleton
    void mine(const std::string& path) {
        std::cout << "=== Starting data mining process ===" << std::endl;
        openFile(path);
        extractData();
        parseData();
        analyzeData();
        sendReport();
        closeFile();
        std::cout << "=== Data mining complete ===" << std::endl;
    }

    virtual ~DataMiner() = default;

protected:
    // Primitive operations - must be implemented by subclasses
    virtual void openFile(const std::string& path) = 0;
    virtual void extractData() = 0;
    virtual void parseData() = 0;
    virtual void closeFile() = 0;

    // Hook method - default implementation, can be overridden
    virtual void analyzeData() {
        std::cout << "  [Default] Analyzing extracted data..." << std::endl;
    }

    // Concrete operation - shared by all subclasses
    void sendReport() {
        std::cout << "  [Common] Sending analysis report to server" << std::endl;
    }
};

// Concrete Class 1: PDF Data Miner
class PdfDataMiner : public DataMiner {
protected:
    void openFile(const std::string& path) override {
        std::cout << "  [PDF] Opening PDF file: " << path << std::endl;
    }

    void extractData() override {
        std::cout << "  [PDF] Extracting text from PDF pages" << std::endl;
    }

    void parseData() override {
        std::cout << "  [PDF] Parsing PDF structure and metadata" << std::endl;
    }

    void closeFile() override {
        std::cout << "  [PDF] Closing PDF document" << std::endl;
    }

    void analyzeData() override {
        std::cout << "  [PDF] Performing PDF-specific text analysis" << std::endl;
    }
};

// Concrete Class 2: CSV Data Miner
class CsvDataMiner : public DataMiner {
protected:
    void openFile(const std::string& path) override {
        std::cout << "  [CSV] Opening CSV file: " << path << std::endl;
    }

    void extractData() override {
        std::cout << "  [CSV] Reading rows and columns" << std::endl;
    }

    void parseData() override {
        std::cout << "  [CSV] Parsing comma-separated values" << std::endl;
    }

    void closeFile() override {
        std::cout << "  [CSV] Closing CSV file" << std::endl;
    }

    // Uses default analyzeData() hook
};

// Concrete Class 3: XML Data Miner
class XmlDataMiner : public DataMiner {
protected:
    void openFile(const std::string& path) override {
        std::cout << "  [XML] Opening XML file: " << path << std::endl;
    }

    void extractData() override {
        std::cout << "  [XML] Extracting XML nodes and attributes" << std::endl;
    }

    void parseData() override {
        std::cout << "  [XML] Parsing XML DOM tree" << std::endl;
    }

    void closeFile() override {
        std::cout << "  [XML] Closing XML document" << std::endl;
    }

    void analyzeData() override {
        std::cout << "  [XML] Validating against XML schema" << std::endl;
    }
};

// Another example: Game AI with template method
class GameAI {
public:
    void takeTurn() {
        collectResources();
        buildStructures();
        buildUnits();
        attack();
    }

    virtual ~GameAI() = default;

protected:
    virtual void collectResources() = 0;
    virtual void buildStructures() = 0;
    virtual void buildUnits() = 0;

    void attack() {
        std::cout << "  [Common] Sending units to attack enemy" << std::endl;
    }

    // Hook
    virtual bool shouldScout() const { return false; }
};

class OrcsAI : public GameAI {
protected:
    void collectResources() override {
        std::cout << "  [Orcs] Collecting gold and wood aggressively" << std::endl;
    }

    void buildStructures() override {
        std::cout << "  [Orcs] Building barracks and war mills" << std::endl;
    }

    void buildUnits() override {
        std::cout << "  [Orcs] Training grunts and raiders" << std::endl;
    }

    bool shouldScout() const override { return true; }
};

class ElvesAI : public GameAI {
protected:
    void collectResources() override {
        std::cout << "  [Elves] Gathering mana and lumber sustainably" << std::endl;
    }

    void buildStructures() override {
        std::cout << "  [Elves] Building ancient protectors and moon wells" << std::endl;
    }

    void buildUnits() override {
        std::cout << "  [Elves] Training archers and druids" << std::endl;
    }
};

int main() {
    std::cout << "=== Template Method Demo ===" << std::endl;

    // Data mining example
    std::cout << "--- PDF Mining ---" << std::endl;
    PdfDataMiner pdfMiner;
    pdfMiner.mine("report.pdf");
    std::cout << std::endl;

    std::cout << "--- CSV Mining ---" << std::endl;
    CsvDataMiner csvMiner;
    csvMiner.mine("data.csv");
    std::cout << std::endl;

    std::cout << "--- XML Mining ---" << std::endl;
    XmlDataMiner xmlMiner;
    xmlMiner.mine("config.xml");
    std::cout << std::endl;

    // Game AI example
    std::cout << "--- Game AI Turns ---" << std::endl;
    std::cout << "Orcs turn:" << std::endl;
    OrcsAI orcs;
    orcs.takeTurn();
    std::cout << std::endl;

    std::cout << "Elves turn:" << std::endl;
    ElvesAI elves;
    elves.takeTurn();

    std::cout << std::endl;
    std::cout << "Template Method defines algorithm skeleton with customizable steps" << std::endl;
    std::cout << "=== End Template Method Demo ===" << std::endl;
    return 0;
}
