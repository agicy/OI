#include<cstdio>
#include<cmath>
#include<algorithm>
using std::max;
#include<map>
using std::map;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1000+5;
const int MAXV=10000000+5;

int n,k;
int cnt,P[MAXV];
map<int,int> M;

int main(void){
	reg int i,j,sqr,ans=0;
	n=read(),k=read();
	for(i=1;i<=n;++i){
		static int v;
		v=read();
		for(j=1;j*j<=v;++j){
			if(v%j==0){
				if(!M[(int)j])
					P[++cnt]=j;
				++M[(int)j];
				if(!M[v/j])
					P[++cnt]=v/j;
				++M[v/j];
			}
		}
		sqr=(int)floor(sqrt(v));
		if(fabs(floor(sqrt(v))-ceil(sqrt(v)))<1e-6)
			--M[(int)sqr];
	}
	for(i=1;i<=cnt;++i)
		if(M[P[i]]>=k)
			ans=max((int)ans,P[i]);
	printf("%d\n",ans);
	return 0;
}
