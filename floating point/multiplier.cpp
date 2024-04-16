#include <iostream>
using namespace std;
#include "multiplier.h"
#include <bitset>
#include <string>

bool bitAdder( bool b1,  bool b2, bool& carry) 
{ 
	bool sum = (b1 ^ b2) ^ carry; 
	carry = (b1 && b2) || (b1 && carry) || (b2 && carry); 
	return sum; 
} 
bitset<23> adder(bitset<23>& x, bitset<23>& y) 
{ 
	bool carry = false; 
	bitset<23> ans; 
	for (int i = 0; i < 23; i++) { 
        ans[i] = bitAdder(x[i], y[i], carry); 
	} 
	return ans; 
} 

bitset<23> roundedBinary(bitset<48>& binary) {
    bitset<23> roundedBinary;
    
    bool truncateBit = binary[24];

    for (int i = 47 , j = 22; i >= 25 , j>=0 ; i-- , j--) {
            roundedBinary[j] = binary[i];
        }

    if (truncateBit == 1) {
        bitset<23> bit(0);
        bit.set(0,1);

        roundedBinary = adder(roundedBinary, bit);
    } 
    return roundedBinary;
}





FloatingPointMultiplier::FloatingPointMultiplier(){}

int counter = 0;

void FloatingPointMultiplier::decimalToFloat(float num, std::bitset<1> &sign, std::bitset<8> &exponent, std::bitset<23> &mantissa) {
  // Union para acceder a la representación binaria del float
  union {
    float f;
    int i;
  } converter;

  converter.f = num;

  // Obtener el signo
  sign[0] = converter.i >> 31 & 1;

  // Obtener el exponente
  exponent = (converter.i >> 23) & 0xFF;

  // Obtener la mantisa
  mantissa = converter.i & 0x7FFFFF;
}


bitset<8> FloatingPointMultiplier::sumExponentsAndCheck(const std::bitset<8> &exponent1, const std::bitset<8> &exponent2) {

    int exp1 = static_cast<int>(exponent1.to_ulong());
    int exp2 = static_cast<int>(exponent2.to_ulong());

    int sumExponents = exp1 + exp2 - 127;
    int sum = (exp1-127) + (exp2 - 127)+ (128-counter); 

    bool overflow = (sumExponents > 255) || (sumExponents < -126);
    bool underflow = (sumExponents < -127);

    if (overflow) {
        cout << "Se ha producido overflow." << endl;
        return bitset<8>(0); 
    } else if (underflow) {
        cout << "Se ha producido underflow." << endl;
        return bitset<8>(0); 
    } else {
        return bitset<8>(sum);
    }


}




bitset<23> FloatingPointMultiplier::mantissa(const std::bitset<23>& mantissa1, const std::bitset<23>& mantissa2){
    
    bitset<24> bitset1(mantissa1.to_string()); 
    bitset1.set(23, 1);

    bitset<24> bitset2(mantissa2.to_string()); 
    bitset2.set(23, 1);
    
    unsigned long long decimal1 = bitset1.to_ullong();
    unsigned long long decimal2 = bitset2.to_ullong();
    unsigned long long resultDecimal = decimal1 * decimal2;

    string resultBinaryString = bitset<48>(resultDecimal).to_string();

    bitset<48> resultBitset(resultBinaryString);

    
    for (int i = 47 ; i >= 0 ; i--){
        if (resultBitset[i]==0){
           counter++;
        }
        else{
            break;
        }
    }


    resultBitset<<=(1+counter);

    return roundedBinary(resultBitset);
    
}

bitset<1> FloatingPointMultiplier::sign(const std::bitset<1>& sign1, const std::bitset<1>& sign2){
    return sign1 ^ sign2;
  }

bitset<32> FloatingPointMultiplier::combinarPuntoFlotante(std::bitset<23> mantissa, std::bitset<8> exponent, std::bitset<1> sign) {
    bitset<32> resultado; 

    resultado[31] = sign[0];

    for (int i = 0; i < 8; ++i) {
        resultado[30 - i] = exponent[7 - i];
    }

    for (int i = 0; i < 23; ++i) {
        resultado[22 - i] = mantissa[22 - i];
    }

    return resultado;
}


float FloatingPointMultiplier::bitsetToFloat(std::bitset<1> sign, std::bitset<8> exponent, std::bitset<23> mantissa) {
    union {
        float f;
        int i;
    } converter;

    converter.i = (sign[0] << 31);

    converter.i |= (exponent.to_ulong() << 23);

    converter.i |= mantissa.to_ulong();

    return converter.f;
}