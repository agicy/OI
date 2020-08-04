#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;/*
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}*/

const int N=2100000;

namespace Splay{
	struct Node{
		int fa,ch[2];
		int size;
		char c;
		#define fa(x) unit[(x)].fa
		#define ch(x) unit[(x)].ch
		#define size(x) unit[(x)].size
		#define c(x) unit[(x)].c
	};
	int tot,root;
	Node unit[N];
	inline void pushup(reg int k){
		size(k)=size(ch(k)[0])+size(ch(k)[1])+1;
		return;
	}
	inline bool check(reg int x){
		return ch(fa(x))[1]==x;
	}
	inline void rootate(reg int x){
		reg int y=fa(x),z=fa(y),k=check(x),w=ch(x)[!k];
		ch(y)[k]=w,fa(w)=y;
		ch(z)[check(y)]=x,fa(x)=z;
		ch(x)[!k]=y,fa(y)=x;
		pushup(y),pushup(x);
		return;
	}
	inline void splay(reg int x,reg int goal=0){
		for(reg int f;f=fa(x),f!=goal;rootate(x))
			if(fa(f)!=goal)
				rootate(check(x)==check(f)?f:x);
		if(!goal)
			root=x;
		return;
	}
	inline int kth(reg int k){
		reg int p=root;
		while(true)
			if(k<size(ch(p)[0]))
				p=ch(p)[0];
			else{
				if(size(ch(p)[0])+1<k){
					k-=size(ch(p)[0])+1;
					p=ch(p)[1];
				}
				else
					return p;
			}
	}
	inline int build(reg int l,reg int r,reg int father,reg char str[]){
		reg int k=++tot;
		reg int mid=(l+r)>>1;
		c(k)=str[mid],fa(k)=father;
		if(l<mid)
			ch(k)[0]=build(l,mid,k,str);
		if(mid<r)
			ch(k)[1]=build(mid+1,r,k,str);
		pushup(k);
		return k;
	}
	inline void print(reg int k){
		printf("k=%d\n",k);
		if(ch(k)[0])
			print(ch(k)[0]);
		putchar(c(k));
		if(ch(k)[1])
			print(ch(k)[1]);
		return;
	}
	inline void split(reg int x,reg int y){
		splay(x),splay(y,x);
		return;
	}
}

using namespace Splay;

char ch[]="   ";

int main(void){
	int t;
	scanf("%d",&t);
	c(0)=' ';
	root=1;
	ch(0)[0]=build(1,2,0,ch);
	reg int ptr=0;
	reg int n=0,totlen=0;
	while(t--){
		static char opt[16],s[1048576];
		scanf("%s",opt);
		printf("t=%d\n",t);
		printf("opt=%s\n",opt);
		switch(opt[0]){
			case 'M':{
				scanf("%d",&ptr);
				//ptr=read();
				break;
			}
			case 'I':{
				scanf("%d",&n);
				//n=read();
				for(reg int i=1;i<=n;++i){
					s[i]=getchar();
					if(s[i]=='\n'||s[i]=='\r')
						--i;
				}
				reg int x=kth(ptr+1),y=kth(ptr+2);
				split(x,y);
				ch(y)[0]=build(1,n,y,s);
				break;
			}
			case 'D':{
				scanf("%d",&n);
				n=min(n,totlen-ptr);
				totlen-=n;
				printf("tot=%d ptr=%d\n",tot,ptr);
				reg int x=kth(ptr+1),y=kth(ptr+n+2);
				split(x,y);
				ch(y)[0]=0;
				break;
			}
			case 'G':{
				scanf("%d",&n);
				n=min(n,totlen-ptr);
				printf("tot=%d ptr+1=%d ptr+n+2=%d\n",size(root),ptr+1,ptr+n+2);
				reg int x=kth(ptr+1),y=kth(ptr+n+2);
				split(x,y);
				print(ch(y)[0]);
				putchar('\n');
				break;
			}
			case 'P':{
				--ptr;
				break;
			}
			case 'N':{
				++ptr;
				break;
			}
			default:{
				puts("FFFFFFFFFFFFFFFFFFFFFFFF");
				exit(0);
				break;
			}
		}
		puts("Finish");
	}
	return 0;
}