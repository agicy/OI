#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;
const double inf=1e9;
const double eps=1e-9;

struct Node{
	double k,a,b,r;
	double x,y;
	int id;
};

int n;;
double dp[MAXN];
int id[MAXN];
Node q[MAXN],tmp[MAXN];

inline double slope(reg int i,reg int j){
	if(fabs(q[i].x-q[j].x)<=eps)
		return inf;
	else
		return (q[j].y-q[i].y)/(q[j].x-q[i].x);
}

inline bool cmpk(const Node& a,const Node& b){
	return a.k<b.k;
}

inline void solve(reg int l,reg int r){
	if(l==r){
		dp[l]=max(dp[l],dp[l-1]);
		q[l].y=dp[l]/(q[l].a*q[l].r+q[l].b);
		q[l].x=q[l].y*q[l].r;
		return;
	}
	reg int mid=(l+r)>>1;
	reg int lef=l-1,rig=mid;
	for(reg int i=l;i<=r;++i)
		if(q[i].id<=mid)
			tmp[++lef]=q[i];
		else
			tmp[++rig]=q[i];
	for(reg int i=l;i<=r;++i)
		q[i]=tmp[i];
	solve(l,mid);
	reg int top=0;
	static int S[MAXN];
	for(reg int i=l;i<=mid;++i){
		while(top>=2&&slope(S[top],i)+eps>slope(S[top-1],S[top]))
			--top;
		S[++top]=i;
	}
	for(reg int i=mid+1;i<=r;++i){
		while(top>=2&&slope(S[top-1],S[top])<=q[i].k)
			--top;
		reg int j=S[top];
		dp[q[i].id]=max(dp[q[i].id],q[j].x*q[i].a+q[j].y*q[i].b);
	}
	solve(mid+1,r);
	reg int i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r)
		if(q[i].x<q[j].x)
			tmp[k++]=q[i++];
		else
			tmp[k++]=q[j++];
	while(i<=mid)
		tmp[k++]=q[i++];
	while(j<=r)
		tmp[k++]=q[j++];
	for(reg int i=l;i<=r;++i)
		q[i]=tmp[i];
	return;
}

int main(void){
	scanf("%d%lf",&n,&dp[0]);
	for(reg int i=1;i<=n;++i){
		scanf("%lf%lf%lf",&q[i].a,&q[i].b,&q[i].r);
		q[i].k=-q[i].a/q[i].b,q[i].id=i;
	}
	sort(q+1,q+n+1,cmpk);
	solve(1,n);
	printf("%.3lf\n",dp[n]);
	return 0;
}