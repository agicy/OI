#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e6+5;
const int lim=60;

int cnt;
int n;
bool vis[MAXN];
mt19937 Rd(500);

inline int myrand(reg int l,reg int r){
	return Rd()%(r-l+1)+l;
}

inline int getPos(void){
	reg int res;
	do
		res=myrand(1,n);
	while(vis[res]);
	vis[res]=true;
	return res;
}

inline int query1(reg int i){
	++cnt;
	printf("? %d\n",i);
	fflush(stdout);
	int res;
	scanf("%d",&res);
	return res;
}

inline bool query2(reg int x){
	++cnt;
	printf("> %d\n",x);
	fflush(stdout);
	int res;
	scanf("%d",&res);
	return res;
}

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

int main(void){
	scanf("%d",&n);
	reg int l=0,r=1e9,mid;
	while(l<r){
		mid=(0ll+l+r)>>1;
		if(query2(mid))
			l=mid+1;
		else
			r=mid;
	}
	reg int aMax=l;
	reg int res=lim-cnt;
	vector<int> V;
	res=min(res,n);
	while(res--){
		reg int pos=getPos();
		V.push_back(query1(pos));
	}
	sort(V.begin(),V.end());
	reg int d=0;
	for(reg int i=0,siz=V.size();i<siz;++i)
		for(reg int j=0;j<i;++j)
			d=gcd(d,V[i]-V[j]);
	reg int a1=aMax-(n-1)*d;
	printf("! %d %d\n",a1,d);
	fflush(stdout);
	return 0;
}