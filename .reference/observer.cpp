#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

// === Observer Demo ===
// Defines a one-to-many dependency between objects so that when one object changes state,
// all its dependents are notified and updated automatically.

// Observer interface
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& event, const std::string& data) = 0;
    virtual std::string getName() const = 0;
};

// Subject interface
class Subject {
public:
    virtual ~Subject() = default;
    virtual void attach(std::shared_ptr<Observer> observer) = 0;
    virtual void detach(std::shared_ptr<Observer> observer) = 0;
    virtual void notify(const std::string& event, const std::string& data) = 0;
};

// Concrete Subject: WeatherStation
class WeatherStation : public Subject {
public:
    void attach(std::shared_ptr<Observer> observer) override {
        observers_.push_back(observer);
        std::cout << "Observer attached: " << observer->getName() << std::endl;
    }

    void detach(std::shared_ptr<Observer> observer) override {
        observers_.erase(
            std::remove_if(observers_.begin(), observers_.end(),
                [&observer](const auto& o) { return o == observer; }),
            observers_.end()
        );
    }

    void notify(const std::string& event, const std::string& data) override {
        for (auto& observer : observers_) {
            observer->update(event, data);
        }
    }

    void setTemperature(double temp) {
        temperature_ = temp;
        std::cout << "WeatherStation: Temperature changed to " << temp << "C" << std::endl;
        notify("temperature", std::to_string(temp));
    }

    void setHumidity(double humidity) {
        humidity_ = humidity;
        std::cout << "WeatherStation: Humidity changed to " << humidity << "%" << std::endl;
        notify("humidity", std::to_string(humidity));
    }

private:
    std::vector<std::shared_ptr<Observer>> observers_;
    double temperature_ = 0.0;
    double humidity_ = 0.0;
};

// Concrete Observer: PhoneDisplay
class PhoneDisplay : public Observer {
public:
    explicit PhoneDisplay(std::string name) : name_(std::move(name)) {}

    void update(const std::string& event, const std::string& data) override {
        std::cout << "[" << name_ << "] Phone display updated - " << event << ": " << data << std::endl;
    }

    std::string getName() const override { return name_; }

private:
    std::string name_;
};

// Concrete Observer: DesktopDisplay
class DesktopDisplay : public Observer {
public:
    explicit DesktopDisplay(std::string name) : name_(std::move(name)) {}

    void update(const std::string& event, const std::string& data) override {
        std::cout << "[" << name_ << "] Desktop widget updated - " << event << ": " << data << std::endl;
    }

    std::string getName() const override { return name_; }

private:
    std::string name_;
};

// Concrete Observer: Logger
class WeatherLogger : public Observer {
public:
    void update(const std::string& event, const std::string& data) override {
        std::cout << "[Logger] Event logged: " << event << "=" << data << std::endl;
    }

    std::string getName() const override { return "Logger"; }
};

// Another example: Stock price monitoring
class StockExchange : public Subject {
public:
    void attach(std::shared_ptr<Observer> observer) override {
        observers_.push_back(observer);
    }

    void detach(std::shared_ptr<Observer> observer) override {
        observers_.erase(
            std::remove_if(observers_.begin(), observers_.end(),
                [&observer](const auto& o) { return o == observer; }),
            observers_.end()
        );
    }

    void notify(const std::string& event, const std::string& data) override {
        for (auto& observer : observers_) {
            observer->update(event, data);
        }
    }

    void setPrice(const std::string& symbol, double price) {
        std::cout << "StockExchange: " << symbol << " = $" << price << std::endl;
        notify(symbol, std::to_string(price));
    }

private:
    std::vector<std::shared_ptr<Observer>> observers_;
};

class StockTrader : public Observer {
public:
    explicit StockTrader(std::string name) : name_(std::move(name)) {}

    void update(const std::string& event, const std::string& data) override {
        double price = std::stod(data);
        std::cout << "[" << name_ << "] Alert: " << event << " price is $" << price;
        if (price > 150.0) {
            std::cout << " -> SELL signal!";
        } else if (price < 100.0) {
            std::cout << " -> BUY signal!";
        }
        std::cout << std::endl;
    }

    std::string getName() const override { return name_; }

private:
    std::string name_;
};

int main() {
    std::cout << "=== Observer Demo ===" << std::endl;

    // Weather station example
    std::cout << "--- Weather Station ---" << std::endl;
    WeatherStation station;

    auto phone = std::make_shared<PhoneDisplay>("Phone");
    auto desktop = std::make_shared<DesktopDisplay>("Desktop");
    auto logger = std::make_shared<WeatherLogger>();

    station.attach(phone);
    station.attach(desktop);
    station.attach(logger);
    std::cout << std::endl;

    station.setTemperature(25.5);
    std::cout << std::endl;
    station.setHumidity(60.0);
    std::cout << std::endl;

    // Detach one observer
    std::cout << "Detaching desktop observer..." << std::endl;
    station.detach(desktop);
    station.setTemperature(30.0);
    std::cout << std::endl;

    // Stock exchange example
    std::cout << "--- Stock Exchange ---" << std::endl;
    StockExchange exchange;

    auto trader1 = std::make_shared<StockTrader>("Alice");
    auto trader2 = std::make_shared<StockTrader>("Bob");

    exchange.attach(trader1);
    exchange.attach(trader2);

    exchange.setPrice("AAPL", 120.0);
    exchange.setPrice("GOOGL", 180.0);
    exchange.setPrice("TSLA", 90.0);

    std::cout << std::endl;
    std::cout << "Observer pattern notifies dependents automatically on state change" << std::endl;
    std::cout << "=== End Observer Demo ===" << std::endl;
    return 0;
}
