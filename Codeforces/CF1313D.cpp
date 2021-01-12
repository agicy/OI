#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e5+5;
const int MAXK=8;
const int inf=0x3f3f3f3f;

struct Node{
	int pos,id;
	inline bool operator<(const Node& a)const{
		return pos==a.pos?id<a.id:pos<a.pos;
	}
};

int n,m,K,cnt;
Node A[MAXN<<1];
int f[1<<MAXK];
int add[1<<MAXK];
int vis[MAXK];

int main(void){
	n=read(),m=read(),K=read();
	for(reg int i=1,l,r;i<=n;++i){
		l=read(),r=read();
		A[++cnt].pos=l,A[cnt].id=i,A[++cnt].pos=r+1,A[cnt].id=-i;
	}
	sort(A+1,A+cnt+1);
	for(reg int i=1;i<(1<<K);++i){
		f[i]=-inf;
		add[i]=add[i>>1]^(i&1);
	}
	for(reg int i=1;i<cnt;++i){
		reg int len=A[i+1].pos-A[i].pos,k;
		if(A[i].id>0){
			for(reg int j=0;j<8;++j)
				if(!vis[j]){
					vis[j]=A[i].id,k=j;
					break;
				}
			for(reg int j=(1<<K)-1;j>=0;--j)
				if(j&(1<<k))
					f[j]=f[j^(1<<k)]+len*add[j];
				else
					f[j]+=len*add[j];
		}
		else{
			for(reg int j=0;j<8;++j)
				if(vis[j]==-A[i].id){
					vis[j]=0,k=j;
					break;
				}
			for(reg int j=0;j<(1<<K);++j)
				if(j&(1<<k))
					f[j]=-inf;
				else
					f[j]=max(f[j],f[j^(1<<k)])+len*add[j];
		}
	}
	reg int ans=0;
	for(reg int i=0;i<(1<<K);++i)
		ans=max(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}