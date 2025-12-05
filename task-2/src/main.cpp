#include "modeparser.h"

class App{
public:
    App() = default;
    void run(int argc, char** argv){
        ModeParser modeParser;
        auto mode = modeParser.parseMode(argc, argv);
        mode->start();
    }
private:
};

int main(int argc, char** argv) {
    App app;
    app.run(argc, argv);
}
