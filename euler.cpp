#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;

bool hasEulerianPathOrCycle(unordered_map<int, vector<int>>& graph, int N) {
    unordered_map<int, int> inDegrees;
    unordered_map<int, int> outDegrees;

    for (auto& it : graph) {
        int u = it.first;
        for (int v : it.second) {
            outDegrees[u]++;
            inDegrees[v]++;
        }
    }

    int startVertex = -1;
    int oddDegreeCount = 0;

    for (int v = 0; v < N; v++) {
        if (outDegrees[v] - inDegrees[v] == 1) {
            if (startVertex != -1)
                return false;
            startVertex = v;
        }
        else if (outDegrees[v] - inDegrees[v] > 1 || inDegrees[v] - outDegrees[v] > 1)
            return false;
        else if (inDegrees[v] - outDegrees[v] == 1)
            oddDegreeCount++;
    }

    if (oddDegreeCount != 0 && oddDegreeCount != 2)
        return false;

    if (startVertex == -1)
        startVertex = 0;

    stack<int> st;
    vector<int> path;

    st.push(startVertex);

    while (!st.empty()) {
        int u = st.top();

        if (outDegrees[u] == 0) {
            path.push_back(u);
            st.pop();
        }
        else {
            int v = graph[u].back();
            outDegrees[u]--;
            graph[u].pop_back();
            st.push(v);
        }
    }

    return path.size() == N + 1;
}

int main() {
    int N, M;
    cin >> N >> M;

    unordered_map<int, vector<int>> graph;

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    if (hasEulerianPathOrCycle(graph, N))
        cout << "CYCLE" << endl;
    else
        cout << "IMPOSSIBLE" << endl;

    return 0;
}
