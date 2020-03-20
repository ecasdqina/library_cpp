#define PROBLEM "https://www.hackerrank.com/contests/kiritan-birthday-contest-2020/challenges/zundamochi"

#include <map>
#include "../../string/rolling_hash.hpp"
#include "../../other/fast_io.hpp"

int main() {
    int n, k; fin.scan(n, k);
    std::string s; fin.scan(s);

    rolling_hash hash(s);
    std::map<std::uint_fast64_t, std::vector<int>> mp;
    for(int i = 0; i < (int)s.size() - k + 1; i++) {
        mp[hash.hash(i, i + k)].push_back(i);
    }

    int ans = 0;
    for(auto vec: mp) {
        int tmp = -k, cnt = 0;
        for(auto v: vec.second) {
            if(tmp + k <= v) {
                tmp = v;
                cnt++;
            }
        }
        ans = std::max(ans, cnt);
    }

	fout.println(ans);
    return 0;
}
