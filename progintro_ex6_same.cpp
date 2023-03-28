#include <iostream>
using namespace std;
void compare(int n){
    int A[n],B[n];
    int i=0;
    int max,min = A[0];
    bool dif = false;

    for (int i=0;i<n;i++){
        cin >> A[i];
    }

    for (int i=0;i<n;i++){
        cin >> B[i];
    }

    while (i<n){
        if (A[i]!=B[i]){
            if (A[i]<B[i] && A[i]<min){
                min = A[i];
            }
            else if (A[i]>B[i]&& B[i]<min){
                min = B[i];
            }

            if (A[i]<B[i] && B[i]>max){
                max = B[i];
            }
            else if (A[i]>B[i]&& A[i]>max){
                max = A[i];
            }
            dif = true;
        }
        i++;
    }
    if (dif){
        cout << "no" << ' ' << min << ' ' << max;
    }
    else {
        cout << "yes";
    }
    // for (int i=0;i<n;i++){
    //     for (int j=0;j<n;j++){
    //         if (A[i] != B[j]) continue;
    //         else found = true;
    //     }
    //     if (found == false){
    //         min = A[0];
    //         while (i<n){

    //         }
    //         cout << "no " << min << ' '<< max << endl;
    //         break;
    //     }
    // }

    // if (found){
    //     cout << "yes" << endl;
    // }
}
int main(){
    int N;
    cin >> N;
    compare(N);
}