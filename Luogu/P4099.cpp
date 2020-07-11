#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define MOD 1000000007

const int MAXN=1000+5;

inline void Read(void);
inline void Work(void);

int C[MAXN][MAXN];

int main(void){
	C[0][0]=1;
	for(reg int i=1;i<=1000;++i){
		C[i][0]=1;
		for(reg int j=1;j<=i;++j)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
	}
	int T;
	scanf("%d",&T);
	while(T--){
		Read();
		Work();
	}
	return 0;
}

int n;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Read(void){
	cnt=0;
	memset(head,0,sizeof(head));
	scanf("%d",&n);
	for(reg int i=1;i<n;++i){
		static int a,b;
		static char ch;
		scanf("%d %c %d",&a,&ch,&b);
		++a,++b;
		Add_Edge(a,b,ch=='<');
		Add_Edge(b,a,ch=='>');
	}
	return;
}

int size[MAXN];
int f[MAXN][MAXN];
int g[MAXN];

inline void DFS(reg int ID,reg int father){
	size[ID]=1;
	f[ID][1]=1;
	for(reg int i=head[ID];i;i=Next[i]){
		if(to[i]!=father){
			DFS(to[i],ID);
			memcpy(g,f[ID],sizeof(f[ID]));
			memset(f[ID],0,sizeof(f[ID]));
			if(w[i]==1)
				for(reg int j=1;j<=size[ID];++j)
					for(reg int k=j;k<j+size[to[i]];++k)
						f[ID][k]=(f[ID][k]+1ll*C[size[ID]+size[to[i]]-k][size[ID]-j]*C[k-1][j-1]%MOD*g[j]%MOD*(f[to[i]][size[to[i]]]-f[to[i]][k-j]+MOD))%MOD;
			else
				for(reg int j=1;j<=size[ID];++j)
					for(reg int k=j+1;k<=j+size[to[i]];++k)
						f[ID][k]=(f[ID][k]+1ll*C[size[ID]+size[to[i]]-k][size[ID]-j]*C[k-1][j-1]%MOD*g[j]%MOD*f[to[i]][k-j])%MOD;
			size[ID]+=size[to[i]];
		}
	}
	for(reg int i=1;i<=size[ID];++i)
		f[ID][i]=(f[ID][i]+f[ID][i-1])%MOD;
	return;
}

inline void Work(void){
	DFS(1,0);
	printf("%d\n",f[1][n]);
	return;
}
