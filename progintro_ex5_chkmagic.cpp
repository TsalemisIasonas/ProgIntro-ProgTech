#include <iostream>
using namespace std;


string read_matrix(int n){
    int matrix[n][n];
    int sum = 0;
    int num = 0;
    int sums[2*n+2];
    int count = 0;
    string res = "yes";
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            cin>>matrix[i][j];
        }
    }

    int success = 0;
    while (num <n*n){
        for (int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                if (num == matrix[i][j]){
                    success++;
                    break;
                }
            }
        }
        num++;
    }
    if (success!=n*n){
        res = "no";
        return res;
    }

    for (int row=0; row<n; row++){
        for (int col=0; col<n; col++){
            sum+=matrix[row][col];
        }
        sums[count] = sum;
        count++;
        sum = 0;
    }
    
    for (int col=0; col<n; col++){
        for (int row=0; row<n; row++){
            sum+=matrix[row][col];
        }
        sums[count] = sum;
        count++;
        sum = 0;
    }
    

    for (int row=0; row<n; row++){
        for (int col=0; col<n; col++){
            if (row==col){
                sum+=matrix[row][row];
            }
        }
    }
    sums[count] = sum;
    count++;
    sum = 0;

    for (int row=0; row<n; row++){
        for (int col=0; col<n; col++){
            if (row+col == n-1){
                sum+=matrix[row][col];
            }
        }  
    }
    sums[count] = sum;


    for (int i=0; i<count+1; i++){
        if (sums[i]!=sums[0]){
            res = "no";
        }
    }     

    return res;

}

int main(){
    int N;
    string res;
    cin>>N;
    res = read_matrix(N);
    cout << res << endl;
    return 0;
}