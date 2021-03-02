#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2e5+5;

struct Node{
	int x,y;
	inline bool operator<(const Node& a)const{
		return y<a.y;
	}
};

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	int unit[MAXN];
	inline void Init(reg int s){
		n=s;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
}

int n;
Node p[MAXN];
vector<int> Vx,Vy;

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		p[i].x=read(),p[i].y=read();
		Vx.push_back(p[i].x),Vy.push_back(p[i].y);
	}
	sort(Vx.begin(),Vx.end()),Vx.erase(unique(Vx.begin(),Vx.end()),Vx.end());
	sort(Vy.begin(),Vy.end()),Vy.erase(unique(Vy.begin(),Vy.end()),Vy.end());
	for(reg int i=1;i<=n;++i){
		p[i].x=lower_bound(Vx.begin(),Vx.end(),p[i].x)-Vx.begin()+1;
		p[i].y=lower_bound(Vy.begin(),Vy.end(),p[i].y)-Vy.begin()+1;
	}
	sort(p+1,p+n+1);
	BIT::Init(Vx.size());
	for(reg int i=n;i>=1;--i){

	}
	return 0;
}