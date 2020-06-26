#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F3F3F3F3Fll
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline ll Solve(vector<int> V,reg bool flag){
	if(V.size()==1){
		reg int t=V[0];
		ll res=0;
		for(reg int i=1;i<=9;++i)
			if(t>>i&1){
				res=res*10+i;
				t^=(1<<i);
				if(t&1)
					res*=10,t^=1;
			}
		if(t&1)
			res=10;
		if(flag)
			res=max(res,1ll);
		return res;
	}
	ll res=INF;
	for(reg int x=0;x<=9;++x){
		if(V.size()==2&&(~V[0]>>9&1)&&(~V[1]&1)&&!flag&&x==9)
			continue;
		vector<int> New;
		int y=x-1,z=0;
		for(reg int i=0,size=V.size();i<size;++i){
			++y;
			z|=V[i]&(~(1<<y));
			if(y==9||i==size-1)
				New.push_back(z),y=-1,z=0;
		}
		res=min(res,Solve(New,(x==0)&&(V[0]&1))*10+x);
	}
	return res;
}

int n;

int main(void){
	n=read();
	vector<int> V(n);
	for(reg int i=0;i<n;++i){
		static int x;
		x=read();
		V[i]=(1<<x);
	}
	printf("%lld\n",Solve(V,1));
	return 0;
}