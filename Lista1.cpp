#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

long long COMP = 0;    
long long ASSIGN = 0;  

inline void resetCounters() { COMP = 0; ASSIGN = 0; }

void printArray(const vector<int>& a) {
    for (int x : a) cout << x << " ";
    cout << "\n";
}
inline void countedSwap(vector<int>& a, int i, int j) {
    int tmp = a[i];           
    a[i] = a[j]; ASSIGN++;      
    a[j] = tmp;  ASSIGN++;     
}


void insertionSort(vector<int>& a) {
    int n = (int)a.size();
    for (int i = 1; i < n; ++i) {
        int key = a[i]; 
        int j = i - 1;
        while (j >= 0) {
            COMP++; 
            if (!(a[j] > key)) break;
            a[j + 1] = a[j]; ASSIGN++;
            --j;
        }
        a[j + 1] = key; ASSIGN++;
    }
}


void doubleInsertionSort(vector<int>& a) {
    int n = (int)a.size();
    for (int i = 2; i <= n; i += 2) {
        int x = a[i - 2], y = a[i - 1];
        
        COMP++;
        if (x > y) { int t = x; x = y; y = t; }

       
        int j = i - 3;
        while (j >= 0) {
            COMP++;                 
            if (!(a[j] > x)) break;
            a[j + 1] = a[j]; ASSIGN++;
            --j;
        }
        a[j + 1] = x; ASSIGN++;

        
        int k = i - 2;
        while (k >= 0) {
            COMP++;                
            if (!(a[k] > y)) break;
            a[k + 1] = a[k]; ASSIGN++;
            --k;
        }
        a[k + 1] = y; ASSIGN++;
    }

    
    if (n % 2 == 1) {
        int key = a[n - 1];
        int j = n - 2;
        while (j >= 0) {
            COMP++;               
            if (!(a[j] > key)) break;
            a[j + 1] = a[j]; ASSIGN++;
            --j;
        }
        a[j + 1] = key; ASSIGN++;
    }
}


void merge2(vector<int>& a, int L, int M, int R) {
    int n1 = M - L + 1, n2 = R - M;
    vector<int> Lbuf(n1), Rbuf(n2);

   
    for (int i = 0; i < n1; ++i) { Lbuf[i] = a[L + i]; ASSIGN++; }
    for (int j = 0; j < n2; ++j) { Rbuf[j] = a[M + 1 + j]; ASSIGN++; }

    int i = 0, j = 0, k = L;
    while (i < n1 && j < n2) {
        COMP++; 
        if (Lbuf[i] <= Rbuf[j]) { a[k++] = Lbuf[i++]; ASSIGN++; }
        else { a[k++] = Rbuf[j++]; ASSIGN++; }
    }
    while (i < n1) { a[k++] = Lbuf[i++]; ASSIGN++; }
    while (j < n2) { a[k++] = Rbuf[j++]; ASSIGN++; }
}

void mergeSort2(vector<int>& a, int L, int R) {
    if (L >= R) return;
    int M = L + (R - L) / 2;
    mergeSort2(a, L, M);
    mergeSort2(a, M + 1, R);
    merge2(a, L, M, R);
}


