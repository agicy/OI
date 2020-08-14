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

const int MAXN=5e3+5;
const int MAXM=1e5+5;

int n,m,k;
vector<int> vec,V;
ll Max[MAXN];
bitset<MAXM> no;

int cnt=1,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1],id[MAXM<<1];
bitset<MAXM<<1> del;

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

int fa[MAXN];

inline int find(reg int x){
	if(x==fa[x])
		return x;
	else
		return fa[x]=find(fa[x]);
}


struct Edge{
	int u,v,w,id;
	inline Edge(reg int u=0,reg int v=0,reg int w=0,reg int id=0):u(u),v(v),w(w),id(id){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return w<a.w;
	}
};

Edge E[MAXM];

inline void GetMax(reg int u,reg int father){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&!del[i]&&v!=1){
			if(w[i]>=w[Max[u]])
				Max[v]=i;
			else
				Max[v]=Max[u];
			GetMax(v,u);
		}
	}
	return;
}

int main(void){
	n=read(),m=read(),k=read();
	cnt=1;
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		E[i]=Edge(u,v,w,i);
	}
	for(reg int i=1;i<=n;++i)
		fa[i]=i;
	sort(E+1,E+m+1);
	for(reg int i=1;i<=m;++i){
		reg int u=find(E[i].u),v=find(E[i].v);
		if(u!=v&&u!=1&&v!=1){
			fa[u]=v;
			V.push_back(E[i].id);
			Add_Edge(E[i].u,E[i].v,E[i].w);
			Add_Edge(E[i].v,E[i].u,E[i].w);
			id[cnt]=id[cnt-1]=E[i].id;
		}
	}
	for(int i=1;i<=m;++i)
		if(E[i].u==1||E[i].v==1){
			reg int u=find(E[i].u),v=find(E[i].v);
			if(u==v)
				vec.push_back(i);
			else{
				fa[u]=v;
				Add_Edge(E[i].u,E[i].v,E[i].w);
				Add_Edge(E[i].v,E[i].u,E[i].w);
				V.push_back(E[i].id);
				--k;
			}
		}
	for(reg int i=2;i<=n;++i)
		if(find(i)!=find(i-1)){
			puts("-1");
			return 0;
		}
	if(k<0){
		puts("-1");
		return 0;
	}
	for(reg int i=1;i<=k;++i){
		if(!vec.size()){
			puts("-1");
			return 0;
		}
		memset(Max,0,sizeof(Max));
		for(reg int j=head[1];j;j=Next[j])
			GetMax(to[j],1);
		reg int now=-1,ans=2147483647;
		for(reg int j=vec.size()-1;j>=0;--j){
			reg int p=vec[j];
			reg int var=max(E[p].u,E[p].v);
			if(E[p].w-w[Max[var]]<ans){
				ans=E[p].w-w[Max[var]];
				now=j;
			}
		}
		reg int p=vec[now];
		reg int var=E[p].u==1?E[p].v:E[p].u;
		Add_Edge(E[p].v,E[p].u,E[p].w);
		V.push_back(E[p].id);
		no[id[Max[var]]]=true;
		del[Max[var]]=del[Max[var]^1]=true;
		vec.erase(vec.begin()+now);
	}
	printf("%d\n",n-1);
	vector<int> ans;
	for(reg int i=V.size()-1;i>=0;--i)
		if(!no[V[i]])
			ans.push_back(V[i]);
	for(reg int i=0,size=ans.size();i<size;++i)
		printf("%d%c",ans[i],i==size-1?'\n':' ');
	return 0;
}