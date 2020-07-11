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

const int MAXN=100000+100;

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
	int root;
	int val[MAXN],Max[MAXN],tag[MAXN];
	int fa[MAXN],ch[MAXN][2];
	int size[MAXN];
	inline bool get(const int& x){
		return x==ch[fa[x]][1];
	}
	inline void pushup(const int& ID){
		Max[ID]=max(val[ID],max(Max[ch[ID][0]],Max[ch[ID][1]]));
		size[ID]=size[ch[ID][0]]+size[ch[ID][1]]+1;
		return;
	}
	inline int Build(const int& father,const int& l,const int& r,reg int a[]){
		if(l>r)
			return 0;
		int mid=(l+r)>>1;
		val[mid]=Max[mid]=a[mid];
		fa[mid]=father;
		size[mid]=1;
		ch[mid][0]=Build(mid,l,mid-1,a);
		ch[mid][1]=Build(mid,mid+1,r,a);
		pushup(mid);
		return mid;
	}
	inline void rotate(const int& x){
		int f=fa[x],ff=fa[f];
		reg bool wh=get(x);
		if(ff)
			ch[ff][get(f)]=x;
		fa[f]=x;
		ch[f][wh]=ch[x][wh^1];
		if(ch[f][wh])
			fa[ch[f][wh]]=f;
		fa[x]=ff;
		ch[x][wh^1]=f;
		pushup(f);
		pushup(x);
		return;
	}
	inline void add(const int& ID,const int& Val){
		val[ID]+=Val,Max[ID]+=Val,tag[ID]+=Val;
		return;
	}
	inline void pushdown(const int& ID){
		if(tag[ID]){
			if(ch[ID][0])
				add(ch[ID][0],tag[ID]);
			if(ch[ID][1])
				add(ch[ID][1],tag[ID]);
			tag[ID]=0;
		}
		return;
	}
	inline void push(const int& x){
		if(fa[x])
			push(fa[x]);
		pushdown(x);
		return;
	}
	inline void splay(const int& x,const int& goal){
		push(x);
		for(int qwq;(qwq=fa[x])!=goal;rotate(x)){
			if(fa[qwq]!=goal){
				rotate(get(x)==get(qwq)?qwq:x);
			}
		}
		if(goal==0)
			root=x;
		return;
	}
	inline int find(const int& x){
		int now=root,res=0;
		while(true){
			pushdown(now);
			if(x<=Max[ch[now][0]])
			    now=ch[now][0];
			else{
				res+=size[ch[now][0]];
				if(x<=val[now])
					return res+1;
				++res;
				now=ch[now][1];
			}
		}
		return -1;
	}
	inline int kth(reg int x){
		int now=root;
		while(true){
			pushdown(now);
			if(x<=size[ch[now][0]])
			    now=ch[now][0];
			else{
				x-=size[ch[now][0]];
				if(x==1){
					splay(now,0);
					return now;
				}
				--x;
				now=ch[now][1];
			}
		}
		return -1;
	}
	inline int split(const int& l,const int& r){
		int x=kth(l),y=kth(r+2);
		splay(x,0),splay(y,x);
		return y;
	}
	inline void F(const int& c,const int& h){
		int l=find(h)-1,r=min(n,l+c-1);
		if(l>n)
			return;
		int mid=find(val[kth(r+1)])-1,tr=ch[split(mid,r)][0];
		fa[tr]=ch[fa[tr]][0]=0;
		++tag[tr],++val[tr],++Max[tr];
		if(mid>l){
			reg int now=ch[split(l,mid-1)][0];
			++tag[now],++val[now],++Max[now];
		}
		int p=find(val[tr])-1,u=split(p,p-1);
		fa[tr]=u,ch[u][0]=tr;
		splay(tr,0);
		return;
	}
	inline int C(const int& Max,const int& Min){
		int l=find(Max)-1,r=find(Min+1)-2;
		return size[ch[split(l,r)][0]];
	}
};

Splay S;

inline void Work(void){
	S.Max[0]=-INF;
	a[n+1]=-INF,a[n+2]=INF;
	sort(a+1,a+n+3);
	S.root=S.Build(0,1,n+2,a);
	while(m--){
		static char opt;
		static int c,h,max,min;
		do
			opt=getchar();
		while(opt!='F'&&opt!='C');
		switch(opt){
			case 'F':{
				c=read(),h=read();
				S.F(c,h);
				break;
			}
			case 'C':{
				max=read(),min=read();
				printf("%d\n",S.C(max,min));
				break;
			}
			default:break;
		}
	}
	return;
}
