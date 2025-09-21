#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <list>
#include <map>
#include <vector>

class TextReader{
public:
    explicit TextReader(const std::string& filename) : filename(filename){}

    std::list<std::string> readLines(){
        std::ifstream inputFile(filename);
        std::list<std::string> lines;
        std::string line;

        while(getline(inputFile, line)){
            lines.push_back(line);
        }
        return lines;
    }
private:
    std::string filename;
};

class WordCounter{
public:
    void processLines(const std::list<std::string>& lines){
        for(const auto& line : lines){
            size_t start = 0;
            while(start < line.size()){
                size_t first = line.find_first_not_of(' ', start);
                if(first == std::string::npos) break;

                size_t last = line.find_first_of(' ', first);
                if(last == std::string::npos) last = line.size();

                std::string word = line.substr(first, last - first);
                ++totalWords;
                ++wordCount[word];
                start = last;
            }
        }
    }

    const std::map<std::string, int>& getWordCount() const{
        return wordCount;
    }

    int getTotalWords() const{
        return totalWords;
    }
private:
    std::map<std::string, int> wordCount;
    int totalWords = 0;
};


class ResultWriter {
public:
    explicit ResultWriter(const std::string& filename) : filename(filename) {}

    void write(const std::map<std::string, int>& wordCount, int totalWords) {
        std::ofstream outputFile(filename);
        std::vector<std::pair<std::string, int>> vec(wordCount.begin(), wordCount.end());

        std::sort(vec.begin(), vec.end(),
                  [](const auto& a, const auto& b) { return a.second > b.second; });

        outputFile << std::fixed << std::setprecision(1);
        for (const auto& pair : vec) {
            outputFile << pair.first << ';' << pair.second << ';'
                       << ((double)pair.second * 100 / totalWords) << "%" << '\n';
        }
    }

private:
    std::string filename;
};

class Application{
public:
    Application(const std::string& input, const std::string& output): reader(input), writer(output) {}
    void run(){
        auto lines = reader.readLines();
        counter.processLines(lines);
        writer.write(counter.getWordCount(), counter.getTotalWords());
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
