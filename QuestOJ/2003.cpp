#include<cstdio>
#include<algorithm>
using std::max;
#include<iostream>
using std::cin;
#define reg register

const int MAXN=100000+5;

int n;
int cnt,head[MAXN],to[MAXN],w[MAXN],Next[MAXN];
int fa[MAXN],son[MAXN],size[MAXN],dep[MAXN];
int tot,lft[MAXN],rig[MAXN],rank[MAXN];
int T[1<<23];
int ans[MAXN],dis[MAXN];

inline void Read(void);
inline void Work(void);
inline void Add_Edge(reg int,reg int,reg int);
inline void DFS1(reg int);
inline void DFS2(reg int,reg bool);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	scanf("%d",&n);
	for(reg int i=2;i<=n;++i){
		static char ch;
		scanf("%d",&fa[i]);
		cin>>ch;
		Add_Edge(fa[i],i,1<<(ch-'a'));
	}
	return;
}

inline void Work(void){
	DFS1(1);
	DFS2(1,true);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",ans[i],i==n?'\n':' ');
	return;
}

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void DFS1(reg int ID){
	lft[ID]=++tot;
	size[ID]=1;
	dep[ID]=dep[fa[ID]]+1;
	rank[tot]=ID;
	for(reg int i=head[ID];i;i=Next[i]){
		dis[to[i]]=dis[ID]^w[i];
		DFS1(to[i]);
		size[ID]+=size[to[i]];
		if(size[son[ID]]<size[to[i]])
			son[ID]=to[i];
	}
	rig[ID]=tot;
	return;
}

inline void DFS2(reg int ID,reg bool save){
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=son[ID]){
			DFS2(to[i],false);
			ans[ID]=max(ans[ID],ans[to[i]]);
		}
	if(son[ID]){
		DFS2(son[ID],true);
		ans[ID]=max(ans[ID],ans[son[ID]]);
	}
	if(T[dis[ID]])
		ans[ID]=max(ans[ID],T[dis[ID]]-dep[ID]);
	for(reg int i=0;i<=21;++i)
		if(T[dis[ID]^(1<<i)])
			ans[ID]=max(ans[ID],T[dis[ID]^(1<<i)]-dep[ID]);
	T[dis[ID]]=max(T[dis[ID]],dep[ID]);
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=son[ID]){
			for(reg int id=lft[to[i]];id<=rig[to[i]];++id){
				reg int p_id=rank[id];
				if(T[dis[p_id]])
					ans[ID]=max(ans[ID],dep[p_id]+T[dis[p_id]]-(dep[ID]<<1));
				for(reg int k=0;k<=21;++k)
					if(T[dis[p_id]^(1<<k)])
						ans[ID]=max(ans[ID],T[dis[p_id]^(1<<k)]+dep[p_id]-(dep[ID]<<1));
			}
			for(reg int id=lft[to[i]];id<=rig[to[i]];++id)
				T[dis[rank[id]]]=max(T[dis[rank[id]]],dep[rank[id]]);
		}
	if(save==false)
		for(reg int id=lft[ID];id<=rig[ID];++id)
			T[dis[rank[id]]]=0;
	return;
}
