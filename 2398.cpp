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

const int MAXN=2e3;
const int MAXK=10;
const int inf=0x3f3f3f3f;

int n,k;
int u[MAXN],v[MAXN];
int f[MAXN+1][MAXK+1][MAXK+1][MAXK+1][MAXK+1];

inline int getDis(reg int a,reg int b){
	return a>b?a-b:b-a;
}

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		u[i]=read(),v[i]=read();
	memset(f,0x3f,sizeof(f));
	f[0][0][0][0][1]=0;
	for(reg int i=0;i<=n;++i){
		for(reg int a=k;a>=0;--a)
			for(reg int b=k;b>=0;--b)
				for(reg int c=k;c>=0;--c)
					for(reg int pos=1;pos<=k;++pos)
						if(f[i][a][b][c][pos]!=inf){
							if(a)
								cMin(f[i][0][b][c][a],f[i][a][b][c][pos]+getDis(pos,a)+1);
							if(b)
								cMin(f[i][a][0][c][b],f[i][a][b][c][pos]+getDis(pos,b)+1);
							if(c)
								cMin(f[i][a][b][0][c],f[i][a][b][c][pos]+getDis(pos,c)+1);
						}
		if(i<n){
			reg int j=i+1;
			for(reg int a=k;a>=0;--a)
				for(reg int b=k;b>=0;--b)
					for(reg int c=k;c>=0;--c)
						if(a&&b&&c)
							for(reg int pos=1;pos<=k;++pos){
								if(f[i][a][b][c][pos]!=inf)
									cMin(f[j][a][b][c][v[j]],f[i][a][b][c][pos]+getDis(pos,u[j])+getDis(u[j],v[j])+2),
									cMin(f[j][v[j]][b][c][a],f[i][a][b][c][pos]+getDis(pos,u[j])+getDis(u[j],a)+2),
									cMin(f[j][a][v[j]][c][b],f[i][a][b][c][pos]+getDis(pos,u[j])+getDis(u[j],b)+2),
									cMin(f[j][a][b][v[j]][c],f[i][a][b][c][pos]+getDis(pos,u[j])+getDis(u[j],c)+2);
							}
						else
							for(reg int pos=1;pos<=k;++pos)
								if(f[i][a][b][c][pos]!=inf){
									if(!a)
										cMin(f[j][v[j]][b][c][u[j]],f[i][a][b][c][pos]+getDis(pos,u[j])+1);
									else if(!b)
										cMin(f[j][a][v[j]][c][u[j]],f[i][a][b][c][pos]+getDis(pos,u[j])+1);
									else
										cMin(f[j][a][b][v[j]][u[j]],f[i][a][b][c][pos]+getDis(pos,u[j])+1);
								}
		}
	}
	int ans=inf;
	for(reg int i=1;i<=k;++i)
		cMin(ans,f[n][0][0][0][i]);
	printf("%d\n",ans);
	return 0;
}