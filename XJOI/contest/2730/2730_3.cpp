#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXN=50;
const int MAXW=3;

int n;
int a[MAXW][2][MAXN];
int Min[MAXN],Max[MAXN];

inline ll getVal(reg int t,reg int pos){
	reg ll res=0;
	for(reg int S=0;S<(1<<MAXW);++S){
		reg int sum=t;
		for(reg int i=0;i<MAXW;++i)
			if((S>>i)&1)
				sum-=a[i][1][pos]-a[i][0][pos]+1;
		if(sum<0)
			continue;
		if(__builtin_parity(S))
			res-=1ll*(sum+1)*(sum+2)/2;
		else
			res+=1ll*(sum+1)*(sum+2)/2;
	}
	return res;
}

inline ll getVal(reg int t){
	reg ll res=0;
	for(reg int i=0;i<n;++i)
		if(Min[i]<=t&&t<=Max[i])
			res+=getVal(t-Min[i],i);
	return res;
}

inline ll solve(reg int l,reg int r){
	reg int __l=l,__r=r,__mid;
	while(__l<__r){
		__mid=(__l+__r)>>1;
		if(getVal(__mid)<=getVal(__mid+1))
			__l=__mid+1;
		else
			__r=__mid;
	}
	return getVal(__l);
}

bool ed;

int main(void){
	n=read();
	vector<int> V;
	V.push_back(-1);
	V.reserve(n<<1);
	for(reg int t=0;t<n;++t){
		for(reg int i=0;i<2;++i)
			for(reg int j=0;j<MAXW;++j)
				a[j][i][t]=read();
		for(reg int i=0;i<MAXW;++i)
			Min[t]+=a[i][0][t],Max[t]+=a[i][1][t];
		V.push_back(Min[t]),V.push_back(Max[t]);
	}
	sort(V.begin(),V.end()),V.erase(unique(V.begin(),V.end()),V.end());
	reg ll res=0;
	for(reg int i=0,siz=V.size();i<siz-1;++i)
		res=max(res,solve(V[i]+1,V[i+1]));
	printf("%lld\n",res);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}