#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=50+5;
const int MAXM=50+5;

int n;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Init(void){
	cnt=0;
	memset(head,0,sizeof(head));
	return;
}

ull S[MAXM][MAXN];

const ull base=1331;

inline ull GetHash(reg int ID,reg int father){
	ull q[MAXN];
	reg int top=0;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father)
			q[++top]=GetHash(to[i],ID);
	sort(q+1,q+top+1);
	reg ull res=0;
	for(reg int i=1;i<=top;++i)
		res=res*base+q[i];
	res=res*base+MAXN+1;
	return res;
}

int main(void){
	reg int m=read();
	for(reg int t=1;t<=m;++t){
		Init();
		n=read();
		for(reg int i=1;i<=n;++i){
			static int fa;
			fa=read();
			if(fa){
				Add_Edge(fa,i);
				Add_Edge(i,fa);
			}
		}
		for(reg int i=1;i<=n;++i)
			S[t][i]=GetHash(i,0);
		sort(S[t]+1,S[t]+n+1);
		for(reg int i=1,j=0;i<=t;++i){
			while(j<=n){
				++j;
				if(S[t][j]!=S[i][j])
					break;
			}
			if(j>n){
				printf("%d\n",i);
				break;
			}
		}
	}
	return 0;
}