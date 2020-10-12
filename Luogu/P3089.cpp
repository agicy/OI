#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline void cMax(reg int& a,reg int b){
	if(a<b)
		a=b;
	return;
}

const int MAXN=1e3+5;

struct Node{
	int x,p;
	inline void Read(void){
		x=read(),p=read();
		return;
	}
	inline bool operator<(const Node& a)const{
		return x<a.x;
	}
};

int n;
Node a[MAXN];
int f[MAXN][MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i].Read();
	sort(a+1,a+n+1);
	int ans=0;
	for(reg int j=1;j<=n;++j){
		int val=f[j][0]+a[j].p;
		for(reg int i=j+1,k=j-1;i<=n;++i){
			while(k&&a[i].x-a[j].x>=a[j].x-a[k].x)
				cMax(val,f[j][k--]+a[j].p);
			cMax(f[i][j],val);
			cMax(ans,val+a[i].p);
		}
	}
	for(reg int j=n;j>=1;--j){
		int val=f[j][n+1]+a[j].p;
		for(reg int i=j-1,k=j+1;i>=1;--i){
			while(k<=n&&a[j].x-a[i].x>=a[k].x-a[j].x)
				cMax(val,f[j][k++]+a[j].p);
			cMax(f[i][j],val);
			cMax(ans,val+a[i].p);
		}
	}
	printf("%d\n",ans);
	return 0;
}