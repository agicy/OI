#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 1e9
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

const long double eps=1e-8;

inline int sgn(reg double x){
	if(fabs(x)<eps)
		return 0;
	else if(x>0)
		return 1;
	else
		return -1;
}

const int MAXN=500+5;

inline void Read(void);
inline void Work(void);

int main(void){
	reg int T=read();
	while(T--){
		Read();
		Work();
	}
	return 0;
}

struct Node{
	int x,y;
	inline void Read(void){
		x=read(),y=read();
		return;
	}
};

inline double GetDis(const Node& a,const Node& b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

inline double GetAng(const Node& a,const Node& b){
	return atan2(b.y-a.y,b.x-a.x);
}

int n,m;
Node nail[MAXN];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		nail[i].Read();
	return;
}

struct Edge{
	double angle,length;
	int to;
	inline Edge(reg double angle=0,reg double length=0,reg int to=0):angle(angle),length(length),to(to){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return sgn(angle-a.angle)==0?sgn(length-a.length)<0:sgn(angle-a.angle)<0;
	}
};

double Min[MAXN];
Edge C[MAXN][MAXN];

int tim,vis[MAXN][MAXN];
int Las[MAXN][MAXN];
long double His[MAXN][MAXN];

inline void Solve(reg double angle,reg long double L){
	++tim;
	angle-=eps;
	reg int ans=1,now=0;
	while(sgn(L-Min[now])>=0){
		reg int cnt=(now==0)?n:n-1;
		reg int l=1,r=cnt,res=-1;
		while(l<=r){
			reg int mid=(l+r)>>1;
			if(sgn(C[now][mid].angle-angle)>=0){
				res=mid;
				r=mid-1;
			}
			else
				l=mid+1;
		}
		if(res==-1)
			res=cnt;
		else
			res=(res+cnt-2)%cnt+1;
		reg int t=res;
		while(sgn(L-C[now][t].length)<0)
			t=(t+cnt-2)%cnt+1;
		L-=C[now][t].length;
		angle=C[now][t].angle;
		reg int nxt=C[now][t].to;
		if(vis[now][nxt]==tim){
			reg long double delta=His[now][nxt]-L;
			reg int cycle=floor(L/delta);
			ans+=cycle*(ans-Las[now][nxt]+1);
			L-=cycle*delta;
		}
		++ans;
		vis[now][nxt]=tim;
		Las[now][nxt]=ans;
		His[now][nxt]=L;
		now=nxt;
	}
	printf("%d\n",ans);
	return;
}

inline void Work(void){
	for(reg int i=1;i<=n;++i){
		reg int cnt=0;
		Min[i]=INF;
		for(reg int j=1;j<=n;++j)
			if(i!=j){
				double Dis=GetDis(nail[i],nail[j]);
				C[i][++cnt]=Edge(GetAng(nail[i],nail[j]),Dis,j);
				Min[i]=min(Min[i],Dis);
			}
		sort(C[i]+1,C[i]+cnt+1);
	}
	while(m--){
		static int L;
		static Node s,t;
		s.Read(),t.Read(),L=read();
		nail[0]=s;
		Min[0]=INF;
		for(reg int i=1;i<=n;++i){
			double Dis=GetDis(nail[0],nail[i]);
			C[0][i]=Edge(GetAng(nail[0],nail[i]),Dis,i);
			Min[0]=min(Min[0],Dis);
		}
		sort(C[0]+1,C[0]+n+1);
		Solve(GetAng(s,t),L);
	}
	return;
}
