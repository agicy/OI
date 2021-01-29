#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=50+5;
const double eps=1e-8;

inline int sgn(reg double x){
	if(fabs(x)<eps)
		return 0;
	else
		return x<0?-1:1;
}

int n;
int id[MAXN];
double a[MAXN][MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n+1;++j)
			a[i][j]=read();
	reg int ptr=1;
	for(reg int i=1;i<=n;++i){
		reg int Max=ptr;
		for(reg int j=ptr+1;j<=n;++j)
			if(fabs(a[j][i])>fabs(a[Max][i]))
				Max=j;
		if(!a[Max][i])
			continue;
		for(reg int j=1;j<=n+1;++j)
			swap(a[ptr][j],a[Max][j]);
		for(reg int j=1;j<=n;++j)
			if(j!=ptr){
				double d=a[j][i]/a[ptr][i];
				for(reg int k=i+1;k<=n+1;++k)
					a[j][k]-=d*a[ptr][k];
			}
		id[i]=ptr++;
	}
	vector<int> V;
	for(int i=1;i<=n;++i)
		if(!id[i])
			V.push_back(i);
	for(reg int j=0;ptr<=n;++j)
		id[V[j]]=ptr++;
	for(reg int i=1;i<=n;++i)
		if(sgn(a[id[i]][i])==0&&sgn(a[id[i]][n+1])!=0){
			puts("-1");
			return 0;
		}
	for(reg int i=1;i<=n;++i)
		if(sgn(a[id[i]][i])==0&&sgn(a[id[i]][n+1])==0){
			puts("0");
			return 0;
		}
	for(reg int i=1;i<=n;++i){
		reg double val=a[id[i]][n+1]/a[id[i]][i];
		if(sgn(val)==0)
			val=0;
		printf("x%d=%.2lf\n",i,val);
	}
	return 0;
}