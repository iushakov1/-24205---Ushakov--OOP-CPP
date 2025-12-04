#ifndef TASK_2_RULE_H
#define TASK_2_RULE_H

#include <cstdint>
#include <string>

class Rule {
public:
    Rule() = default;
    explicit Rule(const std::string& rule);
    void loadRule(const std::string& rule);
    uint8_t decide(int n, uint8_t cellStatus) const noexcept;
    std::string getRule() const noexcept;
private:
    uint16_t GetBirthMask()   const noexcept {return birthMask;}
    uint16_t GetSurviveMask() const noexcept {return surviveMask;}
    int digit_0_8(char c);
    uint16_t birthMask = 0;
    uint16_t surviveMask = 0;
};

#endif
