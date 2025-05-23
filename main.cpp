#include <bits/stdc++.h>
using namespace std;
using Clock = chrono::high_resolution_clock;

struct SortResult {
    long long comparisons;
    double durationMs;
};

class StringGenerator {
    const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#%:;^&*()-.";
public:
    string generateRandomString(int length) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, (int)alphabet.size() - 1);
        string s;
        for (int i = 0; i < length; ++i) s += alphabet[dist(gen)];
        return s;
    }
    vector<string> generateRandomArray(int size, int length) {
        vector<string> arr;
        arr.reserve(size);
        for (int i = 0; i < size; ++i) arr.push_back(generateRandomString(length));
        return arr;
    }
    vector<string> generateReverseSortedArray(int size, int length) {
        auto arr = generateRandomArray(size, length);
        sort(arr.rbegin(), arr.rend());
        return arr;
    }
    vector<string> generateAlmostSortedArray(int size, int length) {
        auto arr = generateRandomArray(size, length);
        sort(arr.begin(), arr.end());
        if (!arr.empty()) swap(arr[0], arr[size - 1]);
        return arr;
    }

    vector<string> generateCommonPrefixArray(int size, int totalLength, int prefixLength) {
        string prefix = generateRandomString(prefixLength);
        vector<string> arr;
        arr.reserve(size);
        for (int i = 0; i < size; ++i) {
            string s = prefix + generateRandomString(totalLength - prefixLength);
            arr.push_back(move(s));
        }
        return arr;
    }

};

int charAt(const string &s, int d) {
    return d < (int)s.size() ? (unsigned char)s[d] + 1 : 0;
}

void QuickSort(vector<string>& a, int lo, int hi, long long &comps) {
    if (lo >= hi) return;
    string pivot = a[(lo + hi) >> 1];
    int i = lo, j = hi;
    while (i <= j) {
        while (true) { comps++; if (!(a[i] < pivot)) break; i++; }
        while (true) { comps++; if (!(a[j] > pivot)) break; j--; }
        if (i <= j) swap(a[i++], a[j--]);
    }
    QuickSort(a, lo, j, comps);
    QuickSort(a, i, hi, comps);
}

SortResult standardQuicksort(vector<string> a) {
    long long comps = 0;
    auto start = Clock::now();
    QuickSort(a, 0, (int)a.size() - 1, comps);
    auto end = Clock::now();
    double ms = chrono::duration<double, milli>(end - start).count();
    return SortResult{comps, ms};
}

void mergePass(vector<string>& a, int lo, int mid, int hi, vector<string>& tmp, long long &comps) {
    int i = lo, j = mid + 1, k = lo;
    while (i <= mid && j <= hi) {
        comps++;
        if (a[i] <= a[j]) tmp[k++] = move(a[i++]);
        else               tmp[k++] = move(a[j++]);
    }
    while (i <= mid) tmp[k++] = move(a[i++]);
    while (j <= hi)  tmp[k++] = move(a[j++]);
    for (int x = lo; x <= hi; ++x)
        a[x] = move(tmp[x]);
}

void MergeSortRec(vector<string>& a, int lo, int hi, vector<string>& tmp, long long &comps) {
    if (lo >= hi) return;
    int mid = (lo + hi) >> 1;
    MergeSortRec(a, lo, mid, tmp, comps);
    MergeSortRec(a, mid + 1, hi, tmp, comps);
    mergePass(a, lo, mid, hi, tmp, comps);
}

SortResult standardMergesort(vector<string> a) {
    long long comps = 0;
    vector<string> tmp(a.size());
    auto start = Clock::now();
    MergeSortRec(a, 0, (int)a.size() - 1, tmp, comps);
    auto end = Clock::now();
    double ms = chrono::duration<double, milli>(end - start).count();
    return SortResult{comps, ms};
}

vector<string> TernaryQuickSort(const vector<string>& R, int L, long long &comps) {
    if (R.size() <= 1) return R;
    vector<string> R_excl, R_rest;
    for (auto &s : R) {
        if ((int)s.size() == L) R_excl.push_back(s);
        else                    R_rest.push_back(s);
    }
    if (R_rest.empty()) return R_excl;
    const string& pivot = R_rest[R_rest.size()/2];
    vector<string> less, equal, great;
    for (auto &s : R_rest) {
        comps += 2; // two comparisons: < and ==
        if (s[L] < pivot[L])      less.push_back(s);
        else if (s[L] == pivot[L]) equal.push_back(s);
        else                       great.push_back(s);
    }
    auto sl = TernaryQuickSort(less, L, comps);
    auto se = TernaryQuickSort(equal, L+1, comps);
    auto sg = TernaryQuickSort(great, L, comps);
    vector<string> res;
    res.reserve(R.size());
    res.insert(res.end(), R_excl.begin(), R_excl.end());
    res.insert(res.end(), sl.begin(), sl.end());
    res.insert(res.end(), se.begin(), se.end());
    res.insert(res.end(), sg.begin(), sg.end());
    return res;
}

SortResult ternaryStringQuicksort(vector<string> a) {
    long long comps = 0;
    auto start = Clock::now();
    auto sorted = TernaryQuickSort(a, 0, comps);
    auto end = Clock::now();
    double ms = chrono::duration<double, milli>(end - start).count();
    return SortResult{comps, ms};
}

pair<bool,int> LcpCompare(const string& A, const string& B, int k, long long &comps) {
    comps++; // one LCP compare operation
    int n=A.size(), m=B.size(), l=k;
    while (l<n && l<m && A[l]==B[l]) ++l;
    if (l==n||l==m) {
        if (n==m) return {false,l};
        return {n<m,l};
    }
    return {A[l]<B[l],l};
}

