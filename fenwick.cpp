/**
* Author:   Markus Niemelä
* Problem:  Fenwick Tree
* Started:  2014-01-30
*
* Comments: Note the difference uses of i in the input,
*           and how they must be offset differently.
* 
* Submission 2: Allowing for values greater than INT_MAX
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
        void add(int k, int v) {
            for (; k < (int)ft.size(); k += LSOne(k))
                ft[k] += v; 
        }
};

int main(int argc, char* argv[]){
    int n, q, i, d;
    char c;
    scanf("%d %d", &n, &q);
    FenwickTree ft(n);
    
    for(int j = 0; j < q; j++){
        scanf("%c", &c);
        scanf("%c", &c);
        if(c == '+'){
            scanf("%d %d", &i, &d);
            ft.add(i+1, d);
        }
        else{
            scanf("%d", &i);
            printf("%lld\n", ft.sum(i));
        }
    }
        
    return 0;
}