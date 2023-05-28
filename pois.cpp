#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

class Point {
public:
    int x;
    int y;
    string category;
};

double calculateDistance(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    int N;
    cin >> N;

    vector<Point> pointsOfInterest(N);
    for (int i = 0; i < N; ++i) {
        cin >> pointsOfInterest[i].x >> pointsOfInterest[i].y;
        cin.ignore(); // Ignore the newline character
        getline(cin, pointsOfInterest[i].category);
    }

    int K;
    cin >> K;

    vector<Point> track(K);
    for (int i = 0; i < K; ++i) {
        cin >> track[i].x >> track[i].y;
    }

    // Calculate the nearest point of interest for each category on the track
    for (const Point& trackPoint : track) {
        vector<string> categories;
        vector<double> distances;

        for (const Point& poi : pointsOfInterest) {
            if (find(categories.begin(), categories.end(), poi.category) == categories.end()) {
                categories.push_back(poi.category);
                distances.push_back(calculateDistance(trackPoint.x, trackPoint.y, poi.x, poi.y));
            } else {
                int index = find(categories.begin(), categories.end(), poi.category) - categories.begin();
                double distance = calculateDistance(trackPoint.x, trackPoint.y, poi.x, poi.y);
                if (distance < distances[index]) {
                    distances[index] = distance;
                }
            }
        }

        // Display the results
        cout << trackPoint.x << " " << trackPoint.y << "\n";
        for (size_t i = 0; i < categories.size(); ++i) {
            cout << categories[i] << " ";
            cout << fixed << setprecision(3) << distances[i] << "\n";
        }
        cout << endl;
    }

    return 0;
}
