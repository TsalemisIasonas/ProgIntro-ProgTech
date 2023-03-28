#include <iostream>
#include <iomanip>
using namespace std;

// TODO GET THE PERCENTAGE floating points

string checker(string input) {
  int len = input.length();

  if (len == 0)
    return "empty";

  if (len > 20)
    return "error";

  for (int i = 0; i < len / 2; i++) {
    if (input[i] != input[len - i - 1]) {
      return "no";
    }
  }

  return "yes";
}

void collector(int n) {
  string matrix[n], results[n], str;
  int i;
  float count=0;
  float percentage;
  for (i = 0; i < n; i++) {
    getline(cin,str);
    matrix[i] = str;
  }
  for (i = 0; i < n; i++) {
    str = checker(matrix[i]);
    results[i] = str;
  }
  for (int i = 0; i < n; i++) {
    cout << results[i] << endl;
    if (results[i] == "yes") {
      count += 1;
    }
  }
  percentage = (count*100)/n;
  cout << fixed;
  cout <<setprecision(3) << percentage << endl;
}

int main() {
  int n;
  //cout << "NoStrs" << endl;
  cin >> n;
  cin.ignore();
  collector(n);
}