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

const int MAXN=100000+5;
const int MAXD=100+5;

int n,d,k;
int x[MAXN][MAXD];
int nx[MAXN][MAXD];
int id[MAXN],rnk[MAXN];

inline void Solve2(void){
	int sum[MAXD];
	memset(sum,0,sizeof(sum));
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=d;++j)
			nx[i][j]&=1;
	reg int pos=-1;
	for(reg int i=1;i<=n;++i){
		reg int res=0;
		for(reg int j=1;j<=d;++j)
			res^=nx[i][j]^sum[j];
		if(res!=((i-1)&1)){
			pos=i;
			for(reg int i=1;i<pos;++i){
				reg int res=0;
				for(reg int j=1;j<=d;++j)
					res^=nx[i][j]&nx[pos][j];
				if(!res){
					int a=id[i],b=id[pos];
					if(a>b)
						swap(a,b);
					printf("%d %d\n",a,b);
					return;
				}
			}
		}
		for(reg int j=1;j<=d;++j)
			sum[j]^=nx[i][j];
	}
	puts("-1 -1");
	return;
}

inline void Solve3(void){
	int sum[MAXD][MAXD];
	memset(sum,0,sizeof(sum));
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=d;++j)
			nx[i][j]%=3;
	reg int pos=-1;
	for(reg int i=1;i<=n;++i){
		reg int res=0;
		for(reg int j=1;j<=d;++j)
			for(reg int k=1;k<=d;++k)
				res+=sum[j][k]*nx[i][j]*nx[i][k];
		if(res%3!=(i-1)%3){
			pos=i;
			for(reg int i=1;i<pos;++i){
				reg int res=0;
				for(reg int j=1;j<=d;++j)
					res+=nx[i][j]*nx[pos][j];
				if(res%3==0){
					int a=id[i],b=id[pos];
					if(a>b)
						swap(a,b);
					printf("%d %d\n",a,b);
					return;
				}
			}
		}
		for(reg int j=1;j<=d;++j)
			for(reg int k=1;k<=d;++k)
				sum[j][k]+=nx[i][j]*nx[i][k];
	}
	puts("-1 -1");
	return;
}

int main(void){
	n=read(),d=read(),k=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=d;++j)
			x[i][j]=read();
	for(reg int i=1;i<=n;++i)
		id[i]=i;
	random_shuffle(id+1,id+n+1);
	for(reg int i=1;i<=n;++i)
		rnk[id[i]]=i;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=d;++j)
			nx[i][j]=x[id[i]][j];
	if(k==2)
		Solve2();
	if(k==3)
		Solve3();
	return 0;
}