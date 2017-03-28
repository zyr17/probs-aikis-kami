#include <ctime>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define R ((rand() % p + 1) / 10.0)
int a[333333], s[333];
int main(){
	freopen("t.in","w",stdout);
	for (int i = 1; i <= 1000000; i ++ );
	srand(unsigned(time(NULL) + clock() * 10));
	
	
	
	int n = 100000, m = 1000000, p = 5, t = 0, w = m, max = 15;
	printf("%d %d\n", n, m);
	for (; n -- ; ){
		int out = (rand() * 65536 + rand()) % (max) + t + 1;
		if (n > 900) out = w - 1 - (rand() * 65536 + rand()) % (max);
		out = rand() % p + t + 1;
		if (rand() % max) out = t + 1;
		if (n > 99000) out = w - 1 - rand() % p;
		printf("%d\n", out);
		if (out * 2 - t > w) w = out * 2 - t;
		t = out;
	}
}
