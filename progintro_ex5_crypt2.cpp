#include <iostream>
#include <cctype>
using namespace std;

int output(int encrypted[26], char selection){
  for (int i = 0; i < 26; i++) {
    if (encrypted[i]<65){
        cout << "error" << endl;
        return 0;
    }
    for (int j=i+1; j<26; j++){
      if (encrypted[i] == encrypted[j]) {
        cout << "error" << endl;
        return 0;
      }  
    }
  }
  
  int c=0;
  int i=0;
  if (selection=='d'){
    while ((c=getchar()) != EOF){
      if (c>='a' and c<='z'){
        for(i=0;i<26;i++){
          if (encrypted[i]==c){
            break;
          }
        }
        putchar('a'+i);
      }
      else if (c>='A' and c<='Z'){
        for(i=0;i<26;i++){
          if (encrypted[i]== tolower(c)){
            break;
          }
        }
        putchar('A'+i);
      }
      else {putchar(c);}
    }
  }
  else{
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
}

int main(){
  int encrypted[26];
  char selection[30];
  int c,i = 0;
  while ((c = getchar()) != '\n') {
    if (c < 'a' or c > 'z' or i>26) {
      break;
    }
    encrypted[i] = c;    
    i++;
  }
  i=0;
  while((c=getchar()) != '\n'){
    selection[i] = c;
    i++;
    }
  output(encrypted,selection[0]);
  return 0;
}