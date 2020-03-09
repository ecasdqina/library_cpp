#define PROBLEM "https://www.hackerrank.com/contests/kiritan-birthday-contest-2020/challenges/zundamochi"

#include <stdio.h>
#include <iostream>
#include <map>
#include "../../string/rolling_hash.hpp"

int main() {
    int n, k; scanf("%d%d", &n, &k);
    std::string s; std::cin >> s;

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

    printf("%d\n", ans);
    return 0;
}
