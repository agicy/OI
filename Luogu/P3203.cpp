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

const int MAXN=200000+5;
const int MAXM=200000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int K[MAXN];

namespace LCT{
	#define lson ch[p][0]
	#define rson ch[p][1]
	int fa[MAXN],ch[MAXN][2];
	int size[MAXN];
	inline bool get(reg int p){
		return ch[fa[p]][1]==p;
	}
	inline bool isroot(reg int p){
		return ch[fa[p]][0]!=p&&ch[fa[p]][1]!=p;
	}
	inline void pushup(reg int p){
		size[p]=size[lson]+size[rson]+1;
		return;
	}
	inline void rotate(reg int x){
		reg int y=fa[x],z=fa[y],k=ch[y][1]==x,w=ch[x][!k];
		if(!isroot(y))
			ch[z][get(y)]=x;
		ch[x][!k]=y;
		ch[y][k]=w;
		if(w)
			fa[w]=y;
		fa[y]=x,fa[x]=z;
		pushup(y);
		return;
	}
	inline void splay(reg int p){
		for(reg int f=fa[p];f=fa[p],!isroot(p);rotate(p))
			if(!isroot(f))
				rotate(get(f)==get(p)?f:p);
		pushup(p);
		return;
	}
	inline void access(reg int p){
		for(reg int pre=0;p;pre=p,p=fa[p])
			splay(p),rson=pre,pushup(p);
		return;
	}
	#undef lson
	#undef rson
}

using namespace LCT;

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static int K;
		size[i]=1;
		K=read();
		if(i+K<=n)
			fa[i]=i+K;
	}
	return;
}

inline void Work(void){
	reg int m=read();
	while(m--){
		static int opt,i,j;
		opt=read();
		switch(opt){
			case 1:{
				i=read()+1;
				access(i),splay(i);
				printf("%d\n",size[i]);
				break;
			}
			case 2:{
				i=read()+1,j=read();
				access(i),splay(i);
				ch[i][0]=fa[ch[i][0]]=0;
				if(i+j<=n)
					fa[i]=i+j;
				pushup(i);
				break;
			}
			default:break;
		}
	}
	return;
}