void merge3(vector<int>& a, int L, int M1, int M2, int R) {
    int nA = M1 - L + 1;
    int nB = M2 - M1;
    int nC = R - M2;
    vector<int> A(nA), B(nB), C(nC);

    for (int i = 0; i < nA; ++i) { A[i] = a[L + i]; ASSIGN++; }
    for (int j = 0; j < nB; ++j) { B[j] = a[M1 + 1 + j]; ASSIGN++; }
    for (int k = 0; k < nC; ++k) { C[k] = a[M2 + 1 + k]; ASSIGN++; }

    int i = 0, j = 0, k = 0, t = L;

    while (i < nA && j < nB && k < nC) {
        COMP++; bool Ai_le_Bj = (A[i] <= B[j]);
        int vMinAB = Ai_le_Bj ? A[i] : B[j];
        COMP++;
        if (vMinAB <= C[k]) {
            if (Ai_le_Bj) { a[t++] = A[i++]; ASSIGN++; }
            else { a[t++] = B[j++]; ASSIGN++; }
        }
        else { a[t++] = C[k++]; ASSIGN++; }
    }

    while (i < nA && j < nB) { COMP++; if (A[i] <= B[j]) { a[t++] = A[i++]; ASSIGN++; } else { a[t++] = B[j++]; ASSIGN++; } }
    while (i < nA && k < nC) { COMP++; if (A[i] <= C[k]) { a[t++] = A[i++]; ASSIGN++; } else { a[t++] = C[k++]; ASSIGN++; } }
    while (j < nB && k < nC) { COMP++; if (B[j] <= C[k]) { a[t++] = B[j++]; ASSIGN++; } else { a[t++] = C[k++]; ASSIGN++; } }

    while (i < nA) { a[t++] = A[i++]; ASSIGN++; }
    while (j < nB) { a[t++] = B[j++]; ASSIGN++; }
    while (k < nC) { a[t++] = C[k++]; ASSIGN++; }
}

void mergeSort3(vector<int>& a, int L, int R) {
    if (L >= R) return;
    int len = R - L + 1;
    int third = len / 3;
    if (third == 0) { 
        int M = L + (R - L) / 2;
        mergeSort2(a, L, M);
        mergeSort2(a, M + 1, R);
        merge2(a, L, M, R);
        return;
    }
    int M1 = L + third - 1;
    int M2 = M1 + third;
    if (M2 >= R) M2 = L + (R - L) / 2; 

    mergeSort3(a, L, M1);
    mergeSort3(a, M1 + 1, M2);
    mergeSort3(a, M2 + 1, R);
    merge3(a, L, M1, M2, R);
}


void heapifyBinary(vector<int>& a, int n, int i) {
    while (true) {
        int largest = i;
        int l = 2 * i + 1, r = 2 * i + 2;

        if (l < n) { COMP++; if (a[l] > a[largest]) largest = l; }
        if (r < n) { COMP++; if (a[r] > a[largest]) largest = r; }

        if (largest == i) break;
        countedSwap(a, i, largest); 
        i = largest;
    }
}
void heapSortBinary(vector<int>& a) {
    int n = (int)a.size();
    for (int i = n / 2 - 1; i >= 0; --i) heapifyBinary(a, n, i);
    for (int end = n - 1; end > 0; --end) {
        countedSwap(a, 0, end);  
        heapifyBinary(a, end, 0);
    }
}


void heapifyTernary(vector<int>& a, int n, int i) {
    while (true) {
        int largest = i;
        int c1 = 3 * i + 1, c2 = 3 * i + 2, c3 = 3 * i + 3;

        if (c1 < n) { COMP++; if (a[c1] > a[largest]) largest = c1; }
        if (c2 < n) { COMP++; if (a[c2] > a[largest]) largest = c2; }
        if (c3 < n) { COMP++; if (a[c3] > a[largest]) largest = c3; }

        if (largest == i) break;
        countedSwap(a, i, largest); 
        i = largest;
    }
}
void heapSortTernary(vector<int>& a) {
    int n = (int)a.size();
    for (int i = (n - 2) / 3; i >= 0; --i) heapifyTernary(a, n, i);
    for (int end = n - 1; end > 0; --end) {
        countedSwap(a, 0, end); 
        heapifyTernary(a, end, 0);
    }
}


