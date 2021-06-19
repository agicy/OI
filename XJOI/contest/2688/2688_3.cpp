#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline void swap(reg int &x,reg int &y){
	reg int tmp=x;
	x=y,y=tmp;
	return;
}

const int MAXN=4e4+5;
const int MAXLOG2N=16+1;
const int MAXM=4e4+5;
const int MAXLOG2M=16+1;
const int MAXQ=4e4+5;

int n,m,q;

namespace Small{
	int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v){
		Add_Edge(u,v),Add_Edge(v,u);
		return;
	}
	int fa[MAXN],dep[MAXN];
	int siz[MAXN],son[MAXN];
	inline void dfs1(reg int u,reg int father){
		siz[u]=1;
		fa[u]=father;
		dep[u]=dep[father]+1;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				dfs1(v,u);
				if(siz[son[u]]<siz[v])
					son[u]=v;
			}
		}
		return;
	}
	int top[MAXN];
	inline void dfs2(reg int u,reg int father,reg int topf){
		top[u]=topf;
		if(!son[u])
			return;
		dfs2(son[u],u,topf);
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father&&v!=son[u])
				dfs2(v,u,v);
		}
		return;
	}
	inline int LCA(reg int x,reg int y){
		while(top[x]!=top[y])
			if(dep[top[x]]>dep[top[y]])
				x=fa[top[x]];
			else
				y=fa[top[y]];
		return dep[x]<dep[y]?x:y;
	}
	inline int getDis(reg int x,reg int y){
		return dep[x]+dep[y]-(dep[LCA(x,y)]<<1);
	}
}

namespace Big{
	int cnt,head[MAXN],to[MAXN<<1],st[MAXN<<1],ed[MAXN<<1],Next[MAXN<<1];
	inline void Add_Edge(reg int u,reg int v,reg int s,reg int e){
		Next[++cnt]=head[u];
		to[cnt]=v,st[cnt]=s,ed[cnt]=e;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v,reg int s,reg int e){
		Add_Edge(u,v,s,e),Add_Edge(v,u,e,s);
		return;
	}
	int fa[MAXM][MAXLOG2M],dep[MAXM];
	int dis[MAXM];
	int rt[MAXM],ptr[MAXM];
	inline void dfs(reg int u,reg int father,reg int e,reg int s){
		dep[u]=dep[father]+1;
		fa[u][0]=father;
		for(reg int i=1;(1<<i)<=dep[u];++i)
			fa[u][i]=fa[fa[u][i-1]][i-1];
		if(father)
			rt[u]=e,ptr[u]=s,dis[u]=dis[father]+Small::getDis(s,rt[father])+1;
		else
			rt[u]=1,ptr[u]=0,dis[u]=0;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father)
				dfs(v,u,ed[i],st[i]);
		}
		return;
	}
	inline int LCA(int x,int y){
		if(dep[x]>dep[y])
			swap(x,y);
		for(reg int i=MAXLOG2N-1;i>=0;--i)
			if(dep[fa[y][i]]>=dep[x])
				y=fa[y][i];
		if(x==y)
			return x;
		for(reg int i=MAXLOG2N-1;i>=0;--i)
			if(fa[x][i]!=fa[y][i])
				x=fa[x][i],y=fa[y][i];
		return fa[x][0];
	}
	inline pair<int,int> LCA_lower(int x,int y){
		if(dep[x]>dep[y])
			swap(x,y);
		for(reg int i=MAXLOG2N-1;i>=0;--i)
			if(dep[fa[y][i]]>dep[x])
				y=fa[y][i];
		if(fa[y][0]==x)
			return make_pair(y,0);
		if(dep[y]>dep[x])
			y=fa[y][0];
		for(reg int i=MAXLOG2N-1;i>=0;--i)
			if(fa[x][i]!=fa[y][i])
				x=fa[x][i],y=fa[y][i];
		return make_pair(x,y);
	}
}

bool ed;

int main(void){
	n=read(),m=read(),q=read();
	for(reg int i=1;i<n;++i){
		static int x,y;
		x=read(),y=read();
		Small::Add_Tube(x,y);
	}
	Small::dfs1(1,0),Small::dfs2(1,0,1);
	for(reg int i=1;i<m;++i){
		static int w,x,y,z;
		w=read(),x=read(),y=read(),z=read();
		Big::Add_Tube(w,y,x,z);
	}
	Big::dfs(1,0,1,0);

	/*
	puts("============");
	puts("Small:");
	for(reg int i=1;i<=n;++i)
		printf("i=%d fa=%d dep=%d\n",i,Small::fa[i][0],Small::dep[i]);
	puts("============");
	puts("Big:");
	for(reg int i=1;i<=m;++i)
		printf("i=%d fa=%d dep=%d dis=%lld rt=%d ptr=%d\n",i,Big::fa[i][0],Big::dep[i],Big::dis[i],Big::rt[i],Big::ptr[i]);
	puts("============");
	*/

	while(q--){
		static int w,x,y,z,part1,part2,part3,bLca;
		static pair<int,int> p;
		w=read(),x=read(),y=read(),z=read();
		//printf("query w=%d x=%d y=%d z=%d\n",w,x,y,z);
		if(w==y){
			//puts("S1");
			writeln(Small::getDis(x,z));
		}
		else{
			bLca=Big::LCA(w,y);
			if(bLca==w||bLca==y){
				//puts("S2");
				if(bLca==y)
					swap(w,y),swap(x,z);
				p=Big::LCA_lower(w,y);
				part1=Small::getDis(z,Big::rt[y]);
				part2=Big::dis[y]-Big::dis[p.first];
				part3=1+Small::getDis(Big::ptr[p.first],x);
				//printf("part1=%d part2=%d part3=%d\n",part1,part2,part3);
				writeln(part1+part2+part3);
			}
			else{
				//puts("S3");
				p=Big::LCA_lower(w,y);
				part1=Small::getDis(x,Big::rt[w])+Small::getDis(z,Big::rt[y]);
				part2=Big::dis[w]-Big::dis[p.first]+Big::dis[y]-Big::dis[p.second];
				part3=2+Small::getDis(Big::ptr[p.first],Big::ptr[p.second]);
				//printf("part1=%d part2=%d part3=%d\n",part1,part2,part3);
				writeln(part1+part2+part3);
			}
		}
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}