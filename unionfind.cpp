/**
* Author:   Markus Niemelä
* Problem:  Union-Find
* Started:  2014-02-02
*/

#include <cstdio>
#include <vector>

using namespace std;

struct UFNode {
    UFNode* r;
	int rank;
	
	UFNode(){
		r = this;
		rank = 0;
	}
	
    UFNode* root(){
		printf("X\n");
        if(r != this)
			printf("Y\n");
            r = r->root();
        return r;
    }
    
    void join(UFNode* v){
		printf("A\n");
        if(root() != v->root()){
			printf("B\n");
			if(r->rank < v->r->rank){
				r->r = v->r;
				printf("C\n");
			}
			else if(r->rank > v->r->rank){
				printf("D\n");
				v->r->r = r;
			}
			else{
				v->r->r = r;
				r->rank++;
				printf("E\n");
			}
		}
    }
};

class UnionFindSet{
		vector<UFNode> sets;
	public:
		UnionFindSet(long n) : sets(n){};
		void join(long a, long b){
			sets[a].join(&sets[b]);
		}
		UFNode* find(long a){
			return sets[a].r;
		}
};

int main(int argc, char* argv[]){
	long n, q, a, b;
	char c;
	scanf("%d %d", &n, &q);
	UnionFindSet uf(n);
	
	for(int i = 0; i < q; i++){
		scanf("\n%c %d %d", &c, &a, &b);
		if(c == '='){
			uf.join(a, b);
			printf("Joined %c and %b\n", a, b);
		}
		else
			printf("%s\n", uf.find(a) == uf.find(b) ? "yes" : "no");
	}
	return 0;
}