#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXL=1e3+5;
const int MAXP=5e3+5;
const double eps=1e-4;

int L,P;
int f[MAXL];
int cnt,head[MAXL],to[MAXP],w[MAXP],Next[MAXP];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool inque[MAXL];
int in[MAXL];
double dis[MAXL];
queue<int> Q;

inline bool check(reg double mid){
	while(!Q.empty())Q.pop();
	for(reg int i=1;i<=L;++i)
		inque[i]=true,in[i]=dis[i]=0,Q.push(i);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		inque[u]=false;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			reg double W=w[i]*mid-f[u];
			if(dis[v]>dis[u]+W){
				dis[v]=dis[u]+W;
				if(!inque[v]){
					inque[v]=true;
					++in[v];
					if(in[v]>L)
						return true;
					Q.push(v);
				}
			}
		}
	}
	return false;
}

int main(void){
	scanf("%d%d",&L,&P);
	for(reg int i=1;i<=L;++i)
		scanf("%d",&f[i]);
	for(reg int i=1;i<=P;++i){
		static int a,b,t;
		scanf("%d%d%d",&a,&b,&t);
		Add_Edge(a,b,t);
	}
	reg double l=0,r=1e3,mid;
	while(r-l>eps){
		mid=0.5*(l+r);
		if(check(mid))
			l=mid;
		else
			r=mid;
	}
	printf("%.2lf\n",r);
	return 0;
}