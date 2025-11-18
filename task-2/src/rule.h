#ifndef TASK_2_RULE_H
#define TASK_2_RULE_H

#include <cstdint>
#include <string>

class Rule {
public:
    Rule() = default;
    explicit Rule(const std::string& rule);
    void loadRule(const std::string& rule);
    [[nodiscard]] uint8_t decide(int n, uint8_t alive) const noexcept;
    [[nodiscard]] std::string getRule() const noexcept;
    [[nodiscard]] uint16_t GetBirthMask()   const noexcept {return birthMask;}
    [[nodiscard]] uint16_t GetSurviveMask() const noexcept {return surviveMask;}

private:
    uint16_t birthMask = 0;
    uint16_t surviveMask = 0;
};

#endif
