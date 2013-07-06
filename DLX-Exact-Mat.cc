const int maxN = 60 * 20, maxM = 60 * 10;
const int max_size = maxN * maxM;
const int inf = 0x3f3f3f3f;
int L[max_size], R[max_size], U[max_size], D[max_size], CH[max_size], RH[max_size];
int S[maxM], O[maxM];
int head, size;
int node(int up, int down, int left, int right) {
    U[size] = up, D[size] = down; L[size] = left, R[size] = right;
    D[up] = U[down] = R[left] = L[right] = size;
    return size++;
}
bool mat[maxN][maxM];
void init(int N, int M) {
    size = 0;
    head = node(0, 0, 0, 0);
    for (int j = 1; j <= M; ++j) {
        CH[j] = node(size, size, L[head], head), S[j] = 0;
    }
    for (int i = 1; i <= N; ++i) {
        int row = -1, k;
        for (int j = 1; j <= M; ++j) {
            if (!mat[i][j]) continue;
            if (row == -1) {
                row = node(U[CH[j]], CH[j], size, size);
                RH[row] = i, CH[row] = CH[j], ++S[j];
            } else {
                k = node(U[CH[j]], CH[j], L[row], row);
                RH[k] = i, CH[k] = CH[j], ++S[j];
            }
        }
    }
}
void remove(const int &c) {
    L[R[c]] = L[c], R[L[c]] = R[c];
    for (int i = D[c]; i != c; i = D[i]) 
        for (int j = R[i]; j != i; j = R[j]) 
            U[D[j]] = U[j], D[U[j]] = D[j], --S[CH[j]];
}
void resume(const int &c) {
    for (int i = U[c]; i != c; i = U[i]) 
        for (int j = L[i]; j != i; j = L[j]) 
            ++S[CH[j]]; U[D[j]] = D[U[j]] = j;
    L[R[c]] = R[L[c]] = c;
}
int len;
bool DLX(const int &k) {
    if (R[head] == head) {
        len = k - 1; return true;
    }
    int s = inf, c;
    for (int t = R[head]; t != head; t = R[t]) 
        if (S[t] < s) s = S[t], c = t;
    remove(c);
    for (int i = D[c]; i != c; i = D[i]) {
        O[k] = RH[i];
        for (int j = R[i]; j != i; j = R[j]) remove(CH[j]);
        if (DLX(k + 1)) return true;
        for (int j = L[i]; j != i; j = L[j]) resume(CH[j]);
    }
    resume(c);
    return false;
}
