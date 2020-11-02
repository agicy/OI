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
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=5e5+5;

int n,k;
int a[MAXN];
int b[MAXN];
int s[MAXN];
bool ban[MAXN];

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=k;++i)
		ban[b[i]=read()]=true;
	sort(b+1,b+k+1);
	for(reg int i=2;i<=k;++i)
		if(a[b[i-1]]-b[i-1]>a[b[i]]-b[i]){
			puts("-1");
			return 0;
		}
	for(reg int i=1;i<=n;++i)
		a[i]-=i;
	reg int las=0,cnt=0;
	for(reg int i=1;i<=n;++i){
		if(!cnt||a[i]>=s[cnt]){
			s[++cnt]=a[i];
			if(ban[i])
				las=cnt;
		}
		else{
			reg int p=upper_bound(s+1,s+cnt+1,a[i])-s;
			if(p<=las)
				continue;
			s[p]=a[i];
			if(ban[i])
				las=cnt=p;
		}
	}
	printf("%d\n",n-cnt);
	return 0;
}