/**
* Author:   Markus Niemelä
* Problem:  Union-Find
* Started:  2014-02-02
*
* Submission 2: ints substituted for longs in certain places.
* Submission 3: Changed find(long) function to return root() instead of r.
*/

#include <cstdio>
#include <vector>

using namespace std;

struct UFNode {
    UFNode* r;
	int rank;
	
    UFNode* root(){
        if(r != this)
            r = r->root();
        return r;
    }
    
    void join(UFNode* v){
        if(root() != v->root()){
			if(r->rank < v->r->rank){
				r->r = v->r;
			}
			else if(r->rank > v->r->rank){
				v->r->r = r;
			}
			else{
				v->r->r = r;
				r->rank++;
			}
		}
    }
};

class UnionFindSet{
		vector<UFNode*> sets;
	public:
		UnionFindSet(long n) : sets(n){
			for(long i = 0; i < n; i++){
				sets[i] = new UFNode();
				sets[i]->r = sets[i];
				sets[i]->rank = 0;
			}
		};
		void join(long a, long b){
			sets[a]->join(sets[b]);
		}
		UFNode* find(long a){
			return sets[a]->root();
		}
};

int main(int argc, char* argv[]){
	long n, q, a, b;
	char c;
	scanf("%d %d", &n, &q);
	UnionFindSet uf(n);
	
	for(long i = 0; i < q; i++){
		scanf("\n%c %d %d", &c, &a, &b);
		if(c == '=')
			uf.join(a, b);
		else
			printf("%s\n", uf.find(a) == uf.find(b) ? "yes" : "no");
	}
	return 0;
}