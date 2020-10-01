#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

inline void cMax(reg int &a,reg int b){
	if(a<b)
		a=b;
	return;
}

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=50+5;
const int inf=0x3f3f3f3f;

int n;
int a[MAXN<<1];
char b[MAXN<<1];
int f[MAXN<<1][MAXN<<1];
int g[MAXN<<1][MAXN<<1];

int main(void){
	n=read();
	for(reg int i=1;i<=2*n;++i)
		if(i&1){
			static char x;
			cin>>x;
			b[(i>>1)+1]=b[(i>>1)+1+n]=x;
		}
		else{
			static int x;
			x=read();
			a[i>>1]=a[(i>>1)+n]=x;
		}
	memset(f,128,sizeof(f));
	memset(g,0x3f,sizeof(g));
	for(reg int i=1;i<=2*n;++i)
		f[i][i]=g[i][i]=a[i];
	for(reg int len=1;len<=n;++len)
		for(reg int l=1;l+len<=2*n;++l){
			reg int r=l+len;
			for(reg int k=l;k<r;++k)
				if(b[k+1]=='t'){
					cMax(f[l][r],f[l][k]+f[k+1][r]);
					cMin(g[l][r],g[l][k]+g[k+1][r]);
				}
				else{
					cMax(f[l][r],f[l][k]*f[k+1][r]);
					cMax(f[l][r],g[l][k]*g[k+1][r]);
					cMin(g[l][r],g[l][k]*g[k+1][r]);
					cMin(g[l][r],f[l][k]*g[k+1][r]);
					cMin(g[l][r],g[l][k]*f[k+1][r]);
				}
		}
	int ans=-inf;
	for(reg int i=1;i<=n;++i)
		cMax(ans,f[i][i+n-1]);
	printf("%d\n",ans);
	reg bool flag=false;
	for(reg int i=1;i<=n;++i)
		if(f[i][i+n-1]==ans){
			if(!flag){
				flag=true;
				printf("%d",i);
			}
			else
				printf(" %d",i);
		}
	putchar('\n');
	return 0;
}