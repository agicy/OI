#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=300000+5;
const int MAXM=300000+5;
const int MAXXY=1000000+5;

struct Node{
	bool type;
	int x,y,t;
	inline Node(reg bool type=false,reg int x=0,reg int y=0,reg int t=0):type(type),x(x),y(y),t(t){
		return;
	}
	inline bool operator<(const Node &a)const{
		return x<a.x;
	}
};

struct TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n,unit[MAXXY];
	inline void Init(reg int tot){
		n=tot;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void Update(reg int ID,int val){
		for(reg int i=ID;i<=n;i+=lowbit(i))
			unit[i]=max(unit[i],val);
		return;
	}
	inline int Query(reg int ID){
		int res=0;
		for(reg int i=ID;i;i-=lowbit(i))
			res=max(res,unit[i]);
		return res;
	}
	inline void Clear(reg int ID){
		for(reg int i=ID;i<=n;i+=lowbit(i))
			if(unit[i])
				unit[i]=0;
			else
				break;
		return;
	}
	#undef lowbit
};

int n,m;
int Maxx,Maxy;
int ans[MAXN+MAXM];
int tot,cnt;
TreeArray T;
Node Q[MAXN+MAXM],back[MAXN+MAXM];

inline void Init(void){
	int rx=0,ry=0;
	static Node temp[MAXN+MAXM];
	cnt=0;
	for(reg int i=1;i<=tot;++i)
		if(!Q[i].type)
			rx=max(rx,Q[i].x),ry=max(ry,Q[i].y);
	for(reg int i=1;i<=tot;++i)
		if(Q[i].x<=rx&&Q[i].y<=ry)
			temp[++cnt]=Q[i];
	for(reg int i=1;i<=cnt;++i)
		Q[i]=temp[i];
	return;
}

inline void Solve(reg int l,reg int r){
	if(l==r)
		return;
	reg int mid=(l+r)>>1;
	Solve(l,mid),Solve(mid+1,r);
	reg int j=l;
	for(reg int i=mid+1;i<=r;++i)
		if(!Q[i].type){
			while(j<=mid&&Q[j].x<=Q[i].x){
				if(Q[j].type)
					T.Update(Q[j].y,Q[j].x+Q[j].y);
				++j;
			}
			reg int temp=T.Query(Q[i].y);
			if(temp)
				ans[Q[i].t]=min(ans[Q[i].t],Q[i].x+Q[i].y-temp);
		}
	for(reg int i=l;i<j;++i)
		if(Q[i].type)
			T.Clear(Q[i].y);
	static Node temp[MAXN+MAXM];
	merge(Q+l,Q+mid+1,Q+mid+1,Q+r+1,temp+l);
	for(reg int i=l;i<=r;++i)
		Q[i]=temp[i];
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		static int x,y;
		x=read()+1,y=read()+1;
		++tot;
		Q[tot]=Node(true,x,y,tot);
		Maxx=max(Maxx,x),Maxy=max(Maxy,y);
	}
	while(m--){
		static int k,x,y;
		k=read(),x=read()+1,y=read()+1;
		++tot;
		Q[tot]=Node(k&1,x,y,tot);
		Maxx=max(Maxx,x),Maxy=max(Maxy,y);
	}
	for(reg int i=1;i<=tot;++i)
		back[i]=Q[i];
	memset(ans,0X3F,sizeof(ans));
	T.Init(Maxy);
	Init();
	Solve(1,cnt);
	for(reg int i=1;i<=tot;++i){
		Q[i]=back[i];
		Q[i].x=Maxx-back[i].x+1;
	}
	Init();
	Solve(1,cnt);
	for(reg int i=1;i<=tot;++i){
		Q[i]=back[i];
		Q[i].y=Maxy-back[i].y+1;
	}
	Init();
	Solve(1,cnt);
	for(reg int i=1;i<=tot;++i){
		Q[i]=back[i];
		Q[i].x=Maxx-back[i].x+1;
		Q[i].y=Maxy-back[i].y+1;
	}
	Init();
	Solve(1,cnt);
	for(reg int i=1;i<=tot;++i)
		if(back[i].type==false)
			printf("%d\n",ans[i]);
	return 0;
}
