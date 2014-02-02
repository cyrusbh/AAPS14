/**
* Author:   Markus Niemelä
* Problem:  CD
* Started:  2014-02-02
*
* Submission 3: Changing ints to longs, unsure about size on Kattis.
* Submission 4: Actually reading longs now.
* Submission 5: The code now actually handles several test cases, as per the problem definition...
* Submission 6: Moved vector outside of loop to avoid segfault.
* Submission 8: Bad loop conditions perhaps?
*/

#include <cstdio>
#include <vector>

using namespace std;

int main(int argc, char* argv[]){
	
	vector<long> jack;
	while(true){
		long n, m, jill;
		long sum = 0;
		scanf("%ld %ld", &n, &m);
		if(n == 0 && m == 0)
			break;
		jack.clear();
		jack.reserve(n);
		for(long i = 0; i < n; i++)
			scanf("%ld", &jack[i]);
		for(long i = 0, j = 0; i < m; i++){
			scanf("%ld", &jill);
			for(; j < n && jack[j] < jill; j++);
			if(jack[j] == jill)
				sum++;
		}
		printf("%ld\n", sum);
	}
	return 0;
}