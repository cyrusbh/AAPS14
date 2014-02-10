/**
* Author:   Markus Niemelä
* Problem:  Interval Cover
* Started:  2014-02-07
*
* Submission 3: Looking to solve potential rounding problems
* Submission 4: Rewrote code to simplify troubleshooting.
* Submission 5: Changed lower bound on right-variables to a from 0.
* Submission 6: Writing correct values to sol, which is now also printed, instead of index.
* Submission 7: Changed the comparison function to take the right value into consideration for ties.
* Submission 8: Reverted comparison change, fixed the real bug instead. The correct index is now stored for the saved interval,
* 				while it earlier only picked the previous one iterated over, even if that was not the interval chosen.
* Submission 9: Subtracting EPS from initial right bound when selecting the first interval to be able to select an interval
				that ends on a point interval.
*/

#include <algorithm>
#include <cstdio>

using namespace std;

const int N = 20010;
const double EPS = 1e-9;
double L[N], R[N];
int index[N], sol[N];

bool cmp(int a, int b){
	return L[a] < L[b];
}

int main(int argc, char* argv[]){
	double a, b;
	int n;
	while(scanf("%lf %lf %d", &a, &b, &n) == 3){
		double new_right, right = a;
		int cnt, i, j;
		bool flag = false;
		for(i = 0; i < n; ++i){
			scanf("%lf %lf", &L[i], &R[i]);
			index[i] = i;
		}
		sort(index, index + n, cmp);
		new_right = a - EPS;
		for(cnt = i = j = 0; i < n; i = j){
			while(j < n && L[index[j]] <= right){
				if(R[index[j]] > new_right){
					new_right = R[index[j]];
					sol[cnt] = index[j];
					flag = true;
				}
				j++;
			}
			cnt++;
			right = new_right;
			if(right + EPS > b || j == i){
				break;
			}
		}
		if(right + EPS > b && flag){
			printf("%d\n", cnt);
			for(int k = 0; k < cnt; k++)
				printf("%d%c", sol[k], k+1 == cnt ? '\n' : ' ');
		}
		else
			printf("impossible\n");
	}
	return 0;
}