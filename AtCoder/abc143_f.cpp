#include<cstdio>
#include<algorithm>
using std::min;
using std::max;
using std::distance;
using std::lower_bound;
using std::reverse;
using std::sort;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=300000+5;
const int MAXA=MAXN;

int n,Max;
int a[MAXN];
int T[MAXA];
int C[MAXA];
int C2[MAXA];

int main(void){
	reg int i,j;
	n=read();
	for(i=0;i<n;++i)
		a[i]=read();
	sort(a,a+n);
	for(i=0;i<n;++i){
		++T[a[i]-1];
		Max=max(Max,T[a[i]-1]);
	}
	for(i=0;i<n;++i)
		for(j=1;j<=T[i];++j)
			++C[j-1];
	for(i=1;i<Max;++i)
		C[i]+=C[i-1];
	for(i=1;i<=n;++i)
		C2[i-1]=C[min((int)i,Max)-1]/i;
	reverse(C2,C2+n);
	for(i=1;i<=n;++i)
		printf("%d\n",(int)(C2+n-lower_bound(C2,C2+n,(int)i)));
	return 0;
}
