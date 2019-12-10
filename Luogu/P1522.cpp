#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 1e15

const int MAXN=150+5;

struct Node{
	int x,y;
	inline void Read(void){
		scanf("%d%d",&x,&y);
		return;
	}
};

int n;
bool M[MAXN][MAXN];
Node a[MAXN];
double f[MAXN][MAXN];
double l[MAXN];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i)
		scanf("%d%d",&a[i].x,&a[i].y);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j){
			static int x;
			scanf("%1d",&x);
			M[i][j]=(x==1);
		}
	return;
}

inline double Calc(const Node& a,const Node& b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			if(M[i][j])
				f[i][j]=Calc(a[i],a[j]);
			else if(i!=j)
				f[i][j]=INF;
	for(reg int k=1;k<=n;++k)
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				if(f[i][j]>f[i][k]+f[k][j])
					f[i][j]=f[i][k]+f[k][j];
	reg double l1=0,l2=INF;
	for(reg int i=1;i<=n;++i){
		for(reg int j=1;j<=n;++j)
			if(f[i][j]!=INF)
				l[i]=max(l[i],f[i][j]);
		l1=max((double)l1,l[i]);
	}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			if(f[i][j]==INF)
				l2=min((double)l2,l[i]+Calc(a[i],a[j])+l[j]);
	printf("%.6lf\n",max((double)l1,(double)l2));
	return;
}
