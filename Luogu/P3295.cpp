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
const int MAXLOG2N=17+1;
const int p=1e9+7;

int n,m;
int f[MAXLOG2N][MAXN];

inline int find(reg int x,reg int y){
	if(f[y][x]!=x)
		f[y][x]=find(f[y][x],y);
	return f[y][x];
}

inline void merge(reg int x,reg int y,reg int len){
	if(find(x,len)!=find(y,len))
		f[len][f[len][x]]=f[len][y];
	return;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%p;
		x=1ll*x*x%p;
		exp>>=1;
	}
	return res;
}

int main(void){
	n=read(),m=read();
	for(reg int j=0;j<MAXLOG2N;++j)
		for(reg int i=1;i<=n;++i)
			f[j][i]=i;
	for(reg int i=1;i<=m;++i){
		static int l1,r1,l2;
		l1=read(),r1=read(),l2=read(),read();
		for(reg int j=MAXLOG2N-1;j>=0;--j)
			if(l1+(1<<j)-1<=r1){
				merge(l1,l2,j);
				l1+=(1<<j),l2+=(1<<j);
			}
	}
	for(reg int j=MAXLOG2N-1;j>=1;--j)
		for(reg int i=1;i+(1<<j)-1<=n;++i){
			merge(i,find(i,j),j-1);
			merge(i+(1<<(j-1)),f[j][i]+(1<<(j-1)),j-1);
		}
	reg int cnt=0;
	for(reg int i=1;i<=n;++i)
		if(find(i,0)==i)
			++cnt;
	printf("%lld\n",9ll*fpow(10,cnt-1)%p);
	return 0;
}