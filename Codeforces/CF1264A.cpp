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

const int MAXN=4e5+5;

int n;
int p[MAXN];
int a[MAXN];
int cnt;
int sum[MAXN];

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		for(reg int i=1;i<=n;++i)
			p[i]=read();
		cnt=0;
		for(reg int i=1,l,r;i<=n;i=r+1){
			l=i,r=i;
			while(r+1<=n&&p[l]==p[r+1])
				++r;
			a[++cnt]=r-l+1;
		}
		for(reg int i=1;i<=cnt;++i)
			sum[i]=sum[i-1]+a[i];
		reg int gpos=1,spos=1,bpos=1;
		reg int g,s,b;
		reg int ans=0,ansg=0,anss=0,ansb=0;
		for(reg int i=cnt;i>=1;--i){
			gpos=i;
			g=sum[gpos];
			if(g+g+1+g+1>n/2)
				continue;
			reg int ls=lower_bound(sum+1,sum+cnt+1,g+g+1)-sum;
			for(reg int j=ls;j<=cnt;++j){
				spos=j;
				s=sum[spos]-sum[gpos];
				if(g+s+g+1>n/2)
					break;
				reg int lb=lower_bound(sum+1,sum+cnt+1,g+s+g+1)-sum;
				for(reg int k=lb;k<=cnt;++k){
					bpos=k;
					b=sum[bpos]-sum[spos];
					if(g+s+b>n/2)
						break;
					else if(g+s+b>ans){
						ans=g+s+b;
						ansg=g,anss=s,ansb=b;
					}
				}
			}
		}
		printf("%d %d %d\n",ansg,anss,ansb);
	}
	return 0;
}