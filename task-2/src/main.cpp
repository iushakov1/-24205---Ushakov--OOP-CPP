
#include "modeparser.h"
#include "presetregistry.h"
#include "rule.h"
#include "universe.h"

class App{
public:
    App(int argc, char** argv) : argc(argc), argv(argv){}
    void run(){
        Universe universe;
        Rule rule;
        ModeParser modeParser(universe, rule);
        auto mode = modeParser.parseMode(argc, argv);
        mode->start();
    }
private:
    int argc;
    char** argv;
};

int main(int argc, char** argv) {
    App app(argc, argv);
    app.run();
}
