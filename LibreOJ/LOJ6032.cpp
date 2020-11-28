#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+5;
const int MAXM=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	int T=read();
	while(T--){
		Read();
		Work();
	}
	return 0;
}

struct Updates{
	int i,y,k;
	inline bool operator<(const Updates& a)const{
		return y==a.y?k<a.k:y<a.y;
	}
};

struct UnionFind{
	int ID[MAXN+MAXM];
	inline void Init(reg int size){
		for(reg int i=1;i<=size;++i)
			ID[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==ID[x])
			return x;
		else
			return ID[x]=find(ID[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			ID[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
};

int n,m;
Updates U[MAXN+MAXM];
UnionFind S;
int dp[2][MAXN+MAXM];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<n;++i){
		U[i+m].i=i;
		U[i+m].y=read();
		U[i+m].k=-1;
	}
	for(reg int i=1;i<=m;++i){
		U[i].i=read();
		U[i].y=read();
		U[i].k=read();
	}
	return;
}

inline void Work(void){
	S.Init(n+m);
	sort(U+1,U+n+m);
	memset(dp,0,sizeof(dp));
	for(reg int i=1;i<=n+m-1;++i){
		switch(U[i].k){
			case -1:{
				reg int ra=S.find(U[i].i+1);
				reg int rb=S.find(U[i].i);
				dp[0][rb]+=dp[0][ra],dp[1][rb]+=dp[1][ra];
				S.ID[ra]=rb;
				break;
			}
			case 0:++dp[0][S.find(U[i].i)];break;
			case 1:++dp[1][S.find(U[i].i)];dp[0][S.find(U[i].i)]=max(dp[0][S.find(U[i].i)],dp[1][S.find(U[i].i)]);break;
			default:break;
		}
	}
	printf("%d\n",dp[0][S.find(1)]);
	return;
}