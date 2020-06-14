#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=200000+5;

struct Node{
	int x1,y1,x2,y2;
	bool f;
	inline void Read(void){
		x1=read(),y1=read(),x2=read(),y2=read();
		return;
	}
};

inline bool cmp1(const Node& a,const Node& b){
	return a.x2>b.x2;
}

inline bool cmp2(const Node& a,const Node& b){
	return a.y2>b.y2;
}

namespace TreeArray{
	#define lowbit(x) ( (x) & (-(x) ) )
	int unit[MAXN<<1];
	inline void Init(void){
		for(reg int i=1;i<2*MAXN;++i)
			unit[i]=INF;
		return;
	}
	inline void Clear(reg int ID){
		for(reg int i=ID;i<2*MAXN;i+=lowbit(i))
			unit[i]=INF;
		return;
	}
	inline void Update(reg int ID,int val){
		for(reg int i=ID;i<2*MAXN;i+=lowbit(i))
			unit[i]=min(unit[i],val);
		return;
	}
	inline int Query(reg int ID){
		int res=INF;
		for(reg int i=ID;i;i-=lowbit(i))
			res=min(res,unit[i]);
		return res;
	}
	#undef lowbit
}

using namespace TreeArray;

Node M[MAXN];

inline void Solve(reg int l,reg int r){
	if(l==r)
		return;
	reg int mid=(l+r)>>1;
	Solve(l,mid),Solve(mid+1,r);
	sort(M+l,M+mid+1,cmp2);
	sort(M+mid+1,M+r+1,cmp2);
	reg int j=l;
	for(reg int i=mid+1;i<=r;++i)
		if(!M[i].f){
			while(j<=mid&&M[j].y2>M[i].y2){
				Update(M[j].x1,M[j].y1);
				++j;
			}
			reg int temp=Query(M[i].x1);
			if(temp<M[i].y1)
				M[i].f=true;
		}
	while(--j>=l)
		Clear(M[j].x1);
	return;
}

int n;
vector<int> Vx,Vy;

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		M[i].Read();
		Vx.push_back(M[i].x1),Vx.push_back(M[i].x2);
		Vy.push_back(M[i].y1),Vy.push_back(M[i].y2);
	}
	sort(Vx.begin(),Vx.end());
	sort(Vy.begin(),Vy.end());
	for(reg int i=1;i<=n;++i){
		M[i].x1=lower_bound(Vx.begin(),Vx.end(),M[i].x1)-Vx.begin()+1;
		M[i].x2=lower_bound(Vx.begin(),Vx.end(),M[i].x2)-Vx.begin()+1;
		M[i].y1=lower_bound(Vy.begin(),Vy.end(),M[i].y1)-Vy.begin()+1;
		M[i].y2=lower_bound(Vy.begin(),Vy.end(),M[i].y2)-Vy.begin()+1;
	}
	sort(M+1,M+n+1,cmp1);
	Init();
	Solve(1,n);
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		ans+=(M[i].f?1:0);
	printf("%d\n",ans);
	return 0;
}