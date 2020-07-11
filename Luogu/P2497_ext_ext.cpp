#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=5000000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct Node{
	ll x;
	int r,v;
	inline void Read(void){
		x=read(),r=read(),v=read();
		return;
	}
};

int n;
ll m;
Node a[MAXN];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i].Read();
	return;
}

bool inque[MAXN];
float dis[MAXN];
queue<int> Q;

inline float GetR(const Node& a,reg double x){
	reg float dx=x-a.x;
	reg float dx2=dx*dx;
	reg float k=4.0*a.r;
	return dx2/k;
}

inline float GetVal(reg int j,reg int i){
	return 1.0*a[j].v+sqrt(GetR(a[j],a[i].x));
}

inline void SPFA(void){
	fill(dis+1,dis+n+1,1e36);
	for(reg int i=n;i>=1;--i)
		if(a[i].x+a[i].r>=m){
			inque[i]=true;
			dis[i]=a[i].v;
			Q.push(i);
		}
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		inque[ID]=false;
		for(reg int i=1;i<=n;++i){
			if(dis[i]>dis[ID]+GetVal(i,ID)){
				dis[i]=dis[ID]+GetVal(i,ID);
				if(!inque[i]){
					inque[i]=true;
					Q.push(i);
				}
			}
		}
	}
	return;
}

inline void Work(void){
	SPFA();
	printf("%.3f\n",dis[1]);
	return;
}
