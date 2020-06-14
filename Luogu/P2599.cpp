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

const int MAXN=1000+5;

int n;
int a[MAXN];
int L[MAXN][MAXN],R[MAXN][MAXN];

int main(void){
	reg int T=read();
	while(T--){
		n=read();
		for(reg int i=1;i<=n;++i)
			a[i]=read();
		for(reg int i=1;i<=n;++i)
			L[i][i]=R[i][i]=a[i];
		for(reg int len=2;len<=n;++len)
			for(reg int l=1,r=l+len-1;r<=n;++l,++r){
				reg int x=a[r],left=L[l][r-1],right=R[l][r-1];
				if(x==right)
					L[l][r]=0;
				else if((x>left&&x>right)||(x<left&&x<right))
					L[l][r]=x;
				else if(right<x&&x<left)
					L[l][r]=x-1;
				else
					L[l][r]=x+1;
				x=a[l],left=L[l+1][r],right=R[l+1][r];
				if(x==left)
					R[l][r]=0;
				else if((x>left&&x>right)||(x<left&&x<right))
					R[l][r]=x;
				else if(right<x&&x<left)
					R[l][r]=x+1;
				else
					R[l][r]=x-1;
			}
		puts(a[1]==L[2][n]?"0":"1");
	}
	return 0;
}