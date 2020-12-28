#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2e5+5;
const int MAXW=2e5+5;

int n,w;
int a[MAXN],b[MAXW<<1];
int kmp[MAXW<<1];

int main(void){
	n=read(),w=read();
	if(w==1)
		printf("%d\n",n);
	else{
		for(reg int i=1;i<=n;++i)
			a[i]=read();
		for(reg int i=1;i<=w;++i)
			b[i]=read();
		for(reg int i=1;i<n;++i)
			a[i]-=a[i+1];
		for(reg int i=1;i<w;++i)
			b[i]-=b[i+1];
		b[w]=-1e9;
		reg int la=n-1;
		for(reg int i=w+1;i<=w+la;++i)
			b[i]=a[i-w];
		reg int ans=0;
		for(reg int i=2,j=0;i<=la+w;++i){
			while(j&&b[j+1]!=b[i])
				j=kmp[j];
			if(b[j+1]==b[i])
				++j;
			kmp[i]=j;
			if(j==w-1)
				++ans;
		}
		printf("%d\n",ans);
	}
	return 0;
}