vector<pair<string,int>> StringMerge(
    const vector<pair<string,int>>& P,
    const vector<pair<string,int>>& Q,
    long long &comps) {
    vector<pair<string,int>> R;
    int i=0,j=0,m=P.size(),f=Q.size();
    while(i<m && j<f) {
        int ki=P[i].second, pj=Q[j].second;
        if (ki>pj)      { R.emplace_back(P[i].first,ki); ++i; }
        else if (ki<pj) { R.emplace_back(Q[j].first,pj); ++j; }
        else {
            auto [less,h]=LcpCompare(P[i].first,Q[j].first,ki, comps);
            if (less)      { R.emplace_back(P[i].first,ki); ++i; }
            else           { R.emplace_back(Q[j].first,pj); ++j; }
        }
    }
    while(i<m) R.push_back(P[i++]);
    while(j<f) R.push_back(Q[j++]);
    return R;
}

vector<pair<string,int>> StringMergeSort(const vector<string>& R, long long &comps) {
    if (R.size()==1) return {{R[0],0}};
    int mid=R.size()/2;
    vector<string> L(R.begin(),R.begin()+mid);
    vector<string> Rr(R.begin()+mid,R.end());
    auto P=StringMergeSort(L, comps);
    auto Q=StringMergeSort(Rr, comps);
    return StringMerge(P, Q, comps);
}

SortResult stringMergesortLCP(vector<string> a) {
    long long comps = 0;
    auto start = Clock::now();
    auto sorted = StringMergeSort(a, comps);
    auto end = Clock::now();
    double ms = chrono::duration<double, milli>(end - start).count();
    return SortResult{comps, ms};
}

void msdRadixSort(vector<string>& a, int lo, int hi, int d) {
    if (hi <= lo) return;
    const int R = 256;
    vector<int> count(R + 2, 0);
    for (int i = lo; i <= hi; ++i) {
        int c = charAt(a[i], d);
        count[c + 1]++;
    }
    for (int r = 0; r <= R; ++r) {
        count[r + 1] += count[r];
    }
    vector<string> aux(hi - lo + 1);
    for (int i = lo; i <= hi; ++i) {
        int c = charAt(a[i], d);
        aux[count[c]++] = move(a[i]);
    }
    for (int i = lo; i <= hi; ++i) {
        a[i] = move(aux[i - lo]);
    }
    for (int r = 0; r < R; ++r) {
        int subLo = lo + count[r];
        int subHi = lo + count[r + 1] - 1;
        if (subLo <= subHi) {
            msdRadixSort(a, subLo, subHi, d + 1);
        }
    }
}

SortResult msdRadixSort(vector<string> a) {
    long long comps = 0;
    auto start = Clock::now();
    msdRadixSort(a,0,(int)a.size()-1,0);
    auto end = Clock::now();
    double ms = chrono::duration<double, milli>(end - start).count();
    return SortResult{comps, ms};
}

const int ALPHABET = 256;
void MSDRadixQuickSort(vector<string>& a, int low, int high, int d, long long &comps) {
    if (high <= low) return;
    int size = high - low + 1;
    if (size <= ALPHABET) {
        QuickSort(a, low, high, comps);
        return;
    }
    vector<int> count(ALPHABET + 1, 0);
    for (int i = low; i <= high; ++i) {
        comps++; int idx = (d < (int)a[i].size() ? (unsigned char)a[i][d] + 1 : 0);
        count[idx]++;
    }
    vector<int> start(ALPHABET + 1, 0);
    start[0] = low;
    for (int r = 1; r <= ALPHABET; ++r)
        start[r] = start[r - 1] + count[r - 1];
    vector<int> idx = start;
    vector<string> aux(size);
    for (int i = low; i <= high; ++i) {
        comps++; int bucket = (d < (int)a[i].size() ? (unsigned char)a[i][d] + 1 : 0);
        aux[idx[bucket] - low] = a[i];
        idx[bucket]++;
    }
    for (int i = 0; i < size; ++i)
        a[low + i] = aux[i];
    for (int r = 1; r <= ALPHABET; ++r) {
        int cnt = count[r];
        if (cnt <= 1) continue;
        int lo = start[r];
        int hi = lo + cnt - 1;
        MSDRadixQuickSort(a, lo, hi, d + 1, comps);
    }
}

SortResult msdRadixSortWithQS(vector<string> a) {
    long long comps = 0;
    auto start = Clock::now();
    MSDRadixQuickSort(a, 0, (int)a.size() - 1, 0, comps);
    auto end = Clock::now();
    double ms = chrono::duration<double, milli>(end - start).count();
    return SortResult{comps, ms};
}

int main(){
    const int LENGTH=50, MIN_SIZE=100, MAX_SIZE=3000, STEP=100;
    StringGenerator gen;
    cout<<"Size,QS_time_ms,QS_comps,MS_time_ms,MS_comps,TSQS_time_ms,TSQS_comps,LCPMS_time_ms,LCPMS_comps,MSD_time_ms,MSD_comps,MSDQS_time_ms,MSDQS_comps\n";
    for(int size=MIN_SIZE; size<=MAX_SIZE; size+=STEP) {
        auto data = gen.generateCommonPrefixArray(size,LENGTH, LENGTH / 3);
        auto r1 = standardQuicksort(data);
        auto r2 = standardMergesort(data);
        auto r3 = ternaryStringQuicksort(data);
        auto r4 = stringMergesortLCP(data);
        auto r5 = msdRadixSort(data);
        auto r6 = msdRadixSortWithQS(data);
        cout<<size
             <<","<<r1.comparisons
             <<","<<r2.comparisons
             <<","<<r3.comparisons
             <<","<<r4.comparisons
             <<","<<r5.comparisons
             <<","<<r6.comparisons
             <<"\n";
    }
    return 0;
}
