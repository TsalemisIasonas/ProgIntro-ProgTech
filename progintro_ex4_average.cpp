#include <iostream>
#include <iomanip>
using namespace std;

void read_matrix(int N, int M){
  float matrix[N][M]; 
  int i,j;
  float temp_avg, total = 0;
  float average = 0;
  float col_avgs[M];
  float row_avgs[N];
  
  for (i=0;i<N; i++){
    for (j=0; j<M; j++){
      cin >> matrix[i][j];
    }   
  }

// --------- ROWS ----------------------------------//  
  
  for (i=0;i<N; i++){
    total = 0;
    temp_avg = 0;
    for (j=0; j<M; j++){
      total+=matrix[i][j];
      } 
    temp_avg = (total)/M;
    row_avgs[i] = temp_avg;
    }
    temp_avg = 0;
    for (i=0;i<N;i++){
        temp_avg+=row_avgs[i];
    }
    average = (temp_avg)/N;
    cout << fixed;
    cout << setprecision(3) << average << endl;

// --------- COLS ----------------------------------//  
  for (j=0;j<M; j++){
    total = 0;
    temp_avg = 0;
    for (i=0; i<N; i++){
      total+=matrix[i][j];
      } 
    temp_avg = (total)/N;
    row_avgs[j] = temp_avg;
    }
    temp_avg = 0;
    for (i=0;i<M;i++){
        temp_avg+=row_avgs[i];
    }
    average = (temp_avg)/M;
    cout << fixed;
    cout << setprecision(3) << average << endl;
    

}

int main() {
  int n,m;
  //cout << "Enter Dimensions" << endl;
  cin >> n; cin >> m;
  read_matrix(n, m);
}