#include "lc.hpp"

class Solution1 {
public:
    int totalWaviness(int num1, int num2) {
        auto countWaviness = [](int x){
            if (x < 100) return 0;
            std::vector<int> digits;
            do{
                digits.push_back(x % 10);
                x /= 10;
            } while (x > 0);
            int w = 0;
            for (int i = 1; i < digits.size() - 1; ++i) {
                if ((digits[i] > digits[i - 1] && digits[i] > digits[i + 1]) ||
                    (digits[i] < digits[i - 1] && digits[i] < digits[i + 1])) {
                    ++w;
                }
            }
            return w;
        };
        int total = 0;
        for (int i = num1; i <= num2; ++i) {
            total += countWaviness(i);
        }
        return total;
    }
};

class Solution {
public:
    int totalWaviness(int num1, int num2) {
        auto solver = [](int x) {
            if (x < 100) return 0;

            auto digits = [](int x) {
                std::vector<int> digits;
                while (x > 0) {
                    digits.push_back(x % 10);
                    x /= 10;
                }
                std::reverse(digits.begin(), digits.end());
                return digits;
            }(x);
            const int N = digits.size();

            long long mcnt[20][10][10], msum[20][10][10];
            std::fill(&mcnt[0][0][0], &mcnt[0][0][0] + sizeof(mcnt) / sizeof(long long), -1LL);
            std::fill(&msum[0][0][0], &msum[0][0][0] + sizeof(msum) / sizeof(long long), -1LL);

            auto dfs = [&](this auto &&dfs, int pos, int prev, int cur, bool tight, bool leading) -> std::pair<long long, long long> {
                if (pos == N) 
                    return {1LL, 0LL};
                
                if (!tight && !leading && prev != -1 && cur != -1 && mcnt[pos][prev][cur] != -1LL && msum[pos][prev][cur] != -1LL) 
                    return {mcnt[pos][prev][cur], msum[pos][prev][cur]};
                
                long long cnt = 0, sum = 0;
                for (int next = 0; next <= (tight ? digits[pos] : 9); next++){
                    auto [ncnt, nsum] = dfs(pos + 1, cur, (leading && next == 0 ? -1 : next), tight && next == digits[pos], leading && next == 0);
                    if (!leading && prev != -1 && cur != -1) 
                        sum += ncnt * (cur > prev && cur > next || cur < prev && cur < next);
                    cnt += ncnt;
                    sum += nsum;
                }

                if (!tight && !leading && prev != -1 && cur != -1) {
                    mcnt[pos][prev][cur] = cnt;
                    msum[pos][prev][cur] = sum;
                }

                return {cnt, sum};
            };

            return (int)dfs(0, -1, -1, true, true).second;
        };

        return solver(num2) - solver(num1 - 1);
    }
};