#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

const int MAXN=18;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int w[MAXN][MAXN];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int s,d,l;
		s=read(),d=read(),l=read();
		w[s][d]=l;
	}
	return;
}

int f[1<<MAXN][MAXN];

inline void Work(void){
	memset(f,-0X7F,sizeof(f));
	f[1][0]=0;
	for(reg int i=1;i<(1<<n);++i)
		for(reg int j=0;j<n;++j){
			if((i>>j)&1){
				reg int res=i^(1<<j);
				for(reg int k=0;k<n;++k)
					if((res>>k)&1&&w[k][j])
						f[i][j]=max(f[i][j],f[res][k]+w[k][j]);
			}
		}
	int ans=0;
	for(reg int i=(1<<(n-1))+1;i<(1<<n);++i)
		ans=max(ans,f[i][n-1]);
	printf("%d\n",ans);
	return;
}
