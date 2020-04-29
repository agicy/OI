#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 998244353

const int MAXN=5000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
	Read();
	Work();
	fclose(stdin);
	fclose(stdout);
	return 0;
}

int n,m;
char str[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Read(void){
	scanf("%d%s",&n,str+1);
	m=(n>>1);
	for(reg int i=1;i<n;++i){
		static int u,v;
		scanf("%d%d",&u,&v);
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	return;
}

int cnt0[MAXN],cnt1[MAXN],size[MAXN];
int dp[MAXN][MAXN];
int tmp[MAXN<<1];

inline void DFS(reg int ID,reg int father){
	dp[ID][0]=1;
	size[ID]=1;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DFS(to[i],ID);
			for(reg int j=0;j<=size[ID]+size[to[i]];++j)
				tmp[j]=0;
			for(reg int j=0;j<=size[ID];++j)
				for(reg int k=0;k<=size[to[i]];++k)
					tmp[j+k]=(tmp[j+k]+(ll)dp[ID][j]*dp[to[i]][k]%MOD)%MOD;
			size[ID]+=size[to[i]];
			cnt0[ID]+=cnt0[to[i]];
			cnt1[ID]+=cnt1[to[i]];
			for(reg int j=0;j<=size[ID];++j)
				dp[ID][j]=tmp[j];
		}
	if(str[ID]=='0'){
		++cnt0[ID];
		for(reg int i=cnt1[ID]-1;i>=0;--i)
			dp[ID][i+1]=(dp[ID][i+1]+(ll)dp[ID][i]*(cnt1[ID]-i)%MOD)%MOD;
	}
	if(str[ID]=='1'){
		++cnt1[ID];
		for(reg int i=cnt0[ID]-1;i>=0;--i)
			dp[ID][i+1]=(dp[ID][i+1]+(ll)dp[ID][i]*(cnt0[ID]-i)%MOD)%MOD;
	}
	return;
}

int fac[MAXN];
int C[MAXN][MAXN],A[MAXN],B[MAXN];

inline void Transfer(reg int A[],reg int B[],reg int m){
	for(reg int i=0;i<=m;++i)
		for(reg int d=i;d<=m;++d)
			if((d-i)&1)
				B[i]=(B[i]-(ll)C[d][i]*A[d]%MOD+MOD)%MOD;
			else
				B[i]=(B[i]+(ll)C[d][i]*A[d]%MOD)%MOD;
	return;
}

inline void Work(void){
	DFS(1,0);
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=(ll)fac[i-1]*i%MOD;
	C[0][0]=1;
	for(reg int i=1;i<=n;++i){
		C[i][0]=C[i][i]=1;
		for(reg int j=1;j<i;++j)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
	}
	for(reg int i=0;i<=m;++i)
		A[i]=(ll)dp[1][i]*fac[m-i]%MOD;
	memset(B,0,sizeof(B));
	Transfer(A,B,m);
	for(reg int i=0;i<=m;++i)
		printf("%d%c",B[i],i==m?'\n':' ');
	return;
}
