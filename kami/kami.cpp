#include <cstdio>
#include <list>
#include <ctime>
#define N 1111111
#define Init freopen("kami.in","r",stdin);freopen("kami.out","w",stdout)
struct osnfoag{
	int l, r, ldis, rdis, num;
}a[N];
int n,m,A[N],w[N],tot = 2,head = 1,tail = 2,rev;
void add_head(int k){
	a[ ++ tot].r = head;
	a[head].l = tot;
	a[head].ldis = a[tot].rdis = a[k].ldis;
	a[tot].num = a[k].num ^ 1;
	head = tot;
}
void add_tail(int k){
	a[ ++ tot].l = tail;
	a[tail].r = tot;
	a[tail].rdis = a[tot].ldis = a[k].rdis;
	a[tot].num = a[k].num ^ 1;
	tail = tot;
}
int main(){
	Init;
	scanf("%d%d", &n, &m);
	int t = 0;
	w[0] = m;
	for (int i = 1; i <= n; i ++ ){
		scanf("%d", &A[i]);
		w[i] = w[i - 1];
		if (A[i] * 2 - t > w[i]) w[i] = A[i] * 2 - t;
		t = A[i];
	}
	a[head].r = tail;
	a[tail].l = head;
	a[head].num = a[tail].num = - 1;
	a[head].rdis = a[tail].ldis = w[n] - t;
	for (int i = n; i >= 1; i -- ){
		if (rev == 0){
			if (2 * A[i] - A[i - 1] <= w[i - 1]){
				int copy = a[head].r, totl;
				a[head].num = 0;
				for (totl = 0; A[i] - totl > A[i - 1]; ){
					add_head(copy);
					totl += a[copy].ldis;
					copy = a[copy].r;
				}
				a[head].rdis -= totl - (A[i] - A[i - 1]);
				a[a[head].r].ldis -= totl - (A[i] - A[i - 1]);
				a[head].num = - 1;
			}
			else{
				int copy = a[head].r, totl;
				a[head].num = 1;
				for (totl = 0; totl < w[i - 1] - A[i]; ){
					add_head(copy);
					totl += a[copy].ldis;
					copy = a[copy].r;
				}
				a[head].rdis -= totl - (w[i - 1] - A[i]);
				a[a[head].r].ldis -= totl - (w[i - 1] - A[i]);
				a[head].num = - 1;
				rev = 1;
			}
		}
		else{
			if (2 * A[i] - A[i - 1] <= w[i - 1]){
				int copy = a[tail].l, totl;
				a[tail].num = 1;
				for (totl = 0; A[i] - totl > A[i - 1]; ){
					add_tail(copy);
					totl += a[copy].rdis;
					copy = a[copy].l;
				}
				a[tail].ldis -= totl - (A[i] - A[i - 1]);
				a[a[tail].l].rdis -= totl - (A[i] - A[i - 1]);
				a[tail].num = - 1;
			}
			else{
				
				int copy = a[tail].l, totl;
				a[tail].num = 0;
				for (totl = 0; totl < w[i - 1] - A[i]; ){
					add_tail(copy);
					totl += a[copy].rdis;
					copy = a[copy].l;
				}
				a[tail].ldis -= totl - (w[i - 1] - A[i]);
				a[a[tail].l].rdis -= totl - (w[i - 1] - A[i]);
				a[tail].num = - 1;
				rev = 0;
			}
		}
	}
	int ans = 0;
	for (int i = a[head].r; i != tail; i = a[i].r)
		ans ++ ;
	printf("%d\n", ans);
	if (rev){
		for (int i = a[tail].l, j = 0; i != head; i = a[i].l)
			printf("%d %d\n", j += a[i].rdis, a[i].num ^ 1);
	}
	else for (int i = a[head].r, j = 0; i != tail; i = a[i].r)
			printf("%d %d\n", j += a[i].ldis, a[i].num);
}
