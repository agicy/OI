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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=5e5+5;
const int MAXM=5e5+5;

int n,m;
int a[MAXN],b[MAXM],c[MAXN],d[MAXM];
set<int> S;
vector<int> V[MAXN];

bool ed;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(int i=1;i<=m;++i)
		b[i]=read(),V[b[i]].push_back(i);
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	for(reg int i=1;i<=m;++i)
		d[i]=read();
	reg ll ans=0;
	for(reg int i=n;i>=1;--i){
		for(vector<int>::iterator it=V[i].begin();it!=V[i].end();++it)
			S.insert(*it);
		while(c[i]){
			set<int>::iterator it=S.upper_bound(a[i]);
			if(it==S.begin())
				break;
			--it;
			reg int val=min(c[i],d[*it]);
			ans+=val,c[i]-=val,d[*it]-=val;
			if(!d[*it])
				S.erase(it);
		}
	}
	printf("%lld\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}