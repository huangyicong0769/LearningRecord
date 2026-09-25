#include "lc.hpp"

class Solution {
    using Set = std::set<std::string>;
    using State = std::pair<Set, Set>;

    Set mul(const Set& a, const Set& b) {
        Set res;
        for (const auto& x : a)
            for (const auto& y : b)
                res.insert(x + y);
        return res;
    }

public:
    vector<string> braceExpansionII(string expression) {
        expression = "{" + expression + "}";

        std::stack<State> stk;
        stk.push({{}, {""}});

        string temp;

        for (char c : expression) {
            if ('a' <= c && c <= 'z') {
                temp += c;
                continue;
            }

            if (!temp.empty()) {
                auto& [sum, prod] = stk.top();
                prod = mul(prod, {temp});
                temp.clear();
            }

            if (c == '{') {
                stk.push({{}, {""}});
            }
            else if (c == ',') {
                auto& [sum, prod] = stk.top();
                sum.merge(prod);
                prod = {""};
            }
            else if (c == '}') {
                auto [sum, prod] = std::move(stk.top());
                stk.pop();

                sum.merge(prod);

                auto& [parent_sum, parent_prod] = stk.top();
                parent_prod = mul(parent_prod, sum);
            }
        }

        auto& [sum, prod] = stk.top();
        return {prod.begin(), prod.end()};
    }
};