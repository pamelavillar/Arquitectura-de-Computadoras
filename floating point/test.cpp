#include <iostream>
#include <bitset>
#include <string>
using namespace std;
int main() {

    string entero = "";
    string decimal = "";

    int pos = 0;
    string result = "";

    if( entero == "0"){
        for(int i = 0; i < decimal.length(); i++){
            if (entero[i] == '1')
                pos = i+1;
                break;
        }
        for(int i = pos; i < decimal.length(); i++){
            result += decimal[i];
        }
    }
    else{
        pos = entero.length();
         for(int i = 0; i < pos; i++){
            result += entero[i];
        }
        result +=decimal;
    }
}
