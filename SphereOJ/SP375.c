#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

typedef long long ll;
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define pc(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
char wbuf[1<<21];int wp1;const int wp2=1<<21;
int read(void){
	char ch=gc();
	int res=0;
	while(!isdigit(ch))ch=gc();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=gc();
	return res;
}

void swap(int *a,int *b){
	*a^=*b,*b^=*a,*a^=*b;
	return;
}

void writeln(int x){
	char buf[32];
	int p=-1;
	if(x==0) pc('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) pc(buf[p--]);
	pc('\n');
	return;
}

int max(int a,int b){
	return a>b?a:b;
}

#define MAXN 10005

int n;
int u[MAXN],v[MAXN],w[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

void Add_Edge(int u,int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int siz[MAXN],son[MAXN];

void dfs1(int u,int father){
	siz[u]=1;
	son[u]=0;
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(int i=head[u];i;i=Next[i]){
		int v=to[i];
		if(v!=father){
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
	}
	return;
}

int tim,dfn[MAXN];
int top[MAXN];

void dfs2(int u,int father,int topf){
	top[u]=topf;
	dfn[u]=++tim;
	if(!son[u])
		return;
	dfs2(son[u],u,topf);
	for(int i=head[u];i;i=Next[i]){
		int v=to[i];
		if(v!=father&&v!=son[u])
			dfs2(v,u,v);
	}
	return;
}


	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	typedef struct{
		int Max;
		#define Max(x) unit[(x)].Max
	} Node;
	Node unit[MAXN<<2];
	void pushup(int k){
		Max(k)=max(Max(lson),Max(rson));
		return;
	}
	void build(int k,int l,int r,int val[]){
		if(l==r){
			Max(k)=val[l];
			return;
		}
		build(lson,l,mid,val),build(rson,mid+1,r,val);
		pushup(k);
		return;
	}
	void update(int k,int l,int r,int pos,int val){
		if(l==r){
			Max(k)=val;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	int query(int k,int l,int r,int L,int R){
		if(L<=l&&r<=R)
			return Max(k);
		if(L<=mid&&mid<R)
			return max(query(lson,l,mid,L,R),query(rson,mid+1,r,L,R));
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid


int Query(int x,int y){
	int res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(&x,&y);
		res=max(res,query(1,1,n,dfn[top[y]],dfn[y]));
		y=fa[top[y]];
	}
	if(dep[x]>dep[y])
		swap(&x,&y);
	if(dfn[x]<dfn[y])
		res=max(res,query(1,1,n,dfn[x]+1,dfn[y]));
	return res;
}

int main(void){
	int t=read();
	while(t--){
		n=read();
		cnt=0;
		for(int i=1;i<=n;++i)
			head[i]=0;
		tim=0;
		for(int i=1;i<n;++i){
			u[i]=read(),v[i]=read(),w[i]=read();
			Add_Edge(u[i],v[i]),Add_Edge(v[i],u[i]);
		}
		dfs1(1,0),dfs2(1,0,1);
		int val[MAXN];
		for(int i=1;i<n;++i){
			int son=dep[u[i]]>dep[v[i]]?u[i]:v[i];
			val[dfn[son]]=w[i];
		}
		build(1,1,n,val);
		int flag=1;
		while(flag){
			char opt;
			int a,b;
			do
				opt=gc();
			while(!isalpha(opt));
			switch(opt){
				case 'Q':{
					a=read(),b=read();
					writeln(Query(a,b));
					break;
				}
				case 'C':{
					a=read(),b=read();
					int son=dep[u[a]]>dep[v[a]]?u[a]:v[a];
					update(1,1,n,dfn[son],b);
					break;
				}
				case 'D':{
					flag=0;
					break;
				}
			}
		}
	}
	flush();
	return 0;
}