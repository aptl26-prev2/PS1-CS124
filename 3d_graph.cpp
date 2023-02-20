#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

class Edge {
    public:
        int v1;
        int v2;
        float weight; 
};

float rand_num() {
    return static_cast< float >(rand() % 100) / 100.0;
};

int main() {
    int n = 10;
    
    Edge edges[n * n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Edge e;
            e.v1 = i;
            e.v2 = j;
            float x1 = rand_num();
            float y1 = rand_num();
            float z1 = rand_num();
            float x2 = rand_num();
            float y2 = rand_num();
            float z2 = rand_num();
            e.weight = sqrt(pow(x1 - x2, 2) + pow(y1 - y1, 2) + pow(z1 - z2, 2));
            edges[i * n + j] = e;
        };
    };
    for (int i = 0; i < n * n; i++) {
        cout << "v1: " << (*(edges + i)).v1 << ", v2: " << (*(edges + i)).v2 <<
          ", weight: " << (*(edges + i)).weight << endl;
    }
    return 0;
}