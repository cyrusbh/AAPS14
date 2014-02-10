/**
* Author:   Markus Niemelä
* Problem:  Best Compression Ever
* Started:  2014-02-10
*/

#include <cstdio>

int main(int argc, char* argv[]){
	long long n;
	int b;
	scanf("%lld %d", &n, &b);
	printf("%s\n", (1LL << (b+1)) - 1 >= n ? "yes" : "no");
	return 0;
}