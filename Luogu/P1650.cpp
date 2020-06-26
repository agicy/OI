#include<bits/stdc++.h>
using namespace std;
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

const int MAXN=2000+5;

int n;
int a[MAXN],b[MAXN];

inline bool cmp(const int& a,const int& b){
	return a>b;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		b[i]=read();
	sort(a+1,a+1+n,cmp);
	sort(b+1,b+1+n,cmp);
	reg int ans=0;
	reg int ri=n,rj=n;
	for(reg int i=1,j=1;i<=ri;)
		if(a[i]>b[j]){
			++i,++j;
			++ans;
		}
		else if(a[i]<b[j]){
			--ri,++j;
			--ans;
		}
		else if(a[ri]>b[rj]){
			--ri,--rj;
			++ans;
		}
		else{
			if(a[ri]<b[j])
				--ans;
			--ri,++j;
		}
	printf("%d\n",ans*200);
	return 0;
}
