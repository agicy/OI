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
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=200000+5;
const int MAXK=200000+5;

int n;
int k[4];
int a[4][MAXK];
int pre[4][MAXN];
int las[MAXN];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	for(reg int i=1;i<=3;++i)
		k[i]=read();
	for(reg int i=1;i<=3;++i)
		for(reg int j=1;j<=k[i];++j)
			a[i][j]=read();
	n=k[1]+k[2]+k[3];
	return;
}

inline void Work(void){
	for(reg int i=1;i<=3;++i)
		for(reg int j=1;j<=k[i];++j)
			++pre[i][a[i][j]];
	for(reg int i=1;i<=3;++i)
		for(reg int j=1;j<=n;++j)
			pre[i][j]+=pre[i][j-1];
	las[n]=pre[3][n]-pre[2][n];
	for(reg int i=n-1;i>=0;--i)
		las[i]=min(las[i+1],pre[3][i]-pre[2][i]);
	int ans=n;
	for(reg int i=0;i<=n;++i)
		ans=min(ans,pre[1][n]-pre[1][i]+pre[2][n]+pre[2][i]+las[i]);
	printf("%d\n",ans);
	return;
}
