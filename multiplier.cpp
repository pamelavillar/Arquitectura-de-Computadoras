#include <iostream>
#include <bitset>
using namespace std;

bool bitAdder( bool b1,  bool b2, bool& carry) 
{ 
	bool sum = (b1 ^ b2) ^ carry; 
	carry = (b1 && b2) || (b1 && carry) || (b2 && carry); 
	return sum; 
} 
template<size_t N>
bitset<N> adder(bitset<N>& x, bitset<N>& y) 
{ 
	bool carry = false; 
	bitset<N> ans; 
	for (int i = 0; i < N+1; i++) { 
        ans[i] = bitAdder(x[i], y[i], carry); 
	} 
	return ans; 
} 

template<size_t N>
bitset<N> complementoa2(bitset<N> m){
    bitset<N> flipped = ~m;  
    bool carry = true;       
    for (size_t i = 0; i < N; ++i) {
        bool sum = bitAdder(flipped[i], 0, carry);  
        flipped[i] = sum;  
    }
    return flipped;  
}

template<size_t N>
void corrimientoAritmetico(bitset<N>& acc, bitset<N>& q, bitset<1>& qn){
    qn[0]=q[0];
    q>>= 1;
    q[N-1]=acc[0];
    bool aux = acc[N-1];
    acc>>=1;
    acc[N-1]=aux;
}
template<size_t N>
void boothAlgorithm(bitset<N>& m, bitset<N>& q){

    bitset<N>m2;
    bitset<N>acc(0);
    bitset<1>qn(0);
    int counter = N;
    for (int k = 0; k < N; k++){
        
        cout<<"             "<<"acc     "<< "q     " << "qn         "<<endl;
        cout<<"counter "<<counter<<":"<<acc <<" "<<q<<" "<<qn<<endl;

        if ((q[0] ==0 && qn[0] == 0)|| (q[0] ==1 && qn[0] == 1)){
            corrimientoAritmetico(acc, q, qn);
        }
        else if(q[0]==1 && qn[0] == 0){
            m2 = complementoa2(m);
            acc = adder(m2, acc);
            corrimientoAritmetico(acc,q,qn);   
        }
        else if(q[0]==0 && qn[0]== 1){
            acc = adder(m, acc);
            corrimientoAritmetico(acc,q,qn);   
        }
         
        counter--;

    }
    cout<<"\nResult: "<<acc<<q<<endl;
}
int main() 
{ 
    int re=1;
    while(re){
        int n1, n2;
        cout<<"Ingrese el primer numero: "<<endl;
        cin>>n1;
        cout<<"Ingrese el segundo numero: "<<endl;
        cin>>n2;
        
        bitset<4> x(n1);
        bitset<4> y(n2);

        cout<<"\nOperacion ingresada: "<<x<<" * "<<y<<"  ("<<size(x)<<"-bit)"<<endl;

        boothAlgorithm(x,y);

        cout<<"\nDesea realiza otra operacion? Presiona cualquier tecla"<<endl;
        cin>>re;
    }
   
	return 0; 
}
