#include<iostream>
#include<vector>
#include<cmath>
#include<string>
#include<random>
#include <queue>
#include<thread>
#include <time.h>
#include <bits/stdc++.h>
#include <cassert>

using namespace std;

class Edge{
    public:
        int v;
        int w;
        float weight;

        Edge(int v1, int v2, float edgeweight){
            v = v1;
            w = v2;
            weight = edgeweight;
        }

        Edge(const Edge& t) {
            v = t.v;
            w = t.w;
            weight = t.weight;
        }
};

float rand_num() {
    return (float) ((double) rand() / (double) INT_MAX);
};

// class MinHeap {
//     public:
//         Edge e;
//         MinHeap* c1 = (MinHeap*) malloc(sizeof(MinHeap));
//         MinHeap* c2 = (MinHeap*) malloc(sizeof(MinHeap));
        
//         int size = 1;

//         MinHeap (const Edge & inite) : e(inite) {}

//         void push(Edge arge) {
//             size += 1;
//             if (e.v == -1) {
//                 e.v = arge.v;
//                 e.w = arge.w;
//                 e.weight = arge.weight;
//                 size = 1;
//             }
//             else if (c1->e.weight == 0) {
//                 *c1 = MinHeap(arge);
//                 swap();
//             }
//             else if (c2->e.weight == 0) {
//                 *c2 = MinHeap(arge);
//                 swap();
//             }
//             else {
//                 if (c1->size <= c2->size) {
//                     c1->push(arge);
//                 }
//                 else {
//                     c2->push(arge);
//                 }
//                 swap();
//             }
 
//         }

//         void swap() {
//             if (c1->e.weight != 0 && e.weight > c1->e.weight &&
//                     c2->e.weight != 0 && e.weight > c2->e.weight) {
//                         if (c1->e.weight <= c2->e.weight) {
//                             Edge phe = e;
//                             e = c1->e;
//                             c1->e = phe;
//                             c1->swap();
//                         }
//                         else {
//                             Edge phe = e;
//                             e = c2->e;
//                             c2->e = phe;
//                             c2->swap();
//                         }
//                     }
//             else if (c1->e.weight != 0 && e.weight > c1->e.weight) {
//                 Edge phe = e;
//                 e = c1->e;
//                 c1->e = phe;
//                 c1->swap();
//             }
//             else if (c2->e.weight != 0 && e.weight > c2->e.weight) {
//                 Edge phe = e;
//                 e = c2->e;
//                 c2->e = phe;
//                 c2->swap();
//             }
//         }

//         Edge pop() {
//             Edge phe = e;
//             e.weight = 2.0;
//             e.v = -1;
//             e.w = -1;
//             swap();
//             return phe;
//         }

//         bool empty() {
//             return e.v == -1;
//         }
// };

class MinHeap {
    public:
        Edge e;
        MinHeap* c1 = (MinHeap*) malloc(sizeof(MinHeap));
        MinHeap* c2 = (MinHeap*) malloc(sizeof(MinHeap));
        
        int size = 1;

        MinHeap (const Edge & inite) : e(inite) {}
        // MinHeap (Edge inite) {
        //     Edge e = Edge(inite.v, inite.w, inite.weight);
        //     c1 = nullptr;
        //     c2 = nullptr;
        //     size = 0;
        // }

        void push(Edge arge) {
            size += 1;
            if (e.v == -1) {
                // cout << "inside push0 " << endl;
                e.v = arge.v;
                e.w = arge.w;
                e.weight = arge.weight;
                size = 1;
                // cout << "c1->e.weight" << c1->e.weight << endl;
                c1->e.weight = 2.0;
                // cout << "c2->e.weight" << c2->e.weight << endl;
                c2->e.weight = 2.0;
            }
            else if (c1->e.weight == 2.0) {
                // cout << "inside push1" << endl;
                // cout << "in push 2" << endl;
                *c1 = MinHeap(arge);
                c1->c1->e.weight = 2.0;
                c1->c2->e.weight = 2.0;
                swap();
                
                // c1->e.v = arge.v;
                // c1->e.w = arge.w;
                // c1->e.weight = arge.weight;
            }
            else if (c2->e.weight == 2.0) {
                // cout << "inside push2" << endl;
                // cout << "in push 3" << endl;
                // MinHeap hptr2 = MinHeap(arge);
                // cout << (&hptr2)->e.v << "  , w: " << (&hptr2)->e.w << endl;
                *c2 = MinHeap(arge);
                c2->c1->e.weight = 2.0;
                c2->c2->e.weight = 2.0;
                swap();
                // cout << c2 << endl;
                // cout << c2->e.v << endl;
                // c2->e.v = arge.v;
                // c2->e.w = arge.w;
                // c2->e.weight = arge.weight;
            }
            else {
                // cout << "in push 3" << endl;
                // cout << "in edge of weight: " <<e.weight<<endl;
                if (c1->size <= c2->size) {
                    // cout << "inside if1" << endl;
                    // cout << "c1 inside here weight" << c1->e.weight << endl;
                    c1->push(arge);
                }
                else {
                    // cout << "inside if2" << endl;
                    c2->push(arge);
                }
                swap();
            }
 
        }

