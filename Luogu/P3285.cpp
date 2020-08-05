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

const int MAXM=1e5+5;
const int inf=0X3F3F3F3F;

int Left,Right;

namespace SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	const int MAXSIZE=40*MAXM;
	struct Node{
		int lson,rson;
		int sum;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define sum(x) unit[(x)].sum
	};
	int tot,root;
	Node unit[MAXSIZE];
	map<int,int> P,V;
	inline void update(reg int &k,reg int l,reg int r,reg int pos){
		if(!k)
			k=++tot;
		++sum(k);
		if(l==r)
			return;
		if(pos<=mid)
			update(lson(k),l,mid,pos);
		else
			update(rson(k),mid+1,r,pos);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int pos){
		if(!sum(k)||l==r)
			return 0;
		if(pos<=mid)
			return query(lson(k),l,mid,pos);
		else
			return sum(lson(k))+query(rson(k),mid+1,r,pos);
	}
	inline int querykth(reg int k,int l,reg int r,reg int val){
		if(l==r)
			return l;
		reg int num=max(0,min(Right,mid)-max(Left,l)+1-sum(lson(k)));
		if(val<=num)
			return querykth(lson(k),l,mid,val);
		else
			return querykth(rson(k),mid+1,r,val-num);
	}
	inline int swap(int x,int y){
		int pos=(P.find(x)==P.end())?x:P[x];
		P[y]=pos,V[pos]=y;
		return pos-Left+1-query(root,-inf,inf,pos);
	}
	inline int front(int x){
		int pos=(P.find(x)==P.end())?x:P[x];
		reg int res=pos-Left+1-query(root,-inf,inf,pos);
		P[x]=--Left,V[Left]=x;
		update(root,-inf,inf,pos);
		return res;
	}
	inline int back(int x){
		int pos=(P.find(x)==P.end())?x:P[x];
		reg int res=pos-Left+1-query(root,-inf,inf,pos);
		P[x]=++Right,V[Right]=x;
		update(root,-inf,inf,pos);
		return res;
	}
	inline int ask(reg int x){
		int pos=querykth(root,-inf,inf,x);
		return V.find(pos)==V.end()?pos:V[pos];
	}
	#undef mid
}

int n,m;

int main(void){
	n=read(),m=read();
	Left=1,Right=n;
	reg int lastans=0;
	while(m--){
		static int type;
		static int k,x,y;
		type=read();
		switch(type){
			case 1:{
				x=read(),y=read();
				lastans=SegmentTree::swap(x-lastans,y-lastans);
				break;
			}
			case 2:{
				x=read();
				lastans=SegmentTree::front(x-lastans);
				break;
			}
			case 3:{
				x=read();
				lastans=SegmentTree::back(x-lastans);
				break;
			}
			case 4:{
				k=read();
				lastans=SegmentTree::ask(k-lastans);
				break;
			}
		}
		printf("%d\n",lastans);
	}
	return 0;
}