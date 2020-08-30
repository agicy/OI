#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=2.5e5+5;
const int w=500;

struct Node{
	ll d,r;
	int m,p;
};

inline ll sqr(ll x){
	return x*x;
}

inline bool cmpD(const Node& a,const Node& b){
	return a.d<b.d;
}
inline bool cmpM(const Node& a,const Node& b){
	return a.m<b.m;
}

ll X0,Y0;
int n;
Node a[MAXN];
bool vis[MAXN];
int L[MAXN],R[MAXN];
ll D[MAXN];
queue<int> Q;

int main(void){
	scanf("%lld%lld%d%lld%d",&X0,&Y0,&a[0].p,&a[0].r,&n);
	a[0].r=sqr(a[0].r);
	for(int i=1;i<=n;++i){
		static int x,y,r;
		scanf("%d%d%d%d%d",&x,&y,&a[i].m,&a[i].p,&r);
		a[i].r=sqr(r),a[i].d=sqr(X0-x)+sqr(Y0-y);
	}
	sort(a+1,a+1+n,cmpD);
	int tot=0;
	for(int i=1;i<=n;i+=w){
		L[++tot]=i;
		R[tot]=min(n,i+w-1);
		D[tot]=a[R[tot]].d;
		sort(a+L[tot],a+R[tot]+1,cmpM);
	}
	Q.push(0);
	int ans=1;
	while(!Q.empty()){
		int id=Q.front();
		ll r=a[id].r;
		int p=a[id].p;
		Q.pop();
		for(int i=1;i<=tot;++i){
			if(D[i]>r){
				for(int j=L[i];j<=R[i];++j)
					if(!vis[j]&&a[j].d<=r&&a[j].m<=p){
						vis[j]=true;
						++ans;
						Q.push(j);
					}
				break;
			}
			while(L[i]<=R[i]&&a[L[i]].m<=p){
				if(!vis[L[i]]){
					++ans;
					Q.push(L[i]);
				}
				++L[i];
			}
		}
	}
	printf("%d\n",ans-1);
	return 0;
}