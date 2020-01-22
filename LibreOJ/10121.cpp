#include<cstdio>
#include<algorithm>
using std::min;
using std::max;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool flag=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)flag|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return flag?-res:res;
}

const int MAXN=2000000+5;
const int MAXLOG2N=21+1;
const int MAXABSA=1000000;
const int MAXA=1000000+5;

struct ST{
	int log[MAXN];
	int pre[MAXA<<1];
	int f[MAXN][MAXLOG2N];
	inline void Init(reg int n,int a[]){
		reg int i,j;
		log[0]=-1;
		for(i=1;i<=n;++i)
			log[i]=log[i>>1]+1;
		for(i=1;i<=n;++i){
			f[i][0]=min(i-pre[a[i]],f[i-1][0]+1);
			pre[a[i]]=i;
		}
		for(j=1;j<MAXLOG2N;++j)
			for(i=1;i+(1<<j)-1<=n;++i)
				f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
		return;
	}
	inline int Query(reg int l,reg int r){
		if(l>r)
			return 0;
		reg int k=log[r-l+1];
		return max(f[l][k],f[r-(1<<k)+1][k]);
	}
};

int n,m;
int a[MAXN];
ST T;

int main(void){
	reg int i,l,r,mid,L,R,loc;
	n=read(),m=read();
	for(i=1;i<=n;++i)
		a[i]=read()+MAXABSA;
	T.Init(n,a);
	while(m--){
		L=l=read()+1,R=r=read()+1;
		loc=r+1;
		while(l<=r){
			mid=(l+r)>>1;
			if(mid-T.f[mid][0]+1<=L)
				l=mid+1;
			else
				loc=mid,r=mid-1;
		}
		printf("%d\n",max(loc-L,T.Query(loc,R)));
	}
	return 0;
}
