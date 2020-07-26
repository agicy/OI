#include<bits/stdc++.h>
using namespace std;
#define reg register
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
inline void read(char* str){
	reg char ch=getchar();
	while(ch<'A'||'Z'<ch)ch=getchar();
	while('A'<=ch&&ch<='Z')(*str++)=ch,ch=getchar();
	return;
}

const int MAXN=1000000+5;
const int MAXM=1000000+5;

inline void Init(void);
inline void Read(void);
inline void Work(void);

int C;

int main(void){
	reg int C=read();
	while(C--){
		Init();
		Read();
		Work();
	}
	return 0;
}

int n,m;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
char val[MAXN];
char pre[MAXN],suf[MAXN];
ull ans;

inline void Add_Edge(const int& u,const int& v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Add_Tube(const int& u,const int& v){
	Add_Edge(u,v);
	Add_Edge(v,u);
	return;
}

inline void fix(reg char *val){
	while(*val){
		*val=*val-'A'+1;
		++val;
	}
	return;
}

inline void copy(reg char *str,const int& m,const int& n){
	for(reg int i=m+1;i<=n;++i)
		str[i]=str[i-m];
	return;
}

const ull base=31;
ull basep[MAXN];
ull prehash[MAXN],sufhash[MAXN];

inline void gethash(reg char *str,reg ull *hash,const int& n){
	for(reg int i=1;i<=n;++i)
		hash[i]=hash[i-1]*base+str[i];
	return;
}

inline void Read(void){
	n=read(),m=read();
	read(val+1);
	fix(val+1);
	basep[0]=1;
	for(reg int i=1;i<=n;++i)
		basep[i]=basep[i-1]*base;
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Tube(u,v);
	}
	read(pre+1);
	fix(pre+1);
	for(reg int i=1;i<=m;++i)
		suf[i]=pre[m-i+1];
	copy(pre,m,n);
	copy(suf,m,n);
	gethash(pre,prehash,n);
	gethash(suf,sufhash,n);
	return;
}

bool del[MAXN];
int size[MAXN],Max[MAXN];

inline void GetRoot(int ID,const int& father,const int& sum,reg int& root){
	size[ID]=1,Max[ID]=0;
	for(reg int i=head[ID];i;i=Next[i])
		if(!del[to[i]]&&to[i]!=father){
			GetRoot(to[i],ID,sum,root);
			size[ID]+=size[to[i]];
			Max[ID]=max(Max[ID],size[to[i]]);
		}
	Max[ID]=max(Max[ID],sum-size[ID]);
	if(Max[ID]<=Max[root])
		root=ID;
	return;
}

int Tpre[MAXN],Tsuf[MAXN];
int sumpre[MAXN],sumsuf[MAXN];

inline void DFS(int ID,const int& father,const int& dep,reg int &Maxdep,const char& mid,reg ull Hash){
	Maxdep=max(Maxdep,dep);
	Hash+=val[ID]*basep[dep-1];
	if(Hash==prehash[dep]){
		++Tpre[dep%m];
		if(mid==pre[dep%m+1])
			ans+=sumsuf[m-dep%m-1];
	}
	if(Hash==sufhash[dep]){
		++Tsuf[dep%m];
		if(mid==suf[dep%m+1])
			ans+=sumpre[m-dep%m-1];
	}
	for(reg int i=head[ID];i;i=Next[i])
		if(!del[to[i]]&&to[i]!=father)
			DFS(to[i],ID,dep+1,Maxdep,mid,Hash);
	return;
}

inline void Calc(const int& ID){
	if(val[ID]==pre[1])
		++sumpre[0];
	if(val[ID]==suf[1])
		++sumsuf[0];
	int Tag=0;
	for(reg int i=head[ID];i;i=Next[i])
		if(!del[to[i]]){
			int Max=0;
			DFS(to[i],ID,1,Max,val[ID],0);
			Tag=max(Tag,Max);
			for(reg int i=0;i<=Max;++i)
				sumpre[i]+=Tpre[i],sumsuf[i]+=Tsuf[i],Tpre[i]=Tsuf[i]=0;
		}
	for(reg int i=0;i<=Tag;++i)
		sumpre[i]=sumsuf[i]=0;
	return;
}

inline void Solve(int ID,const int& sum){
	if(sum<m)
		return;
	int root=0;
	Max[root=0]=INF;
	GetRoot(ID,-1,sum,root);
	del[root]=true;
	Calc(root);
	for(reg int i=head[root];i;i=Next[i])
		if(!del[to[i]])
			Solve(to[i],size[to[i]]<size[root]?size[to[i]]:sum-size[root]);
	return;
}

inline void Work(void){
	Solve(1,n);
	printf("%llu\n",ans);
	return;
}

inline void Init(void){
	cnt=0;
	ans=0;
	memset(del,0,sizeof(del));
	memset(head,0,sizeof(head));
	return;
}
