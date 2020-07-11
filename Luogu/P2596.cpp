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

const int MAXN=80000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int a[MAXN];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

struct Splay{
	int tot;
	int root;
	int fa[MAXN],ch[MAXN][2];
	int val[MAXN],size[MAXN];
	int rank[MAXN];
	inline int Build(reg int l,reg int r,reg int father,reg int a[]){
		if(l>r)
			return 0;
		reg int ID=++tot;
		if(father==0)
			root=ID;
		reg int mid=(l+r)>>1;
		fa[ID]=father,ch[ID][0]=ch[ID][1]=0;
		++size[ID];
		val[ID]=a[mid];
		rank[val[ID]]=ID;
		ch[ID][0]=Build(l,mid-1,ID,a),ch[ID][1]=Build(mid+1,r,ID,a);
		pushup(ID);
		return ID;
	}
	inline void pushup(reg int x){
		size[x]=size[ch[x][0]]+size[ch[x][1]]+1;
		rank[val[ch[x][0]]]=ch[x][0];
		rank[val[ch[x][1]]]=ch[x][1];
		return;
	}
	inline bool get(reg int x){
		return x==ch[fa[x]][1];
	}
	inline void rotate(reg int x){
		reg int f=fa[x],ff=fa[f];
		reg bool w=get(x);
		ch[f][w]=ch[x][w^1];
		fa[ch[f][w]]=f;
		fa[f]=x;
		fa[x]=ff;
		ch[x][w^1]=f;
		if(ff)
			ch[ff][ch[ff][1]==f]=x;
		pushup(f);
		pushup(x);
		return;
	}
	inline void splay(reg int x,reg int goal){
		for(reg int qwq;(qwq=fa[x])!=goal;rotate(x))
			if(fa[qwq]!=goal)
				rotate(get(x)==get(qwq)?qwq:x);
		if(goal==0)
			root=x;
		return;
	}
	inline int pre(reg int x){
		reg int ID=ch[x][0];
		while(ch[ID][1])
			ID=ch[ID][1];
		return ID;
	}
	inline int nxt(reg int x){
		reg int ID=ch[x][1];
		while(ch[ID][0])
			ID=ch[ID][0];
		return ID;
	}
	inline void Top(reg int x){
		reg int ID=rank[x];
		splay(ID,0);
		if(!ch[ID][0])
			return;
		if(!ch[ID][1])
			ch[ID][1]=ch[ID][0],ch[ID][0]=0;
		else{
			reg int y=nxt(ID);
			fa[ch[root][0]]=y;
			ch[y][0]=ch[root][0];
			ch[root][0]=0;
			splay(y,0);
		}
		return;
	}
	inline void Bottom(reg int x){
		reg int ID=rank[x];
		splay(ID,0);
		if(!ch[ID][1])
			return;
		if(!ch[ID][0])
			ch[ID][0]=ch[ID][1],ch[ID][1]=0;
		else{
			reg int y=pre(ID);
			fa[ch[root][1]]=y;
			ch[y][1]=ch[root][1];
			ch[root][1]=0;
			splay(y,0);
		}
		return;
	}
	inline void Insert(reg int x,reg int flag){
		if(!flag)
			return;
		reg int ID=rank[x];
		splay(ID,0);
		reg int y=(flag==1?nxt(ID):pre(ID));
		reg int v1=val[y],v2=rank[x];
		swap(rank[x],rank[v1]);
		swap(val[v2],val[y]);
		return;
	}
	inline int Ask(reg int x){
		reg int ID=rank[x];
		splay(ID,0);
		return size[ch[ID][0]];
	}
	inline int Query(reg int x){
		reg int ID=root;
		while(true){
			if(x<=size[ch[ID][0]])
				ID=ch[ID][0];
			else{
				x-=size[ch[ID][0]]+1;
				if(x<=0)
					return val[ID];
				else
					ID=ch[ID][1];
			}
		}
		return -1;
	}
};

Splay S;

inline void Work(void){
	S.Build(1,n,0,a);
	while(m--){
		static char ch;
		static int s,t;
		do
			ch=getchar();
		while(ch<'A'||'Z'<ch);
		switch(ch){
			case 'T':{
				s=read();
				S.Top(s);
				break;
			}
			case 'B':{
				s=read();
				S.Bottom(s);
				break;
			}
			case 'I':{
				s=read(),t=read();
				S.Insert(s,t);
				break;
			}
			case 'A':{
				s=read();
				printf("%d\n",S.Ask(s));
				break;
			}
			case 'Q':{
				s=read();
				printf("%d\n",S.Query(s));
				break;
			}
			default:break;
		}
	}
	return;
}
