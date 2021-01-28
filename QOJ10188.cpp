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

const int MAXN=21+5;

const int sg[MAXN][MAXN]=
{
{0},
{0,0},
{0,1,0},
{0,2,1,0},
{0,4,2,1,0},
{0,7,4,2,1,0},
{0,8,7,4,2,1,0},
{0,11,8,7,4,2,1,0},
{0,13,11,8,7,4,2,1,0},
{0,14,13,11,8,7,4,2,1,0},
{0,16,14,13,11,8,7,4,2,1,0},
{0,19,16,14,13,11,8,7,4,2,1,0},
{0,21,19,16,14,13,11,8,7,4,2,1,0},
{0,22,21,19,16,14,13,11,8,7,4,2,1,0},
{0,25,22,21,19,16,14,13,11,8,7,4,2,1,0},
{0,26,25,22,21,19,16,14,13,11,8,7,4,2,1,0},
{0,28,26,25,22,21,19,16,14,13,11,8,7,4,2,1,0},
{0,31,28,26,25,22,21,19,16,14,13,11,8,7,4,2,1,0},
{0,32,31,28,26,25,22,21,19,16,14,13,11,8,7,4,2,1,0},
{0,35,32,31,28,26,25,22,21,19,16,14,13,11,8,7,4,2,1,0},
{0,37,35,32,31,28,26,25,22,21,19,16,14,13,11,8,7,4,2,1,0},
{0,38,37,35,32,31,28,26,25,22,21,19,16,14,13,11,8,7,4,2,1,0}
};

int n;
int a[MAXN];

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		for(reg int i=1;i<=n;++i)
			a[i]=read();
		reg int ans=0;
		for(reg int i=1;i<=n;++i)
			if(a[i]&1)
				ans^=sg[n][i];
		reg int tot=0;
		for(reg int i=1;i<=n;++i)
			if(a[i])
				for(reg int j=i+1;j<=n;++j)
					for(reg int k=j;k<=n;++k)
						if(!(ans^sg[n][i]^sg[n][j]^sg[n][k])){
							if(!tot)
								printf("%d %d %d\n",i-1,j-1,k-1);
							++tot;
						}
		if(!tot)
			puts("-1 -1 -1");
		printf("%d\n",tot);
	}
	return 0;
}