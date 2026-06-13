#include <iostream>
#include <memory>
#include <string>

// === Adapter Demo ===
// Converts the interface of a class into another interface clients expect.
// Allows incompatible interfaces to work together.

// Target interface (what the client expects)
class MediaPlayer {
public:
    virtual ~MediaPlayer() = default;
    virtual void play(const std::string& filename) = 0;
};

// Adaptee 1: Existing advanced media player for MP4
class AdvancedMediaPlayer {
public:
    virtual ~AdvancedMediaPlayer() = default;
    virtual void playMp4(const std::string& filename) {
        std::cout << "Playing mp4 file: " << filename << std::endl;
    }
};

// Adaptee 2: Existing advanced media player for VLC
class VlcPlayer {
public:
    void playVlc(const std::string& filename) {
        std::cout << "Playing vlc file: " << filename << std::endl;
    }
};

// Adapter for MP4 (class adapter using inheritance)
class Mp4Adapter : public MediaPlayer, private AdvancedMediaPlayer {
public:
    void play(const std::string& filename) override {
        playMp4(filename);
    }
};

// Adapter for VLC (object adapter using composition)
class VlcAdapter : public MediaPlayer {
public:
    void play(const std::string& filename) override {
        vlcPlayer_.playVlc(filename);
    }
private:
    VlcPlayer vlcPlayer_;
};

// Client code
class AudioPlayer : public MediaPlayer {
public:
    void play(const std::string& filename) override {
        if (filename.ends_with(".mp3")) {
            std::cout << "Playing mp3 file: " << filename << std::endl;
        } else if (filename.ends_with(".mp4")) {
            mp4Adapter_.play(filename);
        } else if (filename.ends_with(".vlc")) {
            vlcAdapter_.play(filename);
        } else {
            std::cout << "Invalid media. " << filename << " format not supported" << std::endl;
        }
    }
private:
    Mp4Adapter mp4Adapter_;
    VlcAdapter vlcAdapter_;
};

// Another example: Voltage adapter
class EuropeanSocket {
public:
    int voltage() const { return 220; }
    std::string type() const { return "European Type C"; }
};

class USASocket {
public:
    int voltage() const { return 110; }
    std::string type() const { return "USA Type A"; }
};

class USAToEuropeanAdapter {
public:
    explicit USAToEuropeanAdapter(const EuropeanSocket& socket) : socket_(socket) {}

    int voltage() const {
        // Step down voltage
        return socket_.voltage() / 2;
    }

    std::string type() const {
        return "USA Type A (adapted from " + socket_.type() + ")";
    }

private:
    EuropeanSocket socket_;
};

int main() {
    std::cout << "=== Adapter Demo ===" << std::endl;

    // Media player adapter example
    AudioPlayer player;
    std::cout << "--- Media Player ---" << std::endl;
    player.play("song.mp3");
    player.play("movie.mp4");
    player.play("video.vlc");
    player.play("document.pdf");
    std::cout << std::endl;

    // Voltage adapter example
    std::cout << "--- Voltage Adapter ---" << std::endl;
    EuropeanSocket europeanSocket;
    std::cout << "European socket: " << europeanSocket.voltage() << "V, " << europeanSocket.type() << std::endl;

    USAToEuropeanAdapter adapter(europeanSocket);
    std::cout << "Adapted for USA: " << adapter.voltage() << "V, " << adapter.type() << std::endl;

    std::cout << std::endl;
    std::cout << "Adapter pattern allows incompatible interfaces to work together" << std::endl;
    std::cout << "=== End Adapter Demo ===" << std::endl;
    return 0;
}
