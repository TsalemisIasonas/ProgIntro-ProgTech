#include <iostream>
using namespace std;

int ex1(){
    int N,i;
    int digit;
    cin>>N;
    for (i=0; i<2; i++){
        digit = N%10; // get last digit
        N /= 10;    // divide by ten, so last digit is dropped
    }
    cout << digit;
    return 0;
}

// TODO Run this in Putty in cpp to see if it accepts it

int ex2(){      // ???
    int N;
    int i = 1;
    int factorial = 1;
    cin >> N;
    while (factorial<N){
        i++;
        factorial *=i;       
    }
    cout << i - 1<< endl;
    return 0;
}

int main(){
    ex2();
}