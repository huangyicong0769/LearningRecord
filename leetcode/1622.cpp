#include "lc.hpp"


class Fancy {
    const int M = 1e9 + 7;
    vector<int> l;
    vector<int> lazy;
    vector<tuple<int, int, int>> events;
    bool current_block_sealed;

    // 每个事件块表示对 [0, size) 的元素施加一次仿射变换: x = x * mul + add
    void ensure_event_block(){
        int size = static_cast<int>(l.size());
        if (events.empty() || get<0>(events.back()) != size || current_block_sealed){
            events.push_back({size, 1, 0});
            current_block_sealed = false;
        }
    }

    void update(int idx){
        for (int i = lazy[idx]; i < events.size(); i++){
            auto &[size, mul, add] = events[i];
            if (size <= idx)
                continue;
            l[idx] = static_cast<int>((1LL * l[idx] * mul + add) % M);
            if (i == static_cast<int>(events.size()) - 1 && size == static_cast<int>(l.size()))
                current_block_sealed = true;
        }
        lazy[idx] = static_cast<int>(events.size());
    }

public:
    Fancy() : current_block_sealed(false) {}
    
    void append(int val) {
        l.push_back(val);
        lazy.push_back(static_cast<int>(events.size()));
        current_block_sealed = false;
    }
    
    void addAll(int inc) {
        ensure_event_block();
        auto &[size, mul, add] = events.back();
        add = (add + inc) % M;
    }
    
    void multAll(int m) {
        ensure_event_block();
        auto &[size, mul, add] = events.back();
        mul = static_cast<int>(1LL * mul * m % M);
        add = static_cast<int>(1LL * add * m % M);
    }
    
    int getIndex(int idx) {
        if (idx >= l.size())
            return -1;
        if (events.size() > lazy[idx])
            update(idx);
        return l[idx];
    }
};

/**
 * Your Fancy object will be instantiated and called as such:
 * Fancy* obj = new Fancy();
 * obj->append(val);
 * obj->addAll(inc);
 * obj->multAll(m);
 * int param_4 = obj->getIndex(idx);
 */