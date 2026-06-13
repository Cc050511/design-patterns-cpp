#include <iostream>
#include <memory>
#include <string>

// === State Demo ===
// Allows an object to alter its behavior when its internal state changes.
// The object will appear to change its class.

// Forward declaration
class Document;

// State interface
class DocumentState {
public:
    virtual ~DocumentState() = default;
    virtual void edit(Document& doc) = 0;
    virtual void publish(Document& doc) = 0;
    virtual void archive(Document& doc) = 0;
    virtual std::string getName() const = 0;
};

// Context: Document
class Document {
public:
    Document(std::string title);

    void setState(std::unique_ptr<DocumentState> state) {
        state_ = std::move(state);
        std::cout << "Document '" << title_ << "' state changed to: " << state_->getName() << std::endl;
    }

    void edit() {
        state_->edit(*this);
    }

    void publish() {
        state_->publish(*this);
    }

    void archive() {
        state_->archive(*this);
    }

    std::string getTitle() const { return title_; }
    std::string getCurrentState() const { return state_->getName(); }

private:
    std::string title_;
    std::unique_ptr<DocumentState> state_;
};

// Concrete State 1: Draft
class DraftState : public DocumentState {
public:
    void edit(Document& doc) override {
        std::cout << "Editing draft document '" << doc.getTitle() << "'" << std::endl;
    }

    void publish(Document& doc) override;

    void archive(Document& doc) override {
        std::cout << "Cannot archive: '" << doc.getTitle() << "' is still a draft" << std::endl;
    }

    std::string getName() const override { return "Draft"; }
};

// Concrete State 2: Moderation
class ModerationState : public DocumentState {
public:
    void edit(Document& doc) override {
        std::cout << "Cannot edit: '" << doc.getTitle() << "' is under moderation" << std::endl;
    }

    void publish(Document& doc) override;

    void archive(Document& doc) override;

    std::string getName() const override { return "Moderation"; }
};

// Concrete State 3: Published
class PublishedState : public DocumentState {
public:
    void edit(Document& doc) override {
        std::cout << "Creating new draft version of '" << doc.getTitle() << "'" << std::endl;
        doc.setState(std::make_unique<DraftState>());
    }

    void publish(Document& doc) override {
        std::cout << "Document '" << doc.getTitle() << "' is already published" << std::endl;
    }

    void archive(Document& doc) override;

    std::string getName() const override { return "Published"; }
};

// Concrete State 4: Archived
class ArchivedState : public DocumentState {
public:
    void edit(Document& doc) override {
        std::cout << "Cannot edit archived document '" << doc.getTitle() << "'" << std::endl;
    }

    void publish(Document& doc) override {
        std::cout << "Cannot publish archived document '" << doc.getTitle() << "'" << std::endl;
    }

    void archive(Document& doc) override {
        std::cout << "Document '" << doc.getTitle() << "' is already archived" << std::endl;
    }

    std::string getName() const override { return "Archived"; }
};

// Implementations after all states are declared
Document::Document(std::string title) : title_(std::move(title)) {
    state_ = std::make_unique<DraftState>();
}

void DraftState::publish(Document& doc) {
    std::cout << "Submitting '" << doc.getTitle() << "' for moderation" << std::endl;
    doc.setState(std::make_unique<ModerationState>());
}

void ModerationState::publish(Document& doc) {
    std::cout << "Document '" << doc.getTitle() << "' approved and published" << std::endl;
    doc.setState(std::make_unique<PublishedState>());
}

void ModerationState::archive(Document& doc) {
    std::cout << "Rejecting and archiving '" << doc.getTitle() << "'" << std::endl;
    doc.setState(std::make_unique<ArchivedState>());
}

void PublishedState::archive(Document& doc) {
    std::cout << "Archiving published document '" << doc.getTitle() << "'" << std::endl;
    doc.setState(std::make_unique<ArchivedState>());
}

// Another example: Traffic light
class TrafficLightState {
public:
    virtual ~TrafficLightState() = default;
    virtual void next(class TrafficLight& light) = 0;
    virtual std::string getColor() const = 0;
};

class TrafficLightRedState;
class TrafficLightYellowState;
class TrafficLightGreenState;

class TrafficLight {
public:
    TrafficLight() : state_(nullptr) {}

    void setState(std::unique_ptr<TrafficLightState> state) {
        state_ = std::move(state);
        std::cout << "Traffic light is now " << state_->getColor() << std::endl;
    }

    void next() {
        state_->next(*this);
    }

    std::string getColor() const {
        return state_ ? state_->getColor() : "Unknown";
    }

private:
    std::unique_ptr<TrafficLightState> state_;
};

class TrafficLightRedState : public TrafficLightState {
public:
    void next(TrafficLight& light) override;
    std::string getColor() const override { return "RED"; }
};

class TrafficLightGreenState : public TrafficLightState {
public:
    void next(TrafficLight& light) override;
    std::string getColor() const override { return "GREEN"; }
};

class TrafficLightYellowState : public TrafficLightState {
public:
    void next(TrafficLight& light) override;
    std::string getColor() const override { return "YELLOW"; }
};

void TrafficLightRedState::next(TrafficLight& light) {
    std::cout << "Red -> Green (cars can go)" << std::endl;
    light.setState(std::make_unique<TrafficLightGreenState>());
}

void TrafficLightGreenState::next(TrafficLight& light) {
    std::cout << "Green -> Yellow (prepare to stop)" << std::endl;
    light.setState(std::make_unique<TrafficLightYellowState>());
}

void TrafficLightYellowState::next(TrafficLight& light) {
    std::cout << "Yellow -> Red (stop)" << std::endl;
    light.setState(std::make_unique<TrafficLightRedState>());
}

int main() {
    std::cout << "=== State Demo ===" << std::endl;

    std::cout << "--- Document Workflow ---" << std::endl;
    Document doc("My Article");
    std::cout << std::endl;

    doc.edit();
    doc.publish();
    std::cout << std::endl;

    doc.edit();
    doc.publish();
    std::cout << std::endl;

    doc.publish();
    doc.edit();
    std::cout << std::endl;

    doc.publish();
    doc.archive();
    std::cout << std::endl;

    doc.edit();
    doc.archive();
    std::cout << std::endl;

    std::cout << "--- Traffic Light ---" << std::endl;
    TrafficLight light;
    light.setState(std::make_unique<TrafficLightRedState>());
    std::cout << std::endl;

    for (int i = 0; i < 6; ++i) {
        light.next();
        std::cout << std::endl;
    }

    std::cout << "State pattern changes object behavior based on internal state" << std::endl;
    std::cout << "=== End State Demo ===" << std::endl;
    return 0;
}
