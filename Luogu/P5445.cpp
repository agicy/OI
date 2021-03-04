#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isdigit(*s))*s=getchar();
	while(isdigit(*s))*(++s)=getchar();
	*s='\0';
	return;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=3e5+5;
const int MAXQ=3e5+5;

namespace BIT{
	namespace SegmentTree{
		const int MAXSIZE=3e7+5;
		#define mid ( ( (l) + (r) ) >> 1 )
		struct Node{
			int lson,rson;
			int sum;
			#define lson(x) unit[(x)].lson
			#define rson(x) unit[(x)].rson
			#define sum(x) unit[(x)].sum
		};
		int tot;
		Node unit[MAXSIZE];
		inline void update(reg int &p,reg int l,reg int r,reg int pos,reg int val){
			if(!p)
				p=++tot;
			sum(p)+=val;
			if(l!=r){
				if(pos<=mid)
					update(lson(p),l,mid,pos,val);
				else
					update(rson(p),mid+1,r,pos,val);
			}
			return;
		}
		inline int query(reg int p,reg int l,reg int r,reg int L,reg int R){
			if(!p)
				return 0;
			if(L<=l&&r<=R)
				return sum(p);
			if(L<=mid&&mid<R)
				return query(lson(p),l,mid,L,R)+query(rson(p),mid+1,r,L,R);
			else if(L<=mid)
				return query(lson(p),l,mid,L,R);
			else
				return query(rson(p),mid+1,r,L,R);
		}
		#undef lson
		#undef rson
		#undef sum
		#undef mid
	}
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	int rt[MAXN];
	inline void Init(reg int s){
		n=s;
		memset(rt,0,sizeof(rt));
		return;
	}
	inline void update(reg int id,reg int pos,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			SegmentTree::update(rt[i],1,n,pos,val);
		return;
	}
	inline int query(reg int id,reg int pos){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=SegmentTree::query(rt[i],1,n,1,pos);
		return res;
	}
}

struct Road{
	int l,r;
	inline Road(reg int l=0,reg int r=0):l(l),r(r){
		return;
	}
	inline bool operator<(const Road& a)const{
		return r<a.r;
	}
};

int n,q;
char s[MAXN];
set<Road> S;

inline void Add(reg int x1,reg int y1,reg int x2,reg int y2,reg int W){
	BIT::update(x1,y1,W),BIT::update(x1,y2+1,-W);
	BIT::update(x2+1,y1,-W),BIT::update(x2+1,y2+1,W);
	return;
}

inline int Query(reg int x,reg int y){
	return BIT::query(x,y);
}

int main(void){
	//printf("%.1lf MiB\n",sizeof(BIT::SegmentTree::unit)/1048576.0);
	n=read()+1,q=read(),read(s+1);
	BIT::Init(n+1);
	for(reg int i=1;i<=n;++i)
		S.insert(Road(i,i));
	for(reg int i=1;i<n;++i)
		if(s[i]=='1'){
			set<Road>::iterator it=S.lower_bound(Road(0,i+1));
			--it;
			reg int lb=it->l;
			S.erase(it),S.erase(Road(i+1,i+1));
			S.insert(Road(lb,i+1));
		}
	for(set<Road>::iterator it=S.begin();it!=S.end();++it)
		Add(it->l,it->l,it->r,it->r,q);
	for(reg int t=1;t<=q;++t){
		static char opt;
		static int i,a,b;
		do
			opt=getchar();
		while(!isalpha(opt));
		switch(opt){
			case 't':{
				i=read();
				if(s[i]=='1'){
					set<Road>::iterator it=S.lower_bound(Road(0,i));
					reg int lb1=it->l,rb1=i;
					reg int lb2=i+1,rb2=it->r;
					Add(lb1,lb2,rb1,rb2,t-q);
					S.erase(Road(lb1,rb2));
					S.insert(Road(lb1,rb1)),S.insert(Road(lb2,rb2));
					s[i]^=1;
				}
				else{
					set<Road>::iterator it=S.lower_bound(Road(0,i));
					reg int lb1=it->l,rb1=i;
					++it;
					reg int lb2=i+1,rb2=it->r;
					Add(lb1,lb2,rb1,rb2,q-t);
					S.erase(Road(lb1,rb1)),S.erase(Road(lb2,rb2));
					S.insert(Road(lb1,rb2));
					s[i]^=1;
				}
				break;
			}
			case 'q':{
				a=read(),b=read();
				reg int x=S.lower_bound(Road(0,a))->l;
				reg int y=S.lower_bound(Road(0,b))->l;
				reg int ans=Query(a,b)-(q-t)*(x==y);
				writeln(ans);
				break;
			}
		}
	}
	flush();
	return 0;
}