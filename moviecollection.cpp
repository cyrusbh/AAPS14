/**
* Author:   Markus Niemelä
* Problem:  Movie collection
* Started:  2014-02-10
* 
* Comments: 5 minutes away from finishing before the end of the contest, woo!
*			Perhaps a better naming scheme for variables would save me some troubleshooting...
*/

#include <cstdio>
#include <vector>

using namespace std;

class FenwickTree{
        vector<long long> ft;
		int size;
        int LSOne(long long i) {return i & -i;};
    public:
        FenwickTree(int n) : ft(n+1, 0){};
        long long sum(long long b) {
            long long sum = 0; 
            for (; b; b -= LSOne(b)){
                sum += ft[b];
			}
            return sum;
        }
        long long sum(int a, int b) { return sum(b) - (a == 1 ? 0 : sum(a - 1)); }
        void add(int k, int v) {
            for (; k < (long long)ft.size(); k += LSOne(k))
                ft[k] += v; 
        }
};

int main(int argc, char* argv[]){
    int n;
	long long m, r, a, x;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
		scanf("%lld %lld", &m, &r);
		FenwickTree ft(m+r);
		vector<long long> index(m+1);
		for(long long j = 1; j <= m; j++){
			ft.add(r+j, 1);
			index[j] = r+j;
		}
		for(long long j = 0; j < r; j++){
			scanf("%lld", &x);			
			printf("%lld%c", ft.sum(index[x]-1), j+1 == r ? '\n' : ' ');
			ft.add(index[x], -1);
			index[x] = r-j;
			ft.add(index[x], 1);
		}
    }
        
    return 0;
}