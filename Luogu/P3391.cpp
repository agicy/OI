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

const int MAXN=100000+5;

struct Splay{
	int root,tot;
	int val[MAXN],cnt[MAXN],tag[MAXN];
	int size[MAXN];
	int fa[MAXN];
	int ch[MAXN][2];
	inline bool get(reg int x){
		return x==ch[fa[x]][1];
	}
	inline void update(reg int x){
		if(x){
			size[x]=cnt[x];
			if(ch[x][0])
				size[x]+=size[ch[x][0]];
			if(ch[x][1])
				size[x]+=size[ch[x][1]];
		}
		return;
	}
	inline void pushdown(reg int x){
		if(x&&tag[x]){
			tag[ch[x][0]]^=1;
			tag[ch[x][1]]^=1;
			swap(ch[x][0],ch[x][1]);
			tag[x]=0;
		}
		return;
	}
	inline void rotate(reg int x){
		reg int f=fa[x],ff=fa[f];
		pushdown(x),pushdown(f);
		bool w=get(x);
		ch[f][w]=ch[x][w^1];
		fa[ch[f][w]]=f;
		fa[f]=x;
		fa[x]=ff;
		ch[x][w^1]=f;
		if(ff)
			ch[ff][ch[ff][1]==f]=x;
		update(f);
		return;
	}
	inline void splay(reg int x,reg int goal){
		for(reg int qwq;(qwq=fa[x])!=goal;rotate(x)){
			if(fa[qwq]!=goal){
				rotate(get(x)==get(qwq)?qwq:x);
			}
		}
		if(goal==0)
			root=x;
		return;
	}
	inline int build(reg int l,reg int r,reg int father,reg int a[]){
		if(l>r)
			return 0;
		reg int mid=(l+r)>>1;
		reg int now=++tot;
		fa[now]=father;
		ch[now][0]=ch[now][1]=0;
		++cnt[now];
		val[now]=a[mid];
		++size[now];
		ch[now][0]=build(l,mid-1,now,a);
		ch[now][1]=build(mid+1,r,now,a);
		update(now);
		return now;
	}
	inline int find(reg int x){
		int now=root;
		while(true){
			pushdown(now);
			if(x<=size[ch[now][0]])
				now=ch[now][0];
			else{
				x-=size[ch[now][0]]+1;
				if(!x)
					return now;
				now=ch[now][1];
			}
		}
	}
	inline void Print(reg int ID){
		pushdown(ID);
		if(ch[ID][0])
			Print(ch[ID][0]);
		if(val[ID]!=-INF&&val[ID]!=INF)
			printf("%d ",val[ID]);
		if(ch[ID][1])
			Print(ch[ID][1]);
		return;
	}
};

int n,m;
int a[MAXN];
Splay T;

int main(void){
	n=read(),m=read();
	a[1]=-INF,a[n+2]=INF;
	for(reg int i=1;i<=n;++i)
		a[i+1]=i;
	T.root=T.build(1,n+2,0,a);
	while(m--){
		static int l,r;
		l=read()+1,r=read()+1;
		reg int l_=T.find(l-1),r_=T.find(r+1);
		T.splay(l_,0);
		T.splay(r_,l_);
		reg int pos=T.ch[T.root][1];
		pos=T.ch[pos][0];
		T.tag[pos]^=1;
	}
	T.Print(T.root);
	putchar('\n');
	return 0;
}
