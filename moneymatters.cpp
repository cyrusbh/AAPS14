/**
* Author:   Markus Niemelä
* Problem:  Money Matters
* Started:  2014-03-09
*/

#include <cstdio>
#include <vector>
#include <map>

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
		map<UFNode*, int> root_index;
	public:
		UnionFindSet(int n) : sets(n){
			for(int i = 0; i < n; i++){
				sets[i] = new UFNode();
				sets[i]->r = sets[i];
				sets[i]->rank = 0;
				root_index[sets[i]] = i;
			}
		};
		void join(int a, int b){
			sets[a]->join(sets[b]);
		}
		UFNode* find(int a){
			return sets[a]->root();
		}
		
		int index(UFNode* n){
			return root_index[n];
		}
};

int main(int argc, char* argv[]){
	int n, m, o, x, y;
	scanf("%d %d", &n, &m);
	UnionFindSet uf(n);
	map<int, int> ssum;
	for(int i = 0; i < n; i++){
		scanf("%d", &o);
		ssum[i] = o;
	}
	for(int i = 0; i < m; i++){
		scanf("%d %d", &x, &y);
		if(uf.find(x) != uf.find(y)){
			int x_idx = uf.index(uf.find(x)), y_idx = uf.index(uf.find(y));
			uf.join(x, y);
			int new_idx = uf.index(uf.find(x)), del_idx = new_idx == x_idx ? y_idx : x_idx;
			ssum[new_idx] += ssum[del_idx];
			ssum.erase(del_idx);
		}
	}
	bool possible = true;
	for(map<int, int>::iterator it = ssum.begin(); it != ssum.end() && possible; it++){
			possible = it->second == 0;
	}
	printf("%s\n", possible ? "POSSIBLE" : "IMPOSSIBLE");
	return 0;
}