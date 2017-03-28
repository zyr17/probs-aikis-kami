#include <cstdio>
#include <cstring>
#include <ctime>
#define N 1111111
#define AddEdge(x,y) num[tail[x] = next[tail[x]] = ++ tot] = y;
#define swap(A,B) {int TMp = A;A = B;B = TMp;}
#define abs(A) (((A)>0)?(A):(-(A)))
#define Init freopen("aikis.in","r",stdin);freopen("aikis.out","w",stdout);
int n,m,tail[N],next[N],num[N],edge1[N],edge2[N],tot,atkr[N],atkf[N],hp[N],posatkf[N],m1,m2,q,PP,total_length;
int dep[N],fa[N][22],sonmax[N],sum[N],son[N],topoi[N],totree[N],ttot,tfa[N],totl,depth[N],lista[N],listb[N],tla[N],tlb[N];
int tree1[N * 4],tree2[N * 4],zero[N * 4];
int dfs_son(int k){
    dep[k] = dep[fa[k][0]] + 1;
    for (int j = next[k]; j; j = next[j]){
    	int J = num[j];
        if (!dep[J]){
            fa[J][0] = k;
            int tmp = dfs_son(J);
            if (sonmax[k] < tmp){
                sonmax[k] = tmp;
                son[k] = J;
            }
            sum[k] += tmp;
        }
    }
    return ++ sum[k];
}
int dfs_make(int k){
	depth[k] = depth[fa[k][0]] + 1;
	topoi[totree[k] = ++ ttot] = k;
	if (son[fa[k][0]] == k) tfa[k] = tfa[fa[k][0]];
	else tfa[k] = k;
	if (son[k]) dfs_make(son[k]);
	for (int i = next[k]; i; i = next[i])
		if (num[i] != son[k] && !totree[num[i]]) dfs_make(num[i]);
}
void ini(int now, int l, int r){
	if (l == r){
		int P = topoi[l];
		tree1[now] = atkf[P];
		if (hp[P])
			tree2[now] = (atkf[P] + atkr[P]) * hp[P] - atkf[P];
		return;
	}
	int p = (l + r) / 2;
	ini(now * 2, l, p);
	ini(now * 2 + 1, p + 1, r);
	tree1[now] = tree1[now * 2] + tree1[now * 2 + 1];
	tree2[now] = tree2[now * 2] + tree2[now * 2 + 1];
}
void change(int now, int l, int r, int x){
	if (l == r){
		zero[now] = 0;
		tree2[now] = (atkf[PP] + atkr[PP]) * hp[PP] - atkf[PP];
		if (!hp[PP]) tree2[now] = 0;
		return;
	}
	if (zero[now]){
		zero[now * 2] = zero[now * 2 + 1] = 1;
		zero[now] = 0;
	}
	int p = (l + r) / 2;
	if (x > p) change(now * 2 + 1, p + 1, r, x);
	else change(now * 2, l, p, x);
	tree2[now] = tree2[now * 2] * (zero[now * 2] ^ 1) + tree2[now * 2 + 1] * (zero[now * 2 + 1] ^ 1);
}
int lca(int x, int y){
	for (int i = 19; i >= 0; i -- )
		if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	for (int i = 19; i >= 0; i -- )
		if (dep[fa[y][i]] >= dep[x]) y = fa[y][i];
	if (x == y) return x;
	for (int i = 19; i >= 0; i -- )
		if (fa[x][i] != fa[y][i]){
			x = fa[x][i];
			y = fa[y][i];
		}
	return fa[x][0];
}
void make_list(int x, int y){
	int LCA = lca(x, y);
	int tot2 = 0;total_length += depth[x] + depth[y] - depth[LCA] * 2;
	totl = 0;
	for (;;){
		int FA = tfa[x];
		if (depth[FA] < depth[LCA]) FA = LCA;
		lista[ ++ totl] = x;
		listb[totl] = FA;
		x = fa[FA][0];
		if (depth[x] < depth[LCA]) break;
	}
	for (;;){
		int FA = tfa[y];
		if (depth[FA] < depth[LCA]) FA = LCA;
		tlb[ ++ tot2] = y;
		tla[tot2] = FA;
		y = fa[FA][0];
		if (depth[y] < depth[LCA]) break;
	}
	if (lista[totl] == listb[totl] && lista[totl] == tla[tot2]) totl -- ;
	if (tla[tot2] == tlb[tot2] && tlb[tot2] == listb[totl]) tot2 -- ;
	for (; tot2; tot2 -- ){
		lista[ ++ totl] = tla[tot2];
		listb[totl] = tlb[tot2];
	}
	for (int i = 1; i <= totl; i ++ ){
		lista[i] = totree[lista[i]];
		listb[i] = totree[listb[i]];
	}
}
int total(int now, int l, int r, int x, int y){
	if (x > y) swap(x, y);
	if (l == x && r == y) return tree1[now] + tree2[now] * (zero[now] ^ 1);
	if (zero[now]){
		tree2[now] = 0;
		zero[now] = 0;
		zero[now * 2] = zero[now * 2 + 1] = 1;
	}
	int p = (l + r) / 2;
	if (y <= p) return total(now * 2, l, p, x, y);
	else if (x > p) return total(now * 2 + 1, p + 1, r, x, y);
	else return total(now * 2, l, p, x, p) + total(now * 2 + 1, p + 1, r, p + 1, y);
}
void fill_zero(int now, int l, int r, int x, int y){
	if (x > y) swap(x, y);
	if (l == x && r == y){
		zero[now] = 1;
		return;
	}
	if (zero[now]) return;
	int p = (l + r) / 2;
	if (y <= p) fill_zero(now * 2, l, p, x, y);
	else if (x > p) fill_zero(now * 2 + 1, p + 1, r, x, y);
	else{
		fill_zero(now * 2, l, p, x, p);
		fill_zero(now * 2 + 1, p + 1, r, p + 1, y);
	}
	tree2[now] = tree2[now * 2] * (zero[now * 2] ^ 1) + tree2[now * 2 + 1] * (zero[now * 2 + 1] ^ 1);
}
void update(int now, int l, int r, int k){
	if (l == r){
		if (zero[now]){
			zero[now] = 0;
			k = topoi[k];
			hp[k] = atkr[k] = 0;
		}
		return;
	}
	if (zero[now]){
		zero[now] = 0;
		zero[now * 2] = zero[now * 2 + 1] = 1;
	}
	int p = (l + r) / 2;
	if (k <= p) update(now * 2, l, p, k);
	else update(now * 2 + 1, p + 1, r, k);
	tree2[now] = tree2[now * 2] * (zero[now * 2] ^ 1) + tree2[now * 2 + 1] * (zero[now * 2 + 1] ^ 1);
}
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
	dfs_son(1);
	dfs_make(1);
	ini(1, 1, n);
	for (int i = 1; i < 20; i ++ )
		for (int j = 1; j <= n; j ++ )
			fa[j][i] = fa[fa[j][i - 1]][i - 1];
	scanf("%d", &q);
	for (; q -- ; ){
		if (chread() == 'A'){
			int t1,t2,t3;
			scanf("%d%d%d", &t1, &t2, &t3);
			hp[t1] = t3;
			atkr[t1] = t2;
			change(1, 1, n, totree[PP = t1]);
		}
		else{
			int t1,t2,t3;
			scanf("%d%d%d", &t1, &t2, &t3);
			make_list(t1, t2);
			int damage = 0;
			for (int i = 1; i <= totl; i ++ ){
				int tmp = total(1, 1, n, lista[i], listb[i]);
				if (damage + tmp >= t3){
					int l = lista[i] - 1, r = listb[i];
					if (lista[i] > listb[i]) l = lista[i] + 1;
					for (; abs(r - l) > 1; ){
						int p = (l + r) / 2;
						int tt = total(1, 1, n, lista[i], p);
						if (tt + damage >= t3) r = p;
						else l = p;
					}
					printf("Kill %d\n", topoi[r]);
					t3 -= damage;
					if (l >= lista[i] && l <= listb[i] || l <= lista[i] && l >= listb[i]){
						t3 -= total(1, 1, n, lista[i], l);
						fill_zero(1, 1, n, lista[i], l);
					}
					update(1, 1, n, r);
					if (hp[topoi[r]]) hp[topoi[r]] -= (t3 - 1) / (atkf[topoi[r]] + atkr[topoi[r]]) + 1;
					if (!hp[topoi[r]]) atkr[topoi[r]] = 0;
					PP = topoi[r];
					change(1, 1, n, r);
					goto QEnd;
				}
				damage += tmp;
				fill_zero(1, 1, n, lista[i], listb[i]);
			}
			printf("Fail %d\n", t3 - damage);
			QEnd:;
		}
	}
}

