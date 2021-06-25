#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;

inline pair<int,int> fix(pair<int,int> x){
	if(x.first>x.second)
		swap(x.first,x.second);
	return x;
}

inline bool cmp(reg int a,reg int b){
	return a>b;
}

int a,b,h,w,n;
int val[MAXN];
queue<pair<int,int>/**/> Q;
map<pair<int,int>,int> M;

int main(void){
	a=read(),b=read(),h=read(),w=read(),n=read();
	for(reg int i=1;i<=n;++i)
		val[i]=read();
	sort(val+1,val+n+1,cmp);
	reg int lim=min(34,n);
	pair<int,int> H=make_pair((a+h-1)/h,(b+w-1)/w),W=make_pair((a+w-1)/w,(b+h-1)/h);
	M[H]=1,Q.push(H),M[W]=1,Q.push(W);
	while(!Q.empty()){
		static pair<int,int> p,f;
		p=Q.front();
		Q.pop();
		reg int dep=M[p];
		if(p.first==1&&p.second==1){
			printf("%d\n",dep-1);
			return 0;
		}
		if(dep<=lim){
			f=fix(make_pair((p.first+val[dep]-1)/val[dep],p.second));
			if(!M[f])
				M[f]=dep+1,Q.push(f);
			f=fix(make_pair(p.first,(p.second+val[dep]-1)/val[dep]));
			if(!M[f])
				M[f]=dep+1,Q.push(f);
		}
	}
	puts("-1");
	return 0;
}