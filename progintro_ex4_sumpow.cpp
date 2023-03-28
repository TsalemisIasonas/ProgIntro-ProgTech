#include <iostream>
#include<math.h>
using namespace std;

int get_sum(int power, int num){
    int temp = 0;
    int sum = 0;
    while(num!=0){
        temp = pow((num%10),power);
        sum+=temp;
        num /= 10;
    }
    return sum;
}
void presenter(int numbers[],int n, int length){
    for (int i=0; i<length;i++){
        cout << numbers[i] << endl;
    }
}




int main(){
    int n;
    cin >> n;
    int numbers = pow(10,n+1);
    int digits[numbers];
    for (int i=0;i<numbers;i++){
        digits[i] = i;
    }
    
    presenter(digits,n,numbers);
    return 0;
}