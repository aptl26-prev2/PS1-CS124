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
};

class EdgeCompareClass {
    public:
        bool operator() (Edge a, Edge b){
        return a.weight > b.weight;
        }
};

float rand_num() {
    return (float) ((double) rand() / (double) INT_MAX);
};

// Generates N vertices sampled uniformly from R^D
vector<vector<float> > generate_vertex(int N, int D){
    vector<vector<float> > V = {};
    // Generate `N` vertices
    for (int i=0; i<N; i++){
        vector<float> Vi = {};
        for (int j=0; j<D; j++)
            Vi.push_back(rand_num());
        V.push_back(Vi);
    }
    return V;
}

// Calculates adjacency matrix for edges [start, end)
void edgethread(vector<vector<Edge> >& E, const vector<vector<float> >& V, int N, int D, float pruneconst, int start, int end){
    for (int i = start; i < end; i++){
        // cout << i << endl;
        for (int j = 0; j < N; j++){
            if (i == j)
                continue;
            // Calculate distance between V[i] and V[j]
            float dist = 0;
            for (int k=0; k<D; k++){
                // Shortcut: immediately ignore this edge if one component is too large
                if (abs(V[i][k] - V[j][k]) > pruneconst){
                    dist = 1;
                    break;
                }
                dist += pow(V[i][k] - V[j][k], 2);
            }
            dist = pow(dist, .5);
            if (dist < pruneconst){
                Edge eij = Edge(i, j, dist);
                E[i].push_back(eij);
            }
        }
    }
}

vector<vector<Edge> > edges_0(int N, float cutoff) {
    vector<vector<Edge> > E;
    for (int i = 0; i < N; i++) {
        E.push_back({});
    }
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            float w = rand_num();
            if (w > cutoff) continue;
            Edge edg1 = Edge(i, j, w);
            E[i].push_back(edg1);
            Edge edg2 = Edge(j, i, w);
            E[j].push_back(edg2);
        }
    }
    return E;
}

// Given N vertices sampled uniformly from R^D
// Returns in adjacency-list form: E[i] contains the vector of indices i is connected to
// Prunes all edges of length larger than pruneconst
vector<vector<Edge> > edgefromvertex(const vector<vector<float> >& V, int N, int D, float pruneconst){
    vector<vector<Edge> > E;
    for (int i = 0; i < N; i++)
        E.push_back({});
    
    // Naive implementation without concurrency: edgethread(E, V, N, D, pruneconst, blocklength*i, blocklengthx*(i+1))));

    // Split the workload into `nthreads` blocks
    vector<std::thread> threads;
    int nthreads = max(1, min((int) thread::hardware_concurrency(), (int) (N / 500)));
    int blocklength = N / nthreads;
    for (int i=0; i<nthreads - 1; i++)
        threads.push_back(thread(edgethread, ref(E), ref(V), N, D, pruneconst, blocklength*i, blocklength*(i+1)));
    threads.push_back(thread(edgethread, ref(E), ref(V), N, D, pruneconst, blocklength*(nthreads-1), N));
    for (auto& t : threads)
        t.join();
    return E;
}

// Returns weight of minimum spanning tree, returns -1 upon failure
float prim(vector<vector<Edge> > E, int N){
    priority_queue<Edge, vector<Edge>, EdgeCompareClass> Q;
    vector<Edge> mst;
    bool spanned[N]; // whether index i is connected to MST
    // Initialization: we start with v0
    for (int i=0; i<N; i++)
        spanned[i] = false;
    spanned[0] = true;

    for (auto& e : E[0]) // for e in E[0]
        Q.push(e);

    for (int i=0; i<N-1; i++){
        bool init = true;
        auto minE = Edge(-1, -1, -1.);
        // Select a minimum-weight edge from current cut. Remove those which are not in cut
        while (init || (spanned[minE.v] && spanned[minE.w])){
            // if (!init)
                // cout << "        Ignoring: " << minE.v << " <-> " << minE.w << " : " << minE.weight << endl;
            if (Q.empty()) // Returns -1 if Q is empty (ran out of edges, which indicates failure)
                return -1;
            minE = Q.top();
            Q.pop();
            init = false;
        }
        // cout << i << "    Selected from candidates: " << minE.v << " <-> " << minE.w << " : " << minE.weight << endl;
        int newv = spanned[minE.w] ? minE.v : minE.w;
        // insert newv into spanned vertices
        spanned[newv] = true;
        mst.push_back(minE);
        // Insert new edges into current cut
        for (auto &e : E[newv])
            if (!(spanned[e.w] && spanned[e.v])){
                // cout << "        Added to MST candidates: " << e.v << " <-> " << e.w << " : " << e.weight << endl;
                Q.push(e);
            }
    }
    float mstweight = 0;
    for (auto& e : mst)
        mstweight += e.weight;
    return mstweight;
}

// Generates ONE graph of N vertices from [0, 1]^D. Returns weight of MST on the graph
float run_trial(int N, int D){
    auto V = generate_vertex(N, D);

    // sqrt(D/N) is just a heuristic function. We start at this value and increment cutoff upon failure
    float cutoff = pow((float) D, .5) * pow(N, -1. / D) / 2, mstweight = 0;
    // cout << "Vertex generated " << cutoff << " " << pow(N, -1. / D) << endl;
    bool rerun = true;
    while (rerun) {
        auto E = edgefromvertex(V, N, D, cutoff);
        // cout << "Edges generated @ cutoff " << cutoff << endl;
        mstweight = prim(E, N);
        if (mstweight == -1){
            cutoff += pow((float) D, .5) * pow(N, -1. / D) / 2; // Regenerate graph and run again
            // cout << "MST compute failure" << endl;
        }
        else
            rerun = false;
    }
    // cout << "MST weight:" << mstweight << " successful calculation @ cutoff: " << cutoff << endl;
    return mstweight;
}

float run_trial_0 (int N) {
    cout << "N" << N << endl;
    float cutoff = 100.0 / (float) N;
    cout << "cutoff: " << cutoff << endl;
    float mstweight = 0;

    bool rerun = true;
    while (rerun) {
        auto E = edges_0(N, cutoff);
        // cout << "Edges generated @ cutoff " << cutoff << endl;
        mstweight = prim(E, N);
        if (mstweight == -1){
            cutoff *= 2; // Regenerate graph and run again
            // cout << "MST compute failure" << endl;
            cout << "increased cutoff" << endl;
        }
        else
            rerun = false;
    }
    // cout << "MST weight:" << mstweight << " successful calculation @ cutoff: " << cutoff << endl;
    return mstweight;
}

int main(int argc, char** argv)
{
    srand(time(0));
    // Parse arguments
    int N = stoi(string(argv[1])), K = stoi(string(argv[2])), D = stoi(string(argv[3]));
    float mstweight = 0;
    for (int i = 0; i < K; i++)
        mstweight += (D == 0) ?  run_trial_0(N) : run_trial(N, D);
    mstweight /= K;
    // average, numpoints, numtrials, dimension
    cout << mstweight << " " << N << " " << K << " " << D << endl;
    return 0;
}