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

const int MAXN=300000+5;

int n;
int a[MAXN];
int l[MAXN],r[MAXN];
int f[MAXN];

int main(void){
	reg int T=read();
	while(T--){
		n=read();
		int ans=0;
		for(reg int i=1;i<=n;++i){
			a[i]=read();
			if(!l[a[i]])
				l[a[i]]=i;
			r[a[i]]=i;
		}
		sort(a+1,a+n+1);
		reg int cnt=unique(a+1,a+n+1)-(a+1);
		for(reg int i=1;i<=cnt;++i)
			if(l[a[i]]>r[a[i-1]])
				f[a[i]]=f[a[i-1]]+1;
			else
				f[a[i]]=1;
		for(reg int i=1;i<=cnt;++i)
			ans=max(ans,f[a[i]]);
		printf("%d\n",cnt-ans);
		for(reg int i=1;i<=cnt;++i)
			f[a[i]]=l[a[i]]=r[a[i]]=0;
	}
	return 0;
}
