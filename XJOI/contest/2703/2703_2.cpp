#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=5;
const int MAXM=7;

int n,m,nm;
int f[2][MAXN*MAXM+1][1<<(MAXN+1)];
char a[MAXM][MAXN];

int main(void){
	reg int t=read();
	while(t--){
		n=read(),m=read(),nm=n*m;
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				do
					a[j][i]=getchar();
				while(!isdigit(a[j][i]));
		swap(n,m);
		reg int ptr=0;
		for(reg int S=0;S<(1<<(m+1));++S)
			f[ptr][0][S]=-1;
		f[ptr][0][0]=0;
		for(reg int i=0;i<n;++i){
			for(reg int j=0;j<m;++j){
				for(reg int cnt=0;cnt<=i*m+j+1;++cnt)
					for(reg int S=0;S<(1<<(m+1));++S)
						f[ptr^1][cnt][S]=-1;
				for(reg int cnt=0;cnt<=i*m+j;++cnt)
					for(reg int S=0;S<(1<<(m+1));++S)
						if(f[ptr][cnt][S]>=0)
							switch((S>>j)&3){
								case 0:{
									f[ptr^1][cnt][S]=max(f[ptr^1][cnt][S],f[ptr][cnt][S]);
									if(a[i][j]=='1'&&i!=n-1&&j!=m-1)
										f[ptr^1][cnt+1][S|(1<<j)|(1<<(j+1))]=max(f[ptr^1][cnt+1][S|(1<<j)|(1<<(j+1))],f[ptr][cnt][S]+1);
									break;
								}
								case 1:{
									if(j!=m-1)
										f[ptr^1][cnt][(S^(1<<j))|(1<<(j+1))]=max(f[ptr^1][cnt][(S^(1<<j))|(1<<(j+1))],f[ptr][cnt][S]+1);
									if(a[i][j]=='1'&&i!=n-1)
										f[ptr^1][cnt+1][S]=max(f[ptr^1][cnt+1][S],f[ptr][cnt][S]+1);
									break;
								}
								case 2:{
									if(i!=n-1)
										f[ptr^1][cnt][(S^(1<<(j+1)))|(1<<j)]=max(f[ptr^1][cnt][(S^(1<<(j+1)))|(1<<j)],f[ptr][cnt][S]+1);
									if(a[i][j]=='1'&&j!=m-1)
										f[ptr^1][cnt+1][S]=max(f[ptr^1][cnt+1][S],f[ptr][cnt][S]+1);
									break;
								}
								case 3:{
									if(i!=n-1&&j!=m-1)
										f[ptr^1][cnt][S]=max(f[ptr^1][cnt][S],f[ptr][cnt][S]+2);
									if(a[i][j]=='1')
										f[ptr^1][cnt+1][S^(1<<j)^(1<<(j+1))]=max(f[ptr^1][cnt+1][S^(1<<j)^(1<<(j+1))],f[ptr][cnt][S]+1);
									break;
								}
							}
				ptr^=1;
			}
			for(reg int cnt=0;cnt<=(i+1)*m;++cnt)
				for(reg int S=0;S<(1<<(m+1));++S)
					f[ptr^1][cnt][S]=-1;
			for(reg int cnt=0;cnt<=(i+1)*m;++cnt)
				for(reg int S=0;S<(1<<m);++S)
					if(f[ptr][cnt][S]>=0)
						f[ptr^1][cnt][S<<1]=f[ptr][cnt][S];
			ptr^=1;
		}
		f[ptr][0][0]=max(f[ptr][0][0],0);
		for(reg int i=1;i<=nm;++i)
			f[ptr][i][0]=max(f[ptr][i][0],f[ptr][i-1][0]);
		for(reg int i=0;i<=nm;++i)
			printf("%d%c",(nm<<2)-(f[ptr][i][0]<<1),i==nm?'\n':' ');
	}
	return 0;
}