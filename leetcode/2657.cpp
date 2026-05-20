#include "lc.hpp"

class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        const int N = A.size();
        std::vector<char> ha(N + 1), hb(N + 1);
        std::vector<int> C(N);
        for (int i = 0; i < N; i++){
            ha[A[i]] = 1;
            hb[B[i]] = 1;
            C[i] += ha[B[i]] + hb[A[i]] + (i != 0 ? C[i - 1] : 0) - (A[i] == B[i] ? 1 : 0);
        }
        return C;
    }
};