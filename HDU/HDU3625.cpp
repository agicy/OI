#include<cstdio>
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

const int MAXN=20+5;

ll fac[MAXN],S[MAXN][MAXN];

inline void Init(reg int n){
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=fac[i-1]*i;
	S[0][0]=1;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=i;++j)
			S[i][j]=S[i-1][j-1]+(i-1)*S[i-1][j];
	return;
}

int n,k;

int main(void){
	Init(20);
	reg int T=read();
	while(T--){
		n=read(),k=read();
		reg ll cnt=0;
		for(reg int i=1;i<=k;++i)
			cnt+=S[n][i]-S[n-1][i-1];
		printf("%.4lf\n",1.0*cnt/fac[n]);
	}
	return 0;
}