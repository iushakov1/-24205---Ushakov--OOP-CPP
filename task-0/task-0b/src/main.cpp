#include "ResultWriter.h"
#include "TextReader.h"
#include "WordCounter.h"

class Application{
public:
    Application(const std::string& input, const std::string& output) : reader(input), writer(output){};
    void run(){
        auto lines = reader.readLines();
        counter.processLines(lines);
        writer.write(counter.getWordCounter(), counter.getTotalWords());
    }
private:
    TextReader reader;
    WordCounter counter;
    ResultWriter writer;

};

int main(int argc, char* argv[]){
    Application app(argv[1], argv[2]);
    app.run();
    return 0;
}