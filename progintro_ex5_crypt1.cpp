#include <iostream>
using namespace std;

int output(int encrypted[26]){
  for (int i = 0; i < 26; i++) {
    for (int j=i+1; j<26; j++){
      if (encrypted[i] == encrypted[j]) {
        cout << "error" << endl;
        return 0;
      }  
    }
  }
  int c=0;
  while ((c=getchar()) != EOF){
    if (c>='a' and c<='z'){
      putchar(encrypted[c-'a']);
    }
    else if (c>='A' and c<='Z'){
      putchar(encrypted[c-'A'] -32);
    }
    else {putchar(c);}
  }
}

int main(){
  int encrypted[26];
  int c,i = 0;
  while ((c = getchar()) != '\n') {
    if (c < 'a' or c > 'z' or i>26) {
      break;
    }
    encrypted[i] = c;    
    i++;
  }
  output(encrypted);
  return 0;
}