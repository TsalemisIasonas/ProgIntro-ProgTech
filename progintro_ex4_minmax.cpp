#include <iostream>
using namespace std;

void read_matrix(int N, int M){
  int matrix[N][M]; 
  int i,j,temp = 0;
  int col_maxs[M];
  int row_mins[N];
  
  for (i=0;i<N; i++){
    for (j=0; j<M; j++){
      cin >> matrix[i][j];
    }   
  }
  
// --------- FIND MIN OF COL MAXS -----------------------------------//

  for (j=0;j<M; j++){
    temp = matrix[0][j];
    for (i=0; i<N; i++){
      if (temp < matrix[i][j]){
        temp = matrix[i][j];
      } 
    }
  col_maxs[j] = temp;
  }
  temp = col_maxs[0];
  for (i=0;i<M;i++){
    if (col_maxs[i] < temp){
      temp = col_maxs[i];
    }
  }
  cout << temp << endl;

// --------- FIND MAX OF ROW MINS ----------------------------------//  
  
  for (i=0;i<N; i++){
    temp = matrix[i][0];
    for (j=0; j<M; j++){
      if (temp > matrix[i][j]){
        temp = matrix[i][j];
      } 
    }
    row_mins[i] = temp;
  }
  temp = row_mins[0];
  for (i=0;i<N;i++){
    if (temp<row_mins[i]){
      temp = row_mins[i];
    }
  }
  cout << temp << endl;
// --------- FIND MAX OF ROW MINS ----------------------------------//
  

}

int main() {
  int n,m;
  //cout << "Enter Dimensions" << endl;
  cin >> n; cin >> m;
  read_matrix(n, m);
}