        void swap() {
            // cout << "in swap" << endl;
            if (c1->e.weight != 2.0 && e.weight > c1->e.weight &&
                    c2->e.weight != 2.0 && e.weight > c2->e.weight) {
                        // cout << "in swap0" << endl;
                        if (c1->e.weight <= c2->e.weight) {
                            Edge phe = e;
                            e = c1->e;
                            c1->e = phe;
                            c1->swap();
                        }
                        else {
                            Edge phe = e;
                            e = c2->e;
                            c2->e = phe;
                            c2->swap();
                        }
                    }
            else if (c1->e.weight != 2.0 && e.weight > c1->e.weight) {
                // cout << "in swap1" << endl;
                Edge phe = e;
                e = c1->e;
                c1->e = phe;
                c1->swap();
            }
            else if (c2->e.weight != 2.0 && e.weight > c2->e.weight) {
                // cout << "in swap2" << endl;
                // cout << "c2->e.weight" << c2->e.weight << endl;
                // cout << "e.weight" << e.weight << endl;
                Edge phe = e;
                e = c2->e;
                c2->e = phe;
                c2->swap();
            }
        }

        Edge pop() {
            Edge phe = e;
            e.weight = 2.0;
            e.v = -1;
            e.w = -1;
            swap();
            return phe;
        }

        bool empty() {
            return e.v == -1;
        }
};

int main() {
    MinHeap H = MinHeap(Edge(-1, -1, 0.));

    int K = 100;
    for (int i = 0; i < K; i++) {
        float num = rand_num();
        cout << "num: " << num << endl;
        H.push(Edge(2, 5, num));
    }

    for (int i = 0; i < K; i++) {
        cout << "H.pop(): " << H.pop().weight << endl;
    }
    cout << "\n\nis empty? : " << H.empty() << endl;
    // cout << "c1: " << H.c1 << endl;
    // H.push(Edge(10, 9 , 0.2));
    // H.push(Edge(3, 5 , 0.32));
    // H.push(Edge(8, 7 , 0.5));
    // H.push(Edge(3, 5 , 0.123));
    // H.push(Edge(8, 7 , 0.5));
    // H.push(Edge(8, 7 , 0.6));
    // H.push(Edge(6, 12 , 0.4)); 
    // H.push(Edge(3, 5 , 0.32323));
    // H.push(Edge(3, 5 , 0.32323));
    // H.push(Edge(3, 5 , 0.34521));
    // H.push(Edge(3, 5 , 0.345324));
    // H.push(Edge(6, 12 , 0.42351)); 
    // H.push(Edge(1, 2 , 0.1));
    // H.push(Edge(3, 5 , 0.3));
    // H.push(Edge(3, 5 , 0.32));
    // H.push(Edge(3, 5 , 0.34));
    // H.push(Edge(3, 5 , 0.345));
    // H.push(Edge(3, 5 , 0.723));
    // H.push(Edge(3, 5 , 0.123));
    // H.push(Edge(3, 5 , 0.822));
    // H.push(Edge(8, 7 , 0.6));
    // H.push(Edge(3, 5 , 0.295));
    // cout << "H.e.v: " << H.e.weight << ",  H.c1->e.v: " << H.c1->e.weight << ",  H.c2->e.v: " << H.c2->e.weight << "H.c1->c1->e.v: " << H.c1->c1->e.weight << "H.c2->c1->e.weight" << H.c2->c1->e.weight << " size: " << H.size << endl;
    // cout << "H.pop(): " << H.pop().weight << endl;
    // cout << "H.pop(): " << H.pop().weight << endl;
    // cout << "H.pop(): " << H.pop().weight << endl;
    // cout << "H.pop(): " << H.pop().weight << endl;
    // cout << "H.pop(): " << H.pop().weight << endl;
    // cout << "H.pop(): " << H.pop().weight << endl;
    // cout << "H.pop(): " << H.pop().weight << endl;
    // cout << "H.pop(): " << H.pop().weight << endl;
    // cout << "H.pop(): " << H.pop().weight << endl;
    // cout << "H.pop(): " << H.pop().weight << endl;
    // cout << "H.pop(): " << H.pop().weight << endl;
    // cout << "H.pop(): " << H.pop().weight << endl;
    // cout << "H.pop(): " << H.pop().weight << endl;
    // cout << "H.pop(): " << H.pop().weight << endl;
    // cout << "H.pop(): " << H.pop().weight << endl;
    // cout << "H.pop(): " << H.pop().weight << endl;
    // cout << "H.pop(): " << H.pop().weight << endl;
    // cout << "H.pop(): " << H.pop().weight << endl;
    // cout << "H.pop(): " << H.pop().weight << endl;
    // cout << "H.pop(): " << H.pop().weight << endl;
    // cout << "H.pop(): " << H.pop().weight << endl;
    // cout << "\n\nis empty? : " << H.empty() << endl;
    // // Edge e1 = Edge(1, 2, 0.2);
    // Edge e2 = Edge(2, 5, 0.5);
    // Edge ph = e1;
    // e1 = e2;
    // e2 = ph;
    // cout << e2.v << "  w: " << e2.w << "  weight: " << e2.weight << endl;
};

