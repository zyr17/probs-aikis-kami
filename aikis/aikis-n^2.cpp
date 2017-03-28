#include <cstdio>
#include <cstring>
#include <ctime>
#define N 1111111
#define AddEdge(x,y) num[tail[x] = next[tail[x]] = ++ tot] = y; 
#define Init freopen("aikis.in","r",stdin);freopen("aikis.out","w",stdout);
int n,m,a[N],tail[N],next[N],num[N],l[N],edge1[N],edge2[N],tot,atkr[N],atkf[N],fa[N],hp[N],posatkf[N],m1,m2,q;
char chread(){
	char ch;
	for (; (ch = getchar()) < 33; );
	return ch;
}
int main(){
	Init;
	scanf("%d", &n);
	for (tot = 1; tot <= n; tot ++ )
		tail[tot] = tot;
	for (int i = 1; i < n; i ++ ){
		scanf("%d%d", &edge1[i], &edge2[i]);
		AddEdge(edge1[i], edge2[i]);
		AddEdge(edge2[i], edge1[i]);
	}
	scanf("%d", &m1);
	for (; m1 -- ; ){
		int t1, t2;
		scanf("%d%d", &t1, &t2);
		atkf[t1] = posatkf[t1] = t2;
	}
	for (int i = 1; i < n; i ++ ){
		atkf[edge1[i]] += posatkf[edge2[i]];
		atkf[edge2[i]] += posatkf[edge1[i]];
	}
	scanf("%d", &m2);
	for (; m2 -- ; ){
		int t1, t2, t3;
		scanf("%d%d%d", &t1, &t2, &t3);
		atkr[t1] = t2;
		hp[t1] = t3;
	}
	scanf("%d", &q);
	for (; q -- ; ){
		if (chread() == 'A'){
			int t1, t2, t3;
			scanf("%d%d%d", &t1, &t2, &t3);
			atkr[t1] = t2;
			hp[t1] = t3;
		}
		else{
			memset(fa, 0, sizeof fa);
			int t1, t2, t3;
			scanf("%d%d%d", &t1, &t2, &t3);
			int t = 1, w = 1;
			l[1] = t2;
			fa[t2] = t2;
			for (; t <= w; t ++ )
				for (int i = next[l[t]]; i; i = next[i])
					if (!fa[num[i]])
						fa[l[ ++ w] = num[i]] = l[t];
			fa[t2] = 0;
			int tot = 0;
			for (int i = t1; i; i = fa[i]){//printf("%d %d\n", i, tot);
				if (hp[i]){
					if (hp[i] * (atkf[i] + atkr[i]) + tot >= t3){
						printf("Kill %d\n", i);
						hp[i] -= (t3 - tot - 1) / (atkf[i] + atkr[i]) + 1;
						goto End;
					}
					else{
						tot += hp[i] * (atkf[i] + atkr[i]);
						hp[i] = 0;
					}
				}
				else if (tot + atkf[i] >= t3){
					printf("Kill %d\n", i);
					goto End;
				}
				else tot += atkf[i];
			}
			printf("Fail %d\n", t3 - tot);
			End:;
		}
	}
}
