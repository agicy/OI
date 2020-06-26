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

const int MAXN=400+5;

int n;
int f[MAXN][MAXN];

int main(void){
	n=read();
	int ans=0;
	for(reg int i=1;i<=n;++i){
		f[i][i]=read();
		ans=max(ans,f[i][i]);
	}
	for(reg int len=2;len<=n;++len)
		for(reg int l=1;l+len-1<=n;++l){
			reg int r=l+len-1;
			for(reg int i=l;i<r;++i)
				if(f[l][i]&&f[i+1][r]&&f[l][i]==f[i+1][r]){
					f[l][r]=f[l][i]+f[i+1][r];
					break;
				}
			for(reg int i=l,j=r;i<j-1&&!f[l][r];){
				if(!f[l][i])
					++i;
				else if(!f[j][r])
					--j;
				else if(f[l][i]==f[j][r]){
					if(f[i+1][j-1])
						f[l][r]=f[l][i]+f[i+1][j-1]+f[j][r];
					else
						++i,--j;
				}
				else if(f[l][i]<f[j][r])
					++i;
				else if(f[l][i]>f[j][r])
					--j;
			}
			ans=max(ans,f[l][r]);
		}
	printf("%d\n",ans);
	return 0;
}
