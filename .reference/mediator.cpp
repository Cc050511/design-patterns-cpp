#include <iostream>
#include <memory>
#include <string>
#include <vector>

// === Mediator Demo ===
// Defines an object that encapsulates how a set of objects interact.
// Promotes loose coupling by keeping objects from referring to each other explicitly.

// Forward declaration
class ChatMediator;

// Colleague interface
class User {
public:
    User(std::string name, std::shared_ptr<ChatMediator> mediator)
        : name_(std::move(name)), mediator_(mediator) {}

    virtual ~User() = default;

    std::string getName() const { return name_; }

    virtual void send(const std::string& message) = 0;
    virtual void receive(const std::string& from, const std::string& message) = 0;

protected:
    std::string name_;
    std::shared_ptr<ChatMediator> mediator_;
};

// Mediator interface
class ChatMediator {
public:
    virtual ~ChatMediator() = default;
    virtual void sendMessage(const std::string& message, std::shared_ptr<User> sender) = 0;
    virtual void addUser(std::shared_ptr<User> user) = 0;
};

// Concrete Mediator
class ChatRoom : public ChatMediator {
public:
    void addUser(std::shared_ptr<User> user) override {
        users_.push_back(user);
        std::cout << user->getName() << " joined the chat" << std::endl;
    }

    void sendMessage(const std::string& message, std::shared_ptr<User> sender) override {
        for (auto& user : users_) {
            if (user != sender) {
                user->receive(sender->getName(), message);
            }
        }
    }

private:
    std::vector<std::shared_ptr<User>> users_;
};

// Another example: Air Traffic Control
class Aircraft;

class AirTrafficControl {
public:
    virtual ~AirTrafficControl() = default;
    virtual void registerAircraft(std::shared_ptr<Aircraft> aircraft) = 0;
    virtual void requestLanding(std::shared_ptr<Aircraft> aircraft) = 0;
    virtual void requestTakeoff(std::shared_ptr<Aircraft> aircraft) = 0;
};

class Aircraft {
public:
    Aircraft(std::string id, std::shared_ptr<AirTrafficControl> atc)
        : id_(std::move(id)), atc_(atc) {}

    virtual ~Aircraft() = default;

    std::string getId() const { return id_; }

    void land() {
        std::cout << id_ << " is landing" << std::endl;
    }

    void takeoff() {
        std::cout << id_ << " is taking off" << std::endl;
    }

protected:
    std::string id_;
    std::shared_ptr<AirTrafficControl> atc_;
};

class ControlTower : public AirTrafficControl {
public:
    void registerAircraft(std::shared_ptr<Aircraft> aircraft) override {
        aircraft_.push_back(aircraft);
        std::cout << "Control Tower: " << aircraft->getId() << " registered" << std::endl;
    }

    void requestLanding(std::shared_ptr<Aircraft> aircraft) override {
        std::cout << "Control Tower: Clearance granted to " << aircraft->getId() << " for landing" << std::endl;
        aircraft->land();
    }

    void requestTakeoff(std::shared_ptr<Aircraft> aircraft) override {
        std::cout << "Control Tower: Clearance granted to " << aircraft->getId() << " for takeoff" << std::endl;
        aircraft->takeoff();
    }

private:
    std::vector<std::shared_ptr<Aircraft>> aircraft_;
};

class ChatUserImpl : public User, public std::enable_shared_from_this<ChatUserImpl> {
public:
    ChatUserImpl(std::string name, std::shared_ptr<ChatMediator> mediator)
        : User(std::move(name), mediator) {}

    void send(const std::string& message) override {
        std::cout << name_ << " sends: " << message << std::endl;
        mediator_->sendMessage(message, shared_from_this());
    }

    void receive(const std::string& from, const std::string& message) override {
        std::cout << name_ << " received from " << from << ": " << message << std::endl;
    }
};

class AircraftImpl : public Aircraft, public std::enable_shared_from_this<AircraftImpl> {
public:
    AircraftImpl(std::string id, std::shared_ptr<AirTrafficControl> atc)
        : Aircraft(std::move(id), atc) {}

    void requestLanding() {
        std::cout << id_ << " requesting landing clearance" << std::endl;
        atc_->requestLanding(shared_from_this());
    }

    void requestTakeoff() {
        std::cout << id_ << " requesting takeoff clearance" << std::endl;
        atc_->requestTakeoff(shared_from_this());
    }
};

int main() {
    std::cout << "=== Mediator Demo ===" << std::endl;

    // Chat room example
    std::cout << "--- Chat Room ---" << std::endl;
    auto chatRoom = std::make_shared<ChatRoom>();

    auto user1 = std::make_shared<ChatUserImpl>("Alice", chatRoom);
    auto user2 = std::make_shared<ChatUserImpl>("Bob", chatRoom);
    auto user3 = std::make_shared<ChatUserImpl>("Charlie", chatRoom);

    chatRoom->addUser(user1);
    chatRoom->addUser(user2);
    chatRoom->addUser(user3);
    std::cout << std::endl;

    user1->send("Hello everyone!");
    std::cout << std::endl;
    user2->send("Hi Alice!");
    std::cout << std::endl;

    // Air traffic control example
    std::cout << "--- Air Traffic Control ---" << std::endl;
    auto tower = std::make_shared<ControlTower>();

    auto plane1 = std::make_shared<AircraftImpl>("Flight 101", tower);
    auto plane2 = std::make_shared<AircraftImpl>("Flight 202", tower);

    tower->registerAircraft(plane1);
    tower->registerAircraft(plane2);
    std::cout << std::endl;

    plane1->requestLanding();
    std::cout << std::endl;
    plane2->requestTakeoff();

    std::cout << std::endl;
    std::cout << "Mediator pattern centralizes complex communications between objects" << std::endl;
    std::cout << "=== End Mediator Demo ===" << std::endl;
    return 0;
}
