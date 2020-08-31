#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=150+5;
const double inf=1e15;

struct Node{
	int x,y;
	inline void read(void){
		scanf("%d%d",&x,&y);
		return;
	}
};

inline double sqr(double x){
	return x*x;
}

inline double getDis(const Node& a,const Node& b){
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}

int n;
bool M[MAXN][MAXN];
Node a[MAXN];
double f[MAXN][MAXN],l[MAXN];

int main(void){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		a[i].read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j){
			static int x;
			scanf("%1d",&x);
			M[i][j]=x;
		}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(M[i][j])
				f[i][j]=getDis(a[i],a[j]);
			else if(i!=j)
				f[i][j]=inf;
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				if(f[i][j]>f[i][k]+f[k][j])
					f[i][j]=f[i][k]+f[k][j];
	double l1=0,l2=inf;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j)
			if(f[i][j]!=inf)
				l[i]=max(l[i],f[i][j]);
		l1=max(l1,l[i]);
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(f[i][j]==inf)
				l2=min(l2,l[i]+getDis(a[i],a[j])+l[j]);
	printf("%lf\n",max(l1,l2));
	return 0;
}