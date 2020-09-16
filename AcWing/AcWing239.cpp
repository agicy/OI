#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXM=1e4+5;

int fa[MAXM<<1],dis[MAXM<<1];

inline void Init(reg int n){
	for(reg int i=1;i<=n;++i)
		fa[i]=i;
	return;
}
inline int find(reg int x){
	if(x==fa[x])
		return x;
	else{
		reg int r=find(fa[x]);
		dis[x]^=dis[fa[x]];
		return fa[x]=r;
	}
}

int n,m;
int l[MAXM],r[MAXM],sum[MAXM];
vector<int> V;

int main(void){
	cin>>n>>m;
	for(reg int i=1;i<=m;++i){
		cin>>l[i]>>r[i];
		V.push_back(l[i]-1),V.push_back(r[i]);
		static string opt;
		cin>>opt;
		sum[i]=(opt[0]=='o');
	}
	reg int ans=m;
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	n=V.size();
	for(reg int i=1;i<=m;++i){
		l[i]=lower_bound(V.begin(),V.end(),l[i]-1)-V.begin()+1;
		r[i]=lower_bound(V.begin(),V.end(),r[i])-V.begin()+1;
	}
	Init(n);
	for(reg int i=1;i<=m;++i){
		reg int ra=find(l[i]),rb=find(r[i]);
		if(ra==rb&&(dis[l[i]]^dis[r[i]])!=sum[i]){
			ans=i-1;
			break;
		}
		else{
			fa[ra]=rb;
			dis[ra]=dis[l[i]]^dis[r[i]]^sum[i];
		}
	}
	printf("%d\n",ans);
	return 0;
}