vector<int> genRandom(int n, int lo, int hi, mt19937& rng) {
    uniform_int_distribution<int> dist(lo, hi);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) a[i] = dist(rng);
    return a;
}
vector<int> genNearlySorted(int n, int swaps, mt19937& rng) {
    vector<int> a(n);
    for (int i = 0; i < n; ++i) a[i] = i;
    uniform_int_distribution<int> dist(0, n ? n - 1 : 0);
    for (int s = 0; s < swaps && n > 1; ++s) {
        int i = dist(rng), j = dist(rng);
        if (i != j) std::swap(a[i], a[j]);
    }
    return a;
}
vector<int> genFewUniques(int n, int distinct, mt19937& rng) {
    if (distinct < 1) distinct = 1;
    uniform_int_distribution<int> pick(0, distinct - 1);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) a[i] = pick(rng);
    return a;
}

struct Result {
    long long comps = 0;
    long long assigns = 0;
    double    time_ms = 0.0;   
};

template <typename Sorter>
Result runOnce(Sorter sorter, const vector<int>& base) {
    vector<int> a = base;          
    resetCounters();
    auto t0 = chrono::steady_clock::now();
    sorter(a);
    auto t1 = chrono::steady_clock::now();
    double ms = chrono::duration<double, milli>(t1 - t0).count();

    if (!is_sorted(a.begin(), a.end())) {
        cerr << "[UWAGA] Wynik nieposortowany!\n";
    }
    return { COMP, ASSIGN, ms };
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    
    vector<int> sizes = { 50, 200, 800, 2000 };
    int T = 5;                 
    int nearly_swaps = 5;      
    int few_distinct = 5;      
    int lo = -1000, hi = 1000;

    if (argc >= 2) { 
        sizes.clear();
        for (int i = 1; i < argc; ++i) sizes.push_back(atoi(argv[i]));
    }

    mt19937 rng(1234567);

    
    std::ofstream out("C:\\Users\\annal\\Documents\\wyniki.csv");
    out << "scenario,n,algorithm,comps,assigns,timems\n";

    auto dumpRow = [&](const string& scen, int n, const string& alg, const Result& r) {
        
        ostringstream ms; ms << fixed << setprecision(6) << r.time_ms;
        out << scen << "," << n << "," << alg << ","
            << r.comps << "," << r.assigns << "," << ms.str() << "\n";
        };

   
    const vector<string> scenNames = {
        "Random", "NearlySorted", "Sorted", "Reversed", "FewUniques"
    };

    for (int n : sizes) {
        for (const string& scen : scenNames) {
            for (int t = 0; t < T; ++t) {
                vector<int> base;
                if (scen == "Random")            base = genRandom(n, lo, hi, rng);
                else if (scen == "NearlySorted") base = genNearlySorted(n, nearly_swaps, rng);
                else if (scen == "Sorted") { base.resize(n); for (int i = 0; i < n; ++i) base[i] = i; }
                else if (scen == "Reversed") { base.resize(n); for (int i = 0; i < n; ++i) base[i] = n - 1 - i; }
                else if (scen == "FewUniques")   base = genFewUniques(n, few_distinct, rng);

                dumpRow(scen, n, "Insertion", runOnce([](vector<int>& v) { insertionSort(v); }, base));
                dumpRow(scen, n, "DoubleInsertion", runOnce([](vector<int>& v) { doubleInsertionSort(v); }, base));
                dumpRow(scen, n, "MergeSort2",
                    runOnce([&](vector<int>& v) { if (!v.empty()) mergeSort2(v, 0, (int)v.size() - 1); }, base));
                dumpRow(scen, n, "MergeSort3",
                    runOnce([&](vector<int>& v) { if (!v.empty()) mergeSort3(v, 0, (int)v.size() - 1); }, base));
                dumpRow(scen, n, "HeapBinary", runOnce([](vector<int>& v) { heapSortBinary(v); }, base));
                dumpRow(scen, n, "HeapTernary", runOnce([](vector<int>& v) { heapSortTernary(v); }, base));
            }
        }
    }

    out.close();
    cout << "Zapisano wyniki do pliku: wyniki.csv\n";
    return 0;
}