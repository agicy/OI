#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

const int MAXA=100+5;
const int MAXN=1000+5;
const int MAXM=1000+5;
const int MAXB=1000+5;

const ull base1=131;
const ull base2=1331;

int m,n,A,B,Q;
ull base1p[MAXM],base2p[MAXN];
ull Hash_A[MAXM][MAXN],Hash_B[MAXA][MAXB];

inline void Read(void);
inline void Init(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int cnt;
ull val[MAXN*MAXM];

inline void Init(void){
	base1p[0]=base2p[0]=1;
	for(reg int i=1,len=max(n,m);i<=len;++i)
		base1p[i]=base1p[i-1]*base1,base2p[i]=base2p[i-1]*base2;
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;j<=n;++j)
			Hash_A[i][j]=Hash_A[i][j-1]*base1+Hash_A[i][j];
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;j<=n;++j)
			Hash_A[i][j]=Hash_A[i-1][j]*base2+Hash_A[i][j];
	for(reg int i=A;i<=m;++i)
		for(reg int j=B;j<=n;++j)
			val[++cnt]=Hash_A[i][j]-Hash_A[i-A][j]*base2p[A]-Hash_A[i][j-B]*base1p[B]+Hash_A[i-A][j-B]*base1p[B]*base2p[A];
	return;
}

inline void Read(void){
	scanf("%d%d%d%d",&m,&n,&A,&B);
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;j<=n;++j)
			scanf("%1llu",&Hash_A[i][j]);
	return;
}

inline void Work(void){
	Init();
	scanf("%d",&Q);
	while(Q--){
		for(reg int i=1;i<=A;++i)
			for(reg int j=1;j<=B;++j)
				scanf("%1llu",&Hash_B[i][j]);
		for(reg int i=1;i<=A;++i)
			for(reg int j=1;j<=B;++j)
				Hash_B[i][j]=Hash_B[i][j-1]*base1+Hash_B[i][j];
		for(reg int i=1;i<=A;++i)
			for(reg int j=1;j<=B;++j)
				Hash_B[i][j]=Hash_B[i-1][j]*base2+Hash_B[i][j];
		reg bool flag=false;
		for(reg int i=1;i<=cnt;++i)
			if(val[i]==Hash_B[A][B]){
				flag=true;
				break;
			}
		puts(flag?"1":"0");
	}
	return;
}
