#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <stack>

// === Memento Demo ===
// Without violating encapsulation, captures and externalizes an object's internal state
// so that the object can be restored to this state later.

// Memento (stores state)
class EditorMemento {
public:
    explicit EditorMemento(std::string content, int cursorPosition)
        : content_(std::move(content)), cursorPosition_(cursorPosition) {}

    std::string getContent() const { return content_; }
    int getCursorPosition() const { return cursorPosition_; }

private:
    std::string content_;
    int cursorPosition_;
};

// Originator: TextEditor
class TextEditor {
public:
    void type(const std::string& text) {
        content_ += text;
        cursorPosition_ = static_cast<int>(content_.size());
    }

    void deleteLast(int n) {
        if (n >= static_cast<int>(content_.size())) {
            content_.clear();
        } else {
            content_ = content_.substr(0, content_.size() - n);
        }
        cursorPosition_ = static_cast<int>(content_.size());
    }

    std::unique_ptr<EditorMemento> save() {
        return std::make_unique<EditorMemento>(content_, cursorPosition_);
    }

    void restore(const EditorMemento& memento) {
        content_ = memento.getContent();
        cursorPosition_ = memento.getCursorPosition();
    }

    std::string getContent() const { return content_; }
    int getCursorPosition() const { return cursorPosition_; }

    void show() const {
        std::cout << "Editor: \"" << content_ << "\" (cursor: " << cursorPosition_ << ")" << std::endl;
    }

private:
    std::string content_;
    int cursorPosition_ = 0;
};

// Caretaker: History manager
class EditorHistory {
public:
    void save(std::unique_ptr<EditorMemento> memento) {
        history_.push(std::move(memento));
        std::cout << "State saved to history" << std::endl;
    }

    bool canUndo() const {
        return !history_.empty();
    }

    std::unique_ptr<EditorMemento> undo() {
        if (history_.empty()) {
            return nullptr;
        }
        auto memento = std::move(history_.top());
        history_.pop();
        return memento;
    }

    size_t getHistorySize() const { return history_.size(); }

private:
    std::stack<std::unique_ptr<EditorMemento>> history_;
};

// Another example: Game state
class GameState {
public:
    GameState(int level, int health, int score, std::string position)
        : level_(level), health_(health), score_(score), position_(std::move(position)) {}

    int getLevel() const { return level_; }
    int getHealth() const { return health_; }
    int getScore() const { return score_; }
    std::string getPosition() const { return position_; }

    void show() const {
        std::cout << "Level: " << level_ << ", Health: " << health_
                  << ", Score: " << score_ << ", Position: " << position_ << std::endl;
    }

private:
    int level_;
    int health_;
    int score_;
    std::string position_;
};

class GameCharacter {
public:
    void playLevel(int level) {
        level_ = level;
        health_ = 100;
        score_ = level * 100;
        position_ = "Level " + std::to_string(level) + " Start";
    }

    void takeDamage(int damage) {
        health_ -= damage;
        if (health_ < 0) health_ = 0;
    }

    void move(const std::string& position) {
        position_ = position;
    }

    std::unique_ptr<GameState> save() {
        return std::make_unique<GameState>(level_, health_, score_, position_);
    }

    void restore(const GameState& state) {
        level_ = state.getLevel();
        health_ = state.getHealth();
        score_ = state.getScore();
        position_ = state.getPosition();
    }

    void show() const {
        std::cout << "Character: Level=" << level_ << ", HP=" << health_
                  << ", Score=" << score_ << ", Pos=" << position_ << std::endl;
    }

private:
    int level_ = 1;
    int health_ = 100;
    int score_ = 0;
    std::string position_ = "Start";
};

class GameSaveManager {
public:
    void saveGame(std::unique_ptr<GameState> state, const std::string& slot) {
        saves_[slot] = std::move(state);
        std::cout << "Game saved to slot: " << slot << std::endl;
    }

    std::unique_ptr<GameState> loadGame(const std::string& slot) {
        auto it = saves_.find(slot);
        if (it != saves_.end()) {
            std::cout << "Game loaded from slot: " << slot << std::endl;
            return std::make_unique<GameState>(*it->second);
        }
        return nullptr;
    }

private:
    std::unordered_map<std::string, std::unique_ptr<GameState>> saves_;
};

int main() {
    std::cout << "=== Memento Demo ===" << std::endl;

    // Text editor example
    std::cout << "--- Text Editor ---" << std::endl;
    TextEditor editor;
    EditorHistory history;

    editor.type("Hello");
    editor.show();
    history.save(editor.save());

    editor.type(" World");
    editor.show();
    history.save(editor.save());

    editor.type("!!!");
    editor.show();
    history.save(editor.save());

    std::cout << std::endl << "--- Undo Operations ---" << std::endl;
    while (history.canUndo()) {
        auto memento = history.undo();
        if (memento) {
            editor.restore(*memento);
            editor.show();
        }
    }
    std::cout << std::endl;

    // Game save example
    std::cout << "--- Game Saves ---" << std::endl;
    GameCharacter character;
    GameSaveManager saveManager;

    character.playLevel(1);
    character.show();
    saveManager.saveGame(character.save(), "Level1");

    character.move("Dungeon Room A");
    character.takeDamage(30);
    character.show();
    saveManager.saveGame(character.save(), "MidLevel1");

    character.move("Boss Room");
    character.takeDamage(50);
    character.show();

    std::cout << std::endl << "Loading mid-level save..." << std::endl;
    auto save = saveManager.loadGame("MidLevel1");
    if (save) {
        character.restore(*save);
        character.show();
    }

    std::cout << std::endl;
    std::cout << "Memento pattern captures and restores object state without breaking encapsulation" << std::endl;
    std::cout << "=== End Memento Demo ===" << std::endl;
    return 0;
}
