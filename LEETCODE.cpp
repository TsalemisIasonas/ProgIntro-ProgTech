#include <string>
#include <vector>
#include <iostream>
using namespace std;

string longestCommonPrefix(vector<string> &strs)
{
    int prefixLen = 0;
    for (int i = 0; i < min((strs[0]).length(),(strs[1]).length()); i++)
    {
            if ((strs[0])[i] == (strs[1])[i])
            {
                prefixLen++;
            }
            else{ break;}
    }
    cout << prefixLen << endl;
    for (int i = 0; i< strs.size(); i++){
        for (int j = 0; j< prefixLen; j++){
            if (strs[i][j] != strs[0][j]){
                prefixLen = prefixLen-j;
                break;
            }
        }
    }
    cout << prefixLen << endl;
    string prefix = "";
    for (int i = 0; i < prefixLen; i++)
    {
        prefix += (strs[0])[i];
    }
    return prefixLen > 0 ? prefix : "";
}

int main(){
    vector<string> strs = {"flower","flow","flight"};
    cout << longestCommonPrefix(strs);
}