#include <cstdio>
#include <cstring>
#define Init freopen("kami.in","r",stdin);freopen("kami.out","w",stdout);
int n,m,ans,a[1111111];
int main(){
	Init;
	scanf("%d%d", &n, &m);
	memset(a, 255, sizeof a);
	int t = 0, w = m;
	int pos_0 = 0, rev = 1;
	for (int i = 1; i <= n; i ++ ){
		int t1;
		scanf("%d", &t1);
		int now = pos_0, dd = rev;
		for (int j = 1; j < m; j ++ ){
			now += dd;//if (~a[j]) printf("[%d %d] ",j,now);
			if (~a[j]) dd *= - 1;
			if (!~a[j] && now == t1) a[j] = (dd == 1 ? 0 : 1);
		}//printf("[%d %d]\n",m,now + dd);
		if (pos_0 < t1){
			pos_0 = t1 * 2 - pos_0;
			rev *= - 1;
		}
		else if (pos_0 == t1 && rev == - 1)
			rev = 1;
	}
	/*
	int now = pos_0, dd = rev;
	for (int j = 1; j < m; j ++ ){
		now += dd;if (~a[j]) printf("[%d %d] ",j,now);
		if (~a[j]) dd *= - 1;
		//if (!~a[j] && now == t1) a[j] = (dd == 1 ? 0 : 1);
	}printf("[%d %d]\n",m,now + dd);
	*/
	for (int i = 1; i < m; i ++ )
		if (~a[i]) ans ++ ;
	printf("%d\n", ans);
	for (int i = 1; i < m; i ++ )
		if (~a[i]) printf("%d %d\n", i, a[i]);
}
