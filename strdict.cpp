#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    int N, D;
    cin >> N >> D;

    map<int, set<string>> dictionaries;

    for (int i = 0; i < N; ++i) {
        int d;
        string word;
        cin >> d >> word;
        dictionaries[d].insert(word);
    }

    int largestDictionarySize = 0;
    int largestDictionaryNumber = 0;

    for (const auto& entry : dictionaries) {
        int dictionaryNumber = entry.first;
        const set<string>& words = entry.second;

        if (words.size() > largestDictionarySize) {
            largestDictionarySize = words.size();
            largestDictionaryNumber = dictionaryNumber;
        }
    }

    cout << largestDictionaryNumber << " " << largestDictionarySize << "\n";

    set<string> commonWords = dictionaries[1];
    for (int i = 2; i <= D; ++i) {
        set<string> currentDictionary = dictionaries[i];
        set<string> intersection;

        set_intersection(
            commonWords.begin(), commonWords.end(),
            currentDictionary.begin(), currentDictionary.end(),
            inserter(intersection, intersection.begin())
        );

        commonWords = intersection;
    }

    int numCommonWords = commonWords.size();
    for (const string& word : commonWords) {
        cout << word << "\n";
    }

    cout << numCommonWords << "\n";

    return 0;
}
