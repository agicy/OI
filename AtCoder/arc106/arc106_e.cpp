#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=18+1;
const int MAXP=(1<<18);
const int MAXSIZE=4e6+1;

int n,K;
int a[MAXN];
int f[MAXP],cnt[MAXP];
int b[MAXSIZE];
int p[MAXN];

inline bool check(reg int t){
	memset(f,0,sizeof(f));
	for(reg int i=1;i<=t;++i)
		++f[p[n]-1],--f[b[i]^(p[n]-1)];
	for(reg int i=1;i<=n;++i)
		for(reg int j=0;j<p[n];++j)
			if(j&p[i-1])
				f[j^p[i-1]]+=f[j];
	for(reg int i=0;i<p[n];++i)
		if(cnt[i]*K>f[i])
			return false;
	return true;
}

int main(void){
	n=read(),K=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	p[0]=1;
	for(reg int i=1;i<=n;++i)
		p[i]=p[i-1]*2;
	for(reg int i=1;i<p[n];++i)
		cnt[i]=cnt[i>>1]+(i&1);
	for(reg int i=1;i<MAXSIZE;++i)
		for(reg int j=1;j<=n;++j)
			if((i-1)%(a[j]*2)<a[j])
				b[i]|=p[j-1];
	reg int l=1,r=MAXSIZE-1,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(check(mid))
			r=mid;
		else
			l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}