#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

namespace Tree{
	const int MAXSIZE=2000000+5;
	struct Node{
		int lson,rson,f;
		int tsize,fsize,data;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define f(x) unit[(x)].f
		#define fsize(x) unit[(x)].fsize
		#define tsize(x) unit[(x)].tsize
		#define data(x) unit[(x)].data
	};

	Node unit[MAXSIZE];
	int Stack[MAXSIZE],temp[MAXSIZE];

	const double alpha=0.75;

	int root,top,tot;

	inline bool cheak(reg int k){
		if((double)fsize(k)*alpha>=(double)max(fsize(lson(k)),fsize(rson(k))))
			return true;
		return false;
	}
	inline void DFS(reg int k){
		if(!k)
			return;
		DFS(lson(k));
		if(f(k))
			temp[++tot]=k;
		else
			Stack[++top]=k;
		DFS(rson(k));
		return;
	}
	inline void Build(reg int &k,reg int l,reg int r){
		reg int mid=(l+r)>>1;
		k=temp[mid];
		if(l==r){
			lson(k)=rson(k)=0;
			fsize(k)=tsize(k)=1;
			return;
		}
		if(l<mid)
			Build(lson(k),l,mid-1);
		else
			lson(k)=0;
		if(mid<r)
			Build(rson(k),mid+1,r);
		else
			rson(k)=0;
		fsize(k)=fsize(lson(k))+fsize(rson(k))+1;
		tsize(k)=tsize(lson(k))+tsize(rson(k))+1;
		return;
	}
	inline void rebuild(reg int &k){
		tot=0;
		DFS(k);
		if(tot)
			Build(k,1,tot);
		else
			k=0;
		return;
	}
	inline void insert(reg int &k,reg int Val){
		if(!k){
			k=Stack[top--];
			data(k)=Val;
			fsize(k)=tsize(k)=f(k)=1;
			lson(k)=rson(k)=0;
			return;
		}
		++fsize(k),++tsize(k);
		if(data(k)>=Val)
			insert(lson(k),Val);
		else
			insert(rson(k),Val);
		if(!cheak(k))
			rebuild(k);
		return;
	}
	inline int kth(reg int rank){
		reg int k=root;
		while(k){
			if(f(k)&&fsize(lson(k))+1==rank)
				return data(k);
			if(fsize(lson(k))+f(k)>=rank)
				k=lson(k);
			else{
				rank-=fsize(lson(k))+f(k);
				k=rson(k);
			}
		}
		return 0;
	}
	inline int rnk(reg int Val){
		reg int k=root,res=1;
		while(k)
			if(data(k)>=Val)
				k=lson(k);
			else{
				res+=fsize(lson(k))+f(k);
				k=rson(k);
			}
		return res;
	}
	inline void del(reg int &k,reg int rank){
		if(f(k)&&fsize(lson(k))+1==rank){
			f(k)=0;
			--fsize(k);
			return;
		}
		--fsize(k);
		if(f(k)+fsize(lson(k))>=rank)
			del(lson(k),rank);
		else
			del(rson(k),rank-f(k)-fsize(lson(k)));
	}
	inline void rdelet(int Val){
		del(root,rnk(Val));
		if(unit[root].tsize*alpha>=unit[root].fsize)
			rebuild(root);
		return;
	}
}

using namespace Tree;

int n,m;
int a[MAXSIZE];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	sort(a+1,a+n+1);
	for(reg int i=2000000;i>=1;--i)
		Stack[i]=++top;
	for(reg int i=1;i<=n;++i){
		temp[i]=i;
		unit[i].data=a[i];
		unit[i].f=1;
	}
	top-=n;
	Build(root,1,n);
	reg int ans=0,lastans=0;
	while(m--){
		int opt,x,y;
		opt=read(),x=read();
		x=lastans^x;
		switch(opt){
			case 1:{
				insert(root,x);
				break;
			}
			case 2:{
				rdelet(x);
				break;
			}
			case 3:{
				y=rnk(x),ans=ans^y,lastans=y;
				break;
			}
			case 4:{
				y=kth(x),ans=ans^y,lastans=y;
				break;
			}
			case 5:{
				y=kth(rnk(x)-1),ans=ans^y,lastans=y;
				break;
			}
			case 6:{
				y=kth(rnk(x+1)),ans=ans^y,lastans=y;
				break;
			}
			default:break;
		}
	}
	printf("%d\n",ans);
	return 0;
}