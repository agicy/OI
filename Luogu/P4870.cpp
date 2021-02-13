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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=300+5;

int n,m,s;
int x[MAXN];
int f[MAXN][MAXN];

int main(void){
	n=read(),m=read();
	reg bool flag=false;
	for(reg int i=1;i<=n;++i){
		x[i]=read();
		flag=flag||!x[i];
	}
	if(!flag)
		x[++n]=0;
	sort(x+1,x+n+1);
	s=lower_bound(x+1,x+1+n,0)-x;
	reg int ans=0;
	for(reg int Len=1;Len<=n;++Len){
		memset(f,0x3f,sizeof(f));
		f[s][s]=0;
		for(reg int len=2;len<=Len;++len)
			for(reg int l=max(1,s-len+1);l<=s&&l<=n-len+1;++l){
				reg int r=l+len-1;
				if(l<s){
					f[l][r]=f[r][l+1]+(x[l+1]-x[l])*(Len-r+l)+(x[r]-x[l])*(Len-r+l-1);
					f[r][l]=f[r][l+1]+(x[l+1]-x[l])*(Len-r+l);
				}
				if(r>s){
					f[l][r]=min(f[l][r],f[l][r-1]+(x[r]-x[r-1])*(Len-r+l));
					f[r][l]=min(f[r][l],f[l][r-1]+(x[r]-x[r-1])*(Len-r+l)+(x[r]-x[l])*(Len-r+l-1));
				}
			}
		for(reg int l=max(1,s-Len+1);l<=s&&l<=n-Len+1;++l){
			reg int r=l+Len-1;
			ans=max(ans,Len*m-min(f[l][r],f[r][l])-(flag?0:m));
		}
	}
	printf("%d\n",ans);
	return 0;
}