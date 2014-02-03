/**
* Author:   Markus Niemelä
* Problem:  Almost Union-Find
* Started:  2014-02-02
*
* Submission 2: Decrements element counter on move.
* Submission 3: Setting root pointer to self on move, could previously have been null.
* Submission 4: Rewrote the data structure based on the code in Competitive Programming 3.
* Submission 5: Reading longs.
* Submission 7: Handling several test cases as per problem definition...
*/

#include <cstdio>
#include <vector>

using namespace std;

class UnionFind {
private:
	vector<long> p, rank, setSize;
	vector<long long> setSum;
	long numSets;
public:
	UnionFind(long N) {
		setSize.assign(N, 1); 
		numSets = N; 
		rank.assign(N, 0);
		p.assign(N, 0);
		setSum.assign(N, 0);
		for (long i = 0; i < N; i++) 
			p[i] = setSum[i] = i;
	}
	
	long findSet(long i) {
		return (p[i] == i) ? i : (p[i] = findSet(p[i])); 
	}
	bool isSameSet(long i, long j) { 
		return findSet(i) == findSet(j); 
	}
	void unionSet(long i, long j) { 
		if (!isSameSet(i, j)) { 
			numSets--; 	
			long x = findSet(i), y = findSet(j);
			if (rank[x] > rank[y]) { 
				p[y] = x;
				setSize[x] += setSize[y];
				setSum[x] += setSum[y];
			}
			else{ 
				p[x] = y; 
				setSize[y] += setSize[x];
				setSum[y] += setSum[x];
				if (rank[x] == rank[y]) 
					rank[y]++;
			}
		}
	}
	
	void remove(long i){
		if(sizeOfSet(i) > 1){
			long size = (long) p.size();
			if(p[i] == i){
				//printf("sup %d\n", i);
				long tmp = -1;
				for(int j = 0; j < size; j++){
					if(j == i)
						continue;
					if(p[j] == i){
						p[j] = tmp = j;
						//printf("%d gets %d\n", j, tmp);
						break;
					}
				}
				for(int j = tmp; j < size; j++){
					if(p[j] == i){
						p[j] = tmp;
						//printf("%d gets %d\n", j, tmp);
					}
				}
				setSize[tmp] = setSize[i] - 1;
				setSum[tmp] = setSum[i] - i;
			}
			else{
				for(int j = 0; j < size; j++){
					if(p[j] == i){
						p[j] = findSet(i);
					}
				}
				setSize[findSet(i)]--;
				setSum[findSet(i)]-= i;
			}
			p[i] = i;
			setSize[i] = 1;
			setSum[i] = i;
			numSets++;
		}
	}
	
	void move(long i, long j){
		if(findSet(i) != findSet(j)){
			remove(i);
			unionSet(i, j);
		}
	}
	
	long numDisjointSets() {
		return numSets; 
	}
	long sizeOfSet(long i) { 
		return setSize[findSet(i)]; 
	}
	
	long long sumOfSet(long i) {
		return setSum[findSet(i)];
	}
};

int main(int argc, char* argv[]){
	long n, m, c, p, q;
	while (scanf("%ld %ld", &n, &m) != EOF){
		UnionFind uf(n+1);
		
		for(long i = 0; i < m; i++){
			scanf("%ld", &c);
			if(c == 3){
				scanf("%ld", &p);
				printf("%ld %lld\n", uf.sizeOfSet(p), uf.sumOfSet(p));
			}
			else{
				scanf("%ld %ld", &p, &q);
				if(c == 1)
					uf.unionSet(p, q);
				else
					uf.move(p, q);
			}
		}
	}
	return 0;
}