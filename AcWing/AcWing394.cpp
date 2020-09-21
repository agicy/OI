#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXM=3e5+5;
const int MAXV=MAXM*2;
const int MAXE=MAXM;
const double eps=0.1;
const double inf=1e9;

int n,m;
map<string,int> M;
int cnt,head[MAXV],to[MAXE],Next[MAXE];
double w[MAXE];

inline void Add_Edge(reg int u,reg int v,reg double len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline int getVal(reg char ch){
	switch(ch){
		case 'S':
			return 1000;
		case 'G':
			return 500;
		case 'D':
			return 300;
		case 'T':
			return 200;
		case 'K':
			return 150;
		default:
			return -1;
	}
}

bool vis[MAXV];
double dis[MAXV];

inline bool spfa(reg int u,reg double mid){
	vis[u]=true;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(dis[v]>dis[u]+w[i]+mid){
			dis[v]=dis[u]+w[i]+mid;
			if(vis[v]||spfa(v,mid)){
				vis[u]=false;
				return true;
			}
		}
	}
	vis[u]=false;
	return false;
}

inline bool check(reg double mid){
	for(reg int i=1;i<=n;++i)
		dis[i]=inf;
	for(reg int i=1;i<=n;++i)
		if(spfa(i,mid))
			return true;
	return false;
}

int main(void){
	cin>>m;
	for(reg int i=1;i<=m;++i){
		static string str,tmp,s,t;
		cin>>str;
		tmp.clear();
		reg bool flag=false;
		reg int sum=0;
		for(reg int i=0,siz=str.length();i<siz;++i)
			if(str[i]=='-'){
				if(!flag){
					flag=true;
					s=tmp;
				}
				sum+=getVal(tmp[0]);
				tmp.clear();
			}
			else
				tmp+=str[i];
		t=tmp;
		sum+=getVal(tmp[0]);
		if(!M.count(s))
			M[s]=++n;
		if(!M.count(t))
			M[t]=++n;
		Add_Edge(M[s],M[t],-sum);
	}
	if(!check(0))
		puts("-1");
	else{
		reg double l=0,r=1e3*20,mid;
		while(r-l>eps){
			mid=0.5*(l+r);
			if(check(mid))
				l=mid;
			else
				r=mid;
		}
		printf("%.0lf\n",l);
	}
	return 0;
}