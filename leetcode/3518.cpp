#include "lc.hpp"

class Solution {
public:
    string smallestPalindrome(string s, int k) {
        std::vector<int> freq(26, 0);
        for (char c : std::string_view(s).substr(0, s.size() / 2))
            freq[c - 'a']++;
        std::string result = "";

        auto P = [&](int k) {
            long long cnt = 1;
            int remain = std::accumulate(freq.begin(), freq.end(), 0);
            auto C = [](int n, int r, int k) {
                r = std::min(r, n - r);
                long long res = 1;
                for (int i = 0; i < r; i++) {
                    res *= (n - i);
                    res /= (i + 1);
                    if (res > k) return 1LL * k + 1;
                }
                return res;
            };
            for (int x : freq) {
                if (x == 0) continue;
                cnt *= C(remain, x, (k + cnt - 1) / cnt);
                remain -= x;
                if (cnt > k) return 1LL * k + 1;
            }
            return cnt;
        };

        if (P(k) < k) return "";

        for (int i = 0; i < s.size() / 2; i++) {
            for (char c = 'a'; c <= 'z'; c++) {
                if (freq[c - 'a'] == 0) continue;
                freq[c - 'a']--;
                long long cnt = P(k);
                if (cnt >= k) {
                    result += c;
                    break;
                }
                freq[c - 'a']++;
                k -= cnt;
            }
        }
        return result + (s.size() % 2 == 1 ? string(1, s[s.size() / 2]) : "") + string(result.rbegin(), result.rend());
    }
};