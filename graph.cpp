#include <iostream>
#include <cstdlib>

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
// Edge *g_rand_helper(int n) {
//     Edge edges[n * n];
//     int k = 0;
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             Edge e;
//             e.v1 = i;
//             e.v2 = j;
//             e.weight = rand_num();
//             edges[i * n + j] = e;
//         };
//     };

//     return edges
// };

int main() {
    // Edge *p = g_rand_helper(10);
    // for (int i = 0; i < 10; i++) {
    //     cout << i << ":  ";
    //     cout << *(p + i) << endl;
    // }
    int n = 10;
    
    Edge edges[n * n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Edge e;
            e.v1 = i;
            e.v2 = j;
            e.weight = rand_num();
            edges[i * n + j] = e;
        };
    };
    for (int i = 0; i < n * n; i++) {
        cout << "v1: " << (*(edges + i)).v1 << ", v2: " << (*(edges + i)).v2 <<
          ", weight: " << (*(edges + i)).weight << endl;
    }
    return 0;
}