#include <cstdio>
#include <list>
#include <ctime>
#define N 111111
#define Init freopen("kami.in","r",stdin);freopen("kami.out","w",stdout);
std::list<int> pos,zf;
int n,m,a[N];
int main(){
	Init;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++ )
		scanf("%d", &a[i]);
	int t = 0, w = m;
	for (int i = 1; i <= n; i ++ ){
		if (a[i] * 2 - t > w) w = a[i] * 2 - t;
		t = a[i];
	}
	for (int i = n; i >= 1; i -- ){
		pos.push_front(a[i]);
		zf.push_front(0);
		std::list<int>::iterator j = pos.begin(), k = zf.begin();
		int max = a[i] * 2 - a[i - 1];
		for (j ++ , k ++ ; j != pos.end() && *j < max; j ++ , k ++ ){
			pos.push_front(a[i] * 2 - *j);
			zf.push_front(1 - *k);
		}
		//for (; *( -- pos.end()) > *pos.begin() + m; pos.pop_back(), zf.pop_back());
		/*
		//printf("%d:\n", n + 1 - i);
		for (std::list<int>::iterator ii = pos.begin(), j = zf.begin(); ii != pos.end() && *ii <= a[i]; ii ++ , j ++ )
			printf("%d %d\n", *ii, *j);
		*/
	}
	//printf("-%d-%d\n", clock(),pos.size());
	for (; *( -- pos.end()) >= m; pos.pop_back(), zf.pop_back());
	printf("%d\n", pos.size());
	//for (; *pos.begin() != *pos.end(); pos.pop_front(), zf.pop_front())
	//	printf("%d %d\n", *pos.begin(), *zf.begin());
	for (std::list<int>::iterator i = pos.begin(), j = zf.begin(); i != pos.end(); i ++ , j ++ )
		printf("%d %d\n", *i, *j);
	//printf("-%d-\n", clock());
}
