#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

const int MAXN=1e5+5;
const int MAXM=1e5+5;

const ull base=131;
ull basep[MAXN];
ull Hash[MAXN];

inline void Init(reg int n,reg char s[]){
	basep[0]=1;
	for(reg int i=1;i<=n;++i)
		basep[i]=basep[i-1]*base;
	for(reg int i=1;i<=n;++i)
		Hash[i]=Hash[i-1]*base+(s[i]-'0'+1);
	return;
}

inline ull getHash(reg int l,reg int r){
	return Hash[r]-Hash[l-1]*basep[r-l+1];
}

int n,m;
char s[MAXN];

int main(void){
	scanf("%d%d%s",&n,&m,s+1);
	Init(n,s);
	while(m--){
		static int l1,r1,l2,r2;
		scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
		if(getHash(l1,r1)==getHash(l2,r2))
			puts("Yes");
		else
			puts("No");
	}
	return 0;
}