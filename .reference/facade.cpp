#include <iostream>
#include <memory>
#include <string>
#include <vector>

// === Facade Demo ===
// Provides a unified interface to a set of interfaces in a subsystem.
// Defines a higher-level interface that makes the subsystem easier to use.

// Complex subsystem classes
class CPU {
public:
    void freeze() { std::cout << "CPU: Freezing processor" << std::endl; }
    void jump(long position) { std::cout << "CPU: Jumping to position " << position << std::endl; }
    void execute() { std::cout << "CPU: Executing instructions" << std::endl; }
};

class Memory {
public:
    void load(long position, const std::string& data) {
        std::cout << "Memory: Loading '" << data << "' at position " << position << std::endl;
    }
};

class HardDrive {
public:
    std::string read(long lba, int size) {
        std::cout << "HardDrive: Reading " << size << " bytes from sector " << lba << std::endl;
        return "boot_sector_data";
    }
};

class PowerSupply {
public:
    void turnOn() { std::cout << "PowerSupply: Turning on" << std::endl; }
    void turnOff() { std::cout << "PowerSupply: Turning off" << std::endl; }
    bool checkVoltage() {
        std::cout << "PowerSupply: Voltage OK" << std::endl;
        return true;
    }
};

class Display {
public:
    void showBootScreen() { std::cout << "Display: Showing boot screen" << std::endl; }
    void showDesktop() { std::cout << "Display: Showing desktop" << std::endl; }
    void showError(const std::string& msg) { std::cout << "Display: ERROR - " << msg << std::endl; }
};

// Facade: simplifies the complex subsystem
class ComputerFacade {
public:
    ComputerFacade()
        : cpu_(std::make_unique<CPU>()),
          memory_(std::make_unique<Memory>()),
          hardDrive_(std::make_unique<HardDrive>()),
          power_(std::make_unique<PowerSupply>()),
          display_(std::make_unique<Display>()) {}

    void start() {
        std::cout << "--- Starting Computer ---" << std::endl;
        power_->turnOn();
        if (!power_->checkVoltage()) {
            display_->showError("Power failure");
            return;
        }
        cpu_->freeze();
        auto bootData = hardDrive_->read(0, 1024);
        memory_->load(0, bootData);
        cpu_->jump(0);
        cpu_->execute();
        display_->showBootScreen();
        display_->showDesktop();
        std::cout << "Computer started successfully!" << std::endl;
    }

    void shutdown() {
        std::cout << "--- Shutting Down Computer ---" << std::endl;
        cpu_->freeze();
        power_->turnOff();
        std::cout << "Computer shut down." << std::endl;
    }

private:
    std::unique_ptr<CPU> cpu_;
    std::unique_ptr<Memory> memory_;
    std::unique_ptr<HardDrive> hardDrive_;
    std::unique_ptr<PowerSupply> power_;
    std::unique_ptr<Display> display_;
};

// Another example: Home Theater Facade
class Amplifier {
public:
    void on() { std::cout << "Amplifier: On" << std::endl; }
    void off() { std::cout << "Amplifier: Off" << std::endl; }
    void setVolume(int level) { std::cout << "Amplifier: Volume set to " << level << std::endl; }
};

class DVDPlayer {
public:
    void on() { std::cout << "DVD Player: On" << std::endl; }
    void off() { std::cout << "DVD Player: Off" << std::endl; }
    void play(const std::string& movie) { std::cout << "DVD Player: Playing '" << movie << "'" << std::endl; }
    void stop() { std::cout << "DVD Player: Stopped" << std::endl; }
};

class Projector {
public:
    void on() { std::cout << "Projector: On" << std::endl; }
    void off() { std::cout << "Projector: Off" << std::endl; }
    void setInput(const std::string& input) { std::cout << "Projector: Input set to " << input << std::endl; }
};

class HomeTheaterFacade {
public:
    void watchMovie(const std::string& movie) {
        std::cout << "--- Get ready to watch movie ---" << std::endl;
        projector_.on();
        projector_.setInput("DVD");
        amp_.on();
        amp_.setVolume(10);
        dvd_.on();
        dvd_.play(movie);
        std::cout << "Movie started!" << std::endl;
    }

    void endMovie() {
        std::cout << "--- Ending movie ---" << std::endl;
        dvd_.stop();
        dvd_.off();
        amp_.off();
        projector_.off();
        std::cout << "Movie ended." << std::endl;
    }

private:
    Amplifier amp_;
    DVDPlayer dvd_;
    Projector projector_;
};

int main() {
    std::cout << "=== Facade Demo ===" << std::endl;

    // Computer facade
    ComputerFacade computer;
    computer.start();
    std::cout << std::endl;
    computer.shutdown();
    std::cout << std::endl;

    // Home theater facade
    HomeTheaterFacade theater;
    theater.watchMovie("The Matrix");
    std::cout << std::endl;
    theater.endMovie();

    std::cout << std::endl;
    std::cout << "Facade pattern provides a simplified interface to a complex subsystem" << std::endl;
    std::cout << "=== End Facade Demo ===" << std::endl;
    return 0;
}
