#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;
const int MAXSIZE=1e4+5;
const int MAXV=26*26;
const double eps=1e-3;

int n;
char str[MAXSIZE];
int cnt,head[MAXV],to[MAXN],w[MAXN],Next[MAXN];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool inque[MAXV];
int in[MAXV];
double dis[MAXV];
queue<int> Q;

inline bool spfa(reg double x){
	while(!Q.empty())Q.pop();
	for(reg int i=0;i<MAXV;++i)
		inque[i]=true,in[i]=0,dis[i]=0,Q.push(i);
	reg int cnt=0;
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		inque[u]=false;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			reg double W=w[i]-x;
			if(dis[v]<dis[u]+W){
				dis[v]=dis[u]+W;
				in[v]=in[u]+1;
				if(in[v]>MAXV)
					return true;
				if(++cnt>2*n)
					return true;
				if(!inque[v]){
					inque[v]=true;
					Q.push(v);
				}
			}
		}
	}
	return false;
}

int main(void){
	while(scanf("%d",&n)!=EOF&&n!=0){
		cnt=0,memset(head,0,sizeof(head));
		for(reg int i=1;i<=n;++i){
			scanf("%s",str);
			reg int len=strlen(str);
			if(len<2)
				continue;
			reg int a=(str[0]-'a')*26+(str[1]-'a');
			reg int b=(str[len-2]-'a')*26+(str[len-1]-'a');
			Add_Edge(a,b,len);
		}
		if(!spfa(0))
			puts("No solution");
		else{
			reg double l=0,r=1e3,mid;
			while(r-l>eps){
				mid=0.5*(l+r);
				if(spfa(mid))
					l=mid;
				else
					r=mid;
			}
			printf("%.2lf\n",r);
		}
	}
	return 0;
}