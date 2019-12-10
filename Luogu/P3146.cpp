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

const int MAXN=248+5;
const int MAXNUMBER=40+5;

int n;
int a[MAXN];
int f[MAXN][MAXNUMBER];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

inline void Work(void){
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		f[i][a[i]]=i+1;
	for(reg int j=2;j<MAXNUMBER;++j)
		for(reg int i=1;i<=n;++i){
			if(!f[i][j])
				f[i][j]=f[f[i][j-1]][j-1];
			if(f[i][j]>0)
				ans=max((int)ans,(int)j);
		}
	printf("%d\n",ans);
	return;
}
