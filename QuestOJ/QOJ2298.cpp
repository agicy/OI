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

const int MAXN=5e5+5;

int n;
int s[MAXN];
bool vis[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		s[i]=read();
	sort(s+1,s+n+1);
	reg int ans=0;
	reg int i=1,j=n/2+1;
	while(i<=n/2){
		while(s[j]<s[i]*2&&j<=n)
			++j;
		if(j>n)
			break;
		vis[i]=true;
		++i,++j;
	}
	for(reg int i=1;i<=n;++i)
		if(!vis[i])
			++ans;
	printf("%d\n",ans);
	return 0;
}