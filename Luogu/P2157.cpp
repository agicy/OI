#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=1e3+5;
const int MAXB=7;
const int inf=0x3f3f3f3f;

int n;
int T[MAXN],B[MAXN];
int f[MAXN][1<<(MAXB+1)][2*(MAXB+1)];

const int Delta=8;

int main(void){
	reg int C=read();
	while(C--){
		n=read();
		for(reg int i=1;i<=n;++i)
			T[i]=read(),B[i]=read();
		memset(f,0x3f,sizeof(f));
		f[1][0][7]=0;
		for(reg int i=1;i<=n;++i)
			for(reg int j=0;j<(1<<8);++j)
				for(reg int k=-8;k<=7;++k)
					if(f[i][j][k+Delta]!=inf){
						if(j&1)
							cMin(f[i+1][j>>1][k-1+Delta],f[i][j][k+Delta]);
						else{
							int tmp=inf;
							for(reg int l=0;l<=7;++l)
								if(!((j>>l)&1)){
									if(i+l>tmp)
										break;
									cMin(tmp,i+l+B[i+l]);
									cMin(f[i][j|(1<<l)][l+Delta],f[i][j][k+Delta]+(i+k?(T[i+k]^T[i+l]):0));
								}
						}
					}
		int res=inf;
		for(reg int k=0;k<=8;++k)
			cMin(res,f[n+1][0][k]);
		printf("%d\n",res);
	}
	return 0;
}