#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2763"

#include <stdio.h>
#include <iostream>
#include "../../string/rolling_hash.hpp"

int main() {
	std::string s; std::cin >> s;

	rolling_hash hash(s);
	for(int i = (int)s.size(); i > 0; i--) {
		int A = i;
		int B = (int)s.size() - 3 * A;
		if(A <= 0 or B <= 0 or B & 1) continue; B /= 2;

		long long X = hash.hash(0, A);
		long long Y = hash.hash(A, A + B);
		if(X != hash.hash(A + B, A + B + A)) continue;
		if(Y != hash.hash(A + B + A, A + B + A + B)) continue;
		if(X != hash.hash(A + B + A + B, A + B + A + B + A)) continue;

		printf("Love %s!\n", s.substr(0, A + B).c_str());
		return 0;
	}
	printf("mitomerarenaiWA\n");
	return 0;
}
