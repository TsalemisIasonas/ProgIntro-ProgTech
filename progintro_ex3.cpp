#include <iostream>
using namespace std;

void output(int a , int p){
    int gcd, temp_a, temp_p;
    if ((a>0 and p<0) or (a<0 and p>0)) cout << '-';
    temp_a = abs(a); temp_p = abs(p);
    while (temp_a > 0 and temp_p > 0)
        if (temp_a > temp_p) temp_a = temp_a % temp_p; 
        else temp_p = temp_p % temp_a;
    gcd = temp_a + temp_p;
    a = abs(a)/gcd; p = abs(p)/gcd;
    cout << a / p << " " << a % p << " " << p << endl;

}

void addition(int a1, int p1, int a2, int p2){
    output((a1 * p2 + a2 * p1), p1 * p2);
}

void subtraction(int a1, int p1, int a2, int p2){
    output((a1 * p2 - a2 * p1), p1 * p2);
}

void multiplication(int a1, int p1, int a2, int p2){
    output(a1 * a2, p1 * p2);
}

void division(int a1, int p1, int a2, int p2){
    if (a2==0) cout << "error" << endl;
    else {
        output(a1 * p2, a2 * p1);
    }
}

int main(){
    int N,a1,a2,p1,p2;
    int i;
    char op;
    cin>>N;
    for (i=0; i<N; i++){
        cin>>op;
        cin>>a1; cin >> p1; cin >> a2; cin >> p2;
        if (p1==0 or p2==0) cout << "error" << endl;
        else if (a1 == 0) cout << "0 0 1" << endl;
        else{
            switch(op){
                case '+': 
                    addition(a1, p1, a2, p2);
                    break;
                case '-': 
                    subtraction(a1, p1, a2, p2);
                    break;
                case '*': 
                    multiplication(a1, p1, a2, p2);
                    break;
                case '/': 
                    division(a1, p1, a2, p2);
                    break;
            }
        }
    }
    return 0;
}