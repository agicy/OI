#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

const int MAXN=100000+5;
const int MAXS=3000000+5;
const int MAXT=5000000+5;

const ull base1=131;
const ull base2=1331;

int n,m;
ull hash1p[MAXS],hash2p[MAXS];

inline void Init(void){
	hash1p[0]=hash2p[0]=1;
	for(reg int i=1;i<MAXS;++i){
		hash1p[i]=hash1p[i-1]*base1;
		hash2p[i]=hash2p[i-1]*base2;
	}
	return;
}

inline void Read(void);
inline void Work(void);

int main(void){
	Init();
	Read();
	Work();
	return 0;
}

vector<ull> Hash1[MAXN],Hash2[MAXN];
char str[MAXS];

inline void GetHash(reg int x,reg char str[]){
	reg int len=strlen(str+1);
	Hash1[x].push_back(0),Hash2[x].push_back(0);
	for(reg int i=1;i<=len;++i){
		Hash1[x].push_back(Hash1[x][i-1]*base1+str[i]-'a'+1);
		Hash2[x].push_back(Hash2[x][i-1]*base2+str[i]-'a'+1);
	}
	return;
}

inline void Read(void){
	scanf("%d%d\n",&n,&m);
	for(reg int i=1;i<=n;++i){
		scanf("%s\n",str+1);
		GetHash(i,str);
	}
	return;
}

inline ull GetHashVal1(reg int i,reg int l,reg int r){
	return Hash1[i][r]-Hash1[i][l-1]*hash1p[r-l+1];
}

inline ull GetHashVal2(reg int i,reg int l,reg int r){
	return Hash2[i][r]-Hash2[i][l-1]*hash2p[r-l+1];
}

char T[MAXT];
int a[MAXN];

inline void Work(void){
	for(reg int i=1;i<=m;++i){
		scanf("%s\n",T+1);
		reg ull Hash1=0,Hash2=0;
		reg int len=strlen(T+1);
		for(reg int j=1;j<=len;++j){
			Hash1=Hash1*base1+T[j]-'a'+1,
			Hash2=Hash2*base2+T[j]-'a'+1;
		}
		memset(a,false,sizeof(a));
		for(reg int j=1;j<=n;++j)
			if((GetHashVal1(j,1,len)==Hash1)&&(GetHashVal2(j,1,len)==Hash2))
				a[j]=true;
			else
				a[j]=false;
		reg int ans=0,lastone=0;
		for(reg int j=1;j<=n;++j)
			if(a[j]==1)
				lastone=j;
			else
				ans=max((int)ans,j-lastone);
		printf("%d\n",ans);
	}
	return;
}
