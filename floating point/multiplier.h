#ifndef MULTIPLIER_H
#define MULTIPLIER_H
#include <bitset>
#include <cstdint>
using namespace std;

class FloatingPointMultiplier {
public:
    FloatingPointMultiplier();

    void decimalToFloat(float num, std::bitset<1> &sign, std::bitset<8> &exponent, std::bitset<23> &mantissa);
    bitset<8> sumExponentsAndCheck(const std::bitset<8> &exponent1, const std::bitset<8> &exponent2);

    bitset<23> mantissa(const std::bitset<23>& mantissa1, const std::bitset<23>& mantissa2);

    bitset<1> sign(const std::bitset<1>& sign1, const std::bitset<1>& sign2);

    bitset<32> combinarPuntoFlotante(std::bitset<23> mantissa, std::bitset<8> exponent, std::bitset<1> sign);
    float bitsetToFloat(std::bitset<1> sign, std::bitset<8> exponent, std::bitset<23> mantissa);
    
};

#endif 
