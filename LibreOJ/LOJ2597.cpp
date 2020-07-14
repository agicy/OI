#include<cstdio>
#include<algorithm>
using std::min;
using std::max;
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

const int MAXN=2000000+5;
const int MAXK=10000+5;

int n,k,p;
int C[MAXN];
int T[MAXK];

int main(void){
	reg int i,l=0;
	reg ll ans=0;
	n=read(),k=read(),p=read();
	for(i=1;i<=n;++i){
		static int P;
		C[i]=read(),P=read();
		if(P<=p){
			while(l<i)
				++T[C[++l]];
			ans+=T[C[i]]-1;
		}
		else
			ans+=T[C[i]];
	}
	printf("%lld\n",ans);
	return 0;
}
