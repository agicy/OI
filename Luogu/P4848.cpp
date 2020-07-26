#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 1e9
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100000+5;
const double alpha=0.75;

const int MAXSIZE=MAXN*20;

int n,K;
int X[2];
int _Max[2],_Min[2];

namespace SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	int lastans;
	namespace kD_Tree{
		#define cMax(x,y) ( (x) < (y) ? (x) = (y) : (0) )
		#define cMin(x,y) ( (x) > (y) ? (x) = (y) : (0) )
		int cnt;
		#define val(x,y) T[x].val[y]
		#define Max(x,y) T[x].Max[y]
		#define Min(x,y) T[x].Min[y]
		#define lson(x) T[x].lson
		#define rson(x) T[x].rson
		#define size(x) T[x].size
		struct Node{
			int size;
			int lson,rson;
			int Max[2],Min[2];
			int val[2];
		}T[MAXSIZE];
		int WD,p[MAXN];
		inline bool cmp(reg int a,reg int b){
			return val(a,WD)<val(b,WD);
		}
		inline void pushup(reg int k){
			reg int l=lson(k),r=rson(k);
			if(l)
				cMax(Max(k,0),Max(l,0)),cMax(Max(k,1),Max(l,1)),cMin(Min(k,0),Min(l,0)),cMin(Min(k,1),Min(l,1));
			if(r)
				cMax(Max(k,0),Max(r,0)),cMax(Max(k,1),Max(r,1)),cMin(Min(k,0),Min(r,0)),cMin(Min(k,1),Min(r,1));
			size(k)=size(l)+size(r)+1;
			return;
		}
		inline void flat(reg int k){
			if(lson(k))
				flat(lson(k));
			p[++cnt]=k;
			if(rson(k))
				flat(rson(k));
			return;
		}
		int buf[MAXN];
		inline int Build(reg int l,reg int r,reg int wd){
			if(l>r)
				return 0;
			WD=wd;
			std::nth_element(p+l,p+mid,p+r+1,cmp);
			reg int k=p[mid];
			Max(k,0)=Min(k,0)=val(k,0),Max(k,1)=Min(k,1)=val(k,1);
			lson(k)=Build(l,mid-1,wd^1),rson(k)=Build(mid+1,r,wd^1);
			pushup(k);
			return k;
		}
		inline void Insert(reg int& root,reg int c){
			if(!root){
				root=c;
				return;
			}
			reg int top=0;
			for(reg int wd=0,x=root;;wd^=1){
				buf[++top]=x;
				cMax(Max(x,0),Max(c,0)),cMax(Max(x,1),Max(c,1)),cMin(Min(x,0),Min(c,0)),cMin(Min(x,1),Min(c,1));
				++size(x);
				if(val(c,wd)<val(x,wd))
					if(!lson(x)){
						lson(x)=c;
						break;
					}
					else
						x=lson(x);
				else
					if(!rson(x)){
						rson(x)=c;
						break;
					}
					else
						x=rson(x);
			}
			buf[++top]=c;
			while(size(lson(c))<alpha*size(c)&&size(rson(c))<alpha*size(c))
				c=buf[--top];
			if(!c)
				return;
			if(c==root){
				cnt=0;
				flat(root);
				root=Build(1,cnt,0);
				cnt=0;
				return;
			}
			reg int fa=buf[--top],crt;
			flat(c);
			crt=Build(1,cnt,top&1);
			cnt=0;
			if(lson(fa)==c)
				lson(fa)=crt;
			else
				rson(fa)=crt;
		}
		inline void Query(reg int x){
			if(!x||Max(x,0)<_Min[0]||Max(x,1)<_Min[1]||Min(x,0)>_Max[0]||Min(x,1)>_Max[1]||lastans>=K)
				return;
			if(_Min[0]<=Min(x,0)&&Max(x,0)<=_Max[0]&&_Min[1]<=Min(x,1)&&Max(x,1)<=_Max[1]){
				lastans+=size(x);
				return;
			}
			if(_Min[0]<=val(x,0)&&val(x,0)<=_Max[0]&&_Min[1]<=val(x,1)&&val(x,1)<=_Max[1])
				++lastans;
			Query(lson(x));
			Query(rson(x));
			return;
		}
		#undef lson
		#undef rson
	}
	using kD_Tree::T;
	int ct,tot=1;
	int root[MAXSIZE],lson[MAXSIZE],rson[MAXSIZE];
	inline void Update(void){
		reg bool flag=true;
		reg int ID=1;
		reg int l=1,r=INF;
		while(true){
			if(flag){
				++ct;
				Max(ct,0)=Min(ct,0)=val(ct,0)=X[0],Max(ct,1)=Min(ct,1)=val(ct,1)=X[1];
				size(ct)=1;
				kD_Tree::Insert(root[ID],ct);
			}
			if(l==r)
				return;
			if(K<=mid){
				if(!lson[ID])
					lson[ID]=++tot;
				ID=lson[ID],r=mid;
				flag=false;
			}
			else{
				if(!rson[ID])
					rson[ID]=++tot;
				ID=rson[ID],l=mid+1;
				flag=true;
			}
		}
		return;
	}
	inline void Query(void){
		lastans=0;
		kD_Tree::Query(root[1]);
		if(lastans<K){
			puts("NAIVE!ORZzyz.");
			lastans=0;
			return;
		}
		reg int ID=1,l=1,r=INF;
		while(l<r){
			lastans=0;
			kD_Tree::Query(root[rson[ID]]);
			if(K<=lastans)
				ID=rson[ID],l=mid+1;
			else
				K-=lastans,ID=lson[ID],r=mid;
		}
		printf("%d\n",lastans=l);
		return;
	}
}

using SegmentTree::lastans;

int main(void){
	reg int cnt=0;
	read(),n=read();
	reg int type,x1,y1,x2,y2;
	for(reg int i=1;i<=n;++i)
		switch(type=read()){
			case 1:{
				x1=read()^lastans,y1=read()^lastans,K=read()^lastans;
				X[0]=x1,X[1]=y1;
				SegmentTree::Update();
				++cnt;
				break;
			}
			case 2:{
				x1=read()^lastans,y1=read()^lastans,x2=read()^lastans,y2=read()^lastans,K=read()^lastans;
				_Min[0]=x1,_Min[1]=y1,_Max[0]=x2,_Max[1]=y2;
				SegmentTree::Query();
				break;
			}
			default:break;
		}
	return 0;
}