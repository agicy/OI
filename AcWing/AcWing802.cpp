#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;
const int MAXM=1e5+5;

int n,m;
int x[MAXN],c[MAXN];
int l[MAXM],r[MAXM];
vector<int> V;
int sum[MAXN+MAXM*2];

int main(void){
	scanf("%d%d",&n,&m);
	V.resize(n+2*m);
	for(reg int i=1;i<=n;++i){
		scanf("%d%d",&x[i],&c[i]);
		V[i-1]=x[i];
	}
	for(reg int i=1;i<=m;++i){
		scanf("%d%d",&l[i],&r[i]);
		V[n+(i-1)*2]=l[i],V[n+(i-1)*2+1]=r[i];
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i){
		x[i]=lower_bound(V.begin(),V.end(),x[i])-V.begin()+1;
		sum[x[i]]+=c[i];
	}
	reg int L=V.size();
	for(reg int i=1;i<=L;++i)
		sum[i]+=sum[i-1];
	for(reg int i=1;i<=m;++i){
		l[i]=lower_bound(V.begin(),V.end(),l[i])-V.begin()+1;
		r[i]=lower_bound(V.begin(),V.end(),r[i])-V.begin()+1;
		printf("%d\n",sum[r[i]]-sum[l[i]-1]);
	}
	return 0;
}