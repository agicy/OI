#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXP=100+5;

struct Node{
	int h,t;
	ll s;
	inline bool operator<(const Node& a)const{
		return s<a.s;
	}
	inline void Read(void){
		h=read(),t=read();
		return;
	}
};

int n,m,p;
int Q[MAXN];
ll f[MAXN][MAXP],sum[MAXN],d[MAXN];
Node C[MAXN];

int main(void){
	n=read(),m=read(),p=read();
	for(reg int i=2;i<=n;++i){
		d[i]=read();
		d[i]+=d[i-1];
	}
	for(reg int i=1;i<=m;++i){
		C[i].Read();
		C[i].s=C[i].t-d[C[i].h];
	}
	sort(C+1,C+m+1);
	for(reg int i=1;i<=m;++i)
		sum[i]=sum[i-1]+C[i].s;
	memset(f,0X3F,sizeof(f));
	f[0][0]=0;
	for(reg int i=1;i<=p;++i){
		reg int head=1,tail=1;
		Q[head]=0;
		for(reg int j=1;j<=m;++j){
			while(head<tail&&f[Q[head]][i-1]+sum[Q[head]]-C[j].s*Q[head]>f[Q[head+1]][i-1]+sum[Q[head+1]]-C[j].s*Q[head+1])
				++head;
			f[j][i]=f[Q[head]][i-1]+C[j].s*(j-Q[head])-(sum[j]-sum[Q[head]]);
			while(tail>head&&(f[j][i-1]+sum[j]-f[Q[tail]][i-1]-sum[Q[tail]])*(Q[tail]-Q[tail-1]) <(f[Q[tail]][i-1]+sum[Q[tail]]-f[Q[tail-1]][i-1]-sum[Q[tail-1]])*(j-Q[tail]))
				--tail;
			Q[++tail]=j;
		}
	}
	printf("%lld\n",f[m][p]);
	return 0;
}