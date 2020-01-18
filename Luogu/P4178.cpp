#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

const int MAXN=40000+5;
const int MAXK=20000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
int K;

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int a,b,c;
		a=read(),b=read(),c=read();
		Add_Edge(a,b,c);
		Add_Edge(b,a,c);
	}
	K=read();
	return;
}

int root,sum;
int size[MAXN],MaxSon[MAXN];
bool del[MAXN];

inline void GetRoot(reg int ID,reg int father){
	size[ID]=1,MaxSon[ID]=0;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father&&!del[to[i]]){
			GetRoot(to[i],ID);
			size[ID]+=size[to[i]];
			MaxSon[ID]=max(MaxSon[ID],size[to[i]]);
		}
	MaxSon[ID]=max(MaxSon[ID],sum-size[ID]);
	if(MaxSon[ID]<MaxSon[root])
		root=ID;
	return;
}

int tot,v[MAXN],dis[MAXN];

inline void DFS(reg int ID,reg int father){
	v[++tot]=dis[ID];
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father&&!del[to[i]]){
			dis[to[i]]=dis[ID]+w[i];
			DFS(to[i],ID);
		}
	return;
}

ll ans;
int Q[MAXN];

struct TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n,unit[MAXK];
	inline void Init(reg int size){
		n=size;
		memset(unit,0,sizeof(unit));
	}
	inline void Update(reg int ID,reg int val){
		while(ID<=n){
			unit[ID]+=val;
			ID+=lowbit(ID);
		}
		return;
	}
	inline int Query(reg int ID){
		reg int res=0;
		while(ID){
			res+=unit[ID];
			ID-=lowbit(ID);
		}
		return res;
	}
	#undef lowbit
};

TreeArray T;

inline void Calc(reg int ID){
	reg int p=0;
	for(reg int i=head[ID];i;i=Next[i]){
		if(!del[to[i]]){
			tot=0;
			dis[to[i]]=w[i];
			DFS(to[i],0);
			for(reg int i=1;i<=tot;++i)
				if(v[i]<K)
					ans+=T.Query(K-v[i])+1;
				else if(v[i]==K)
					++ans;
			for(reg int i=1;i<=tot;++i)
				if(v[i]<=K)
					T.Update(v[i],1),Q[++p]=v[i];
		}
	}
	for(reg int i=1;i<=p;++i)
		T.Update(Q[i],-1);
	return;
}

inline void Solve(reg int ID){
	del[ID]=true;
	Calc(ID);
	for(reg int i=head[ID];i;i=Next[i]){
		if(!del[to[i]]){
			sum=size[to[i]];
			MaxSon[root=0]=INF;
			GetRoot(to[i],0);
			Solve(root);
		}
	}
	return;
}

inline void Work(void){
	T.Init(K+2);
	MaxSon[root=0]=sum=n;
	GetRoot(1,0);
	Solve(root);
	printf("%lld\n",ans);
	return;
}
