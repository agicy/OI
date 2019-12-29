#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

const int MAXN=200000+5;

int n,m,Q;
char S[MAXN],T[MAXN];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	scanf("%d%d%d\n%s\n%s",&n,&m,&Q,S+1,T+1);
	return;
}

const ull base=131;

ull hashp[MAXN];
ull HashA[MAXN];
ull HashB[MAXN];
int cnt[MAXN];

inline ull GetHashA(reg int l,reg int r){
	return HashA[r]-HashA[l-1]*hashp[r-l+1];
}

inline ull GetHashB(reg int l,reg int r){
	return HashB[r]-HashB[l-1]*hashp[r-l+1];
}

inline void Work(void){
	hashp[0]=1;
	for(reg int i=1;i<=max(n,m);++i)
		hashp[i]=hashp[i-1]*base;
	for(reg int i=1;i<=n;++i)
		HashA[i]=HashA[i-1]*base+S[i];
	for(reg int i=1;i<=m;++i)
		HashB[i]=HashB[i-1]*base+T[i];
	for(reg int i=1;i<=n;++i){
		if(S[i]!=T[1]){
			++cnt[0];
			continue;
		}
		reg int l=1,r=min(n-i+1,m),mid;
		while(l<r){
			mid=(l+r+1)>>1;
			if(GetHashA(i,i+mid-1)==GetHashB(1,mid))
				l=mid;
			else
				r=mid-1;
		}
		++cnt[r];
	}
	while(Q--){
		static int x;
		scanf("%d",&x);
		printf("%d\n",cnt[x]);
	}
	return;
}
