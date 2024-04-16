#include <iostream>
using namespace std;
#include "multiplier.h"
#include <bitset>

int main(){
    int re = 1;

    while (re){
        FloatingPointMultiplier f;
        cout << "Digite un numero: ";
        float n1;
        cin >> n1;

        cout<<"Digite un segundo numero: ";
        float n2;
        cin >> n2;

        bitset<1> sign1, sign2;
        bitset<8> exponent1, exponent2;
        bitset<23> mantissa1, mantissa2;
        bitset<32> result_of_multiplication;
        float result_of_multiplication_float = 0.0;

        if(n1 == 0 || n2 == 0){
           result_of_multiplication = f.combinarPuntoFlotante(0,0,0);
           result_of_multiplication_float = f.bitsetToFloat(0,0,0);

            cout << "Resultado IEEE-754 Floating Point: " << result_of_multiplication << endl;
            cout << "Resultado float decimal: " << result_of_multiplication_float << endl;
            cout << "Resultado float original: "<< n1*n2 << endl;
            break;
        }

        f.decimalToFloat(n1, sign1, exponent1, mantissa1);
        f.decimalToFloat(n2, sign2, exponent2, mantissa2);

        bitset<1> resultSign = f.sign(sign1, sign2);

        bitset<23> resultMantissa = f.mantissa(mantissa1, mantissa2);

        bitset<8> resultExponent = f.sumExponentsAndCheck(exponent1, exponent2);

        if (resultExponent == std::bitset<8>(0)) {
            cout << "La suma de los exponentes produce overflow o underflow." << endl;
            break;
        }
        else{
            result_of_multiplication = f.combinarPuntoFlotante(resultMantissa, resultExponent, resultSign);
            result_of_multiplication_float = f.bitsetToFloat(resultSign, resultExponent, resultMantissa); 

             cout << "Resultado IEEE-754 Floating Point: " << result_of_multiplication << endl;
             cout << "Resultado float decimal: " << result_of_multiplication_float << endl;
             cout << "Resultado float original: "<< n1*n2 << endl;
        }


        cout<< "presione 0 si no desea calcular otro numero: ";
        cin >>re;
    }


}