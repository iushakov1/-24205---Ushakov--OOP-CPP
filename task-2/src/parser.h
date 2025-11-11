#ifndef TASK_2_PARSER_H
#define TASK_2_PARSER_H
#include <string>
#include <variant>

struct Options{
    int mode;
    int iteration;
    std::string inputPath;
    std::string outputPath;
};
struct Command{
    std::string name;
    std::string args;
    int digitParam;
};
struct ParseError{
    std::string message;
};

class Parser {
public:
    Parser() = default;
    static std::variant<Command, ParseError> parseCommand(std::string& string);
    static std::variant<Options, ParseError> parseArgv(int argc, char** argv);
private:
    static bool getNWordFromString(int N, const std::string& s, std::string& out) {
        int n = 1;
        size_t i1 = 0;
        size_t i2 = 0;
        while(n <= N) {
            i1 = s.find_first_not_of(' ', i2);
            if (i1 == std::string::npos) return false;
            i2 = s.find_first_of(' ', i1);
            if(i2 == std::string::npos){
                i2 = s.size();
            }
            if(n == N) {
                out = s.substr(i1, (i2 == std::string::npos) ? s.size() - i1 : i2 - i1);
                return true;
            }
            ++n;
        }
        return false;
    }
};


#endif