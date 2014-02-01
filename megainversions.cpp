/**
* Author:   Markus Niemelä
* Problem:  Mega Inversions
* Started:  2014-01-31
*
* Submission 2: Removed unnecessary tree, changed tree type to long long.
*/

#include <cstdio>
#include <vector>

using namespace std;

class FenwickTree{
        vector<long long> ft;
        int LSOne(int i) {return i & -i;};
    public:
        FenwickTree(int n) : ft(n+1, 0){};
        long long sum(int b) {
            long long sum = 0; 
            for (; b; b -= LSOne(b)) 
                sum += ft[b];
            return sum;
        }
        long long sum(int a, int b) { return sum(b) - (a == 1 ? 0 : sum(a - 1)); }
        void add(int k, long long v) {
            for (; k < (int)ft.size(); k += LSOne(k))
                ft[k] += v; 
        }
};

int main(int argc, char* argv[]){
    int n, a;
	long long sum = 0;
	
	scanf("%d", &n);
	FenwickTree s1(n+1);
	FenwickTree s2(n+1);
	
	for(int i = 1; i <= n; i++){
		scanf("%d", &a);
		sum += s2.sum(n-a);
		s2.add(n-a+1, s1.sum(n-a));
		s1.add(n-a+1, 1);
	}
	printf("%lld", sum);
    return 0;
}