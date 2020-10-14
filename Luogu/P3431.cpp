#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline void cMax(reg int &a,reg int b){
	if(a<b)
		a=b;
	return;
}

const int MAXK=1e5+5;

struct Node{
	int x,y,p;
	inline Node(reg int x=0,reg int y=0,reg int p=0):x(x),y(y),p(p){
		return;
	}
	inline bool operator<(const Node& a)const{
		return x==a.x?y<a.y:x<a.x;
	}
};

int n,m,k;
Node a[MAXK];
vector<int> Vx,Vy;

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXK];
	inline void Init(reg int s){
		n=s;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			cMax(unit[i],val);
		return;
	}
	inline int query(reg int id){
		int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			cMax(res,unit[i]);
		return res;
	}
}

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=k;++i){
		static int x,y,p;
		x=read(),y=read(),p=read();
		a[i]=Node(x,y,p);
		Vx.push_back(x),Vy.push_back(y);
	}
	sort(Vx.begin(),Vx.end()),Vx.erase(unique(Vx.begin(),Vx.end()),Vx.end());
	sort(Vy.begin(),Vy.end()),Vy.erase(unique(Vy.begin(),Vy.end()),Vy.end());
	for(reg int i=1;i<=k;++i){
		a[i].x=lower_bound(Vx.begin(),Vx.end(),a[i].x)-Vx.begin()+1;
		a[i].y=lower_bound(Vy.begin(),Vy.end(),a[i].y)-Vy.begin()+1;
	}
	sort(a+1,a+k+1);
	BIT::Init(Vy.size());
	for(reg int i=1;i<=k;++i){
		reg int sum=BIT::query(a[i].y)+a[i].p;
		BIT::update(a[i].y,sum);
	}
	printf("%d\n",BIT::query(Vy.size()));
	return 0;
}