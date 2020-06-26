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

const int MAXQ=2000000+5;

struct Node{
	int val,id;
	inline Node(reg int val=0,reg int id=0):val(val),id(id){
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
};

static char wbuf[1000000];
int wp;

inline void pc(reg char x){
	if(wp>=1000000)
		fwrite(wbuf,1,1000000,stdout),wp=0;
	wbuf[wp++]=x;
	return;
}

inline void write(reg int x){
	int c[12]={0};
	if(!x)
		return pc('0'),void();
	while(x)
		c[++c[0]]=x%10,x/=10;
	while(c[0])
		pc(c[c[0]--]+'0');
	return;
}

Node V[MAXQ];

struct Message{
	int opt,t,x,y;
};

Message M[MAXQ];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	struct Node{
		int L,R;
		int ice,tagI;
		int fire,tagF;
		#define L(x) unit[(x)].L
		#define R(x) unit[(x)].R
		#define ice(x) unit[(x)].ice
		#define tagI(x) unit[(x)].tagI
		#define fire(x) unit[(x)].fire
		#define tagF(x) unit[(x)].tagF
	};
	Node unit[MAXQ<<2];
	inline void Build(reg int k,reg int l,reg int r){
		L(k)=l,R(k)=r,ice(k)=tagI(k)=0;
		if(l==r)
			return;
		reg int mid=(l+r)>>1;
		Build(lson,l,mid);
		Build(rson,mid+1,r);
		return;
	}
	inline void AddI(reg int k,reg int val){
		ice(k)+=val;
		tagI(k)+=val;
		return;
	}
	inline void AddF(reg int k,reg int val){
		fire(k)+=val;
		tagF(k)+=val;
		return;
	}
	inline void pushdown(reg int k){
		if(tagI(k)){
			AddI(lson,tagI(k));
			AddI(rson,tagI(k));
			tagI(k)=0;
		}
		if(tagF(k)){
			AddF(lson,tagF(k));
			AddF(rson,tagF(k));
			tagF(k)=0;
		}
		return;
	}
	inline void UpdateI(reg int k,reg int l,reg int r,reg int val){
		if(R(k)<l||r<L(k))
			return;
		if(l<=L(k)&&R(k)<=r){
			AddI(k,val);
			return;
		}
		pushdown(k);
		UpdateI(lson,l,r,val);
		UpdateI(rson,l,r,val);
		ice(k)=ice(lson);
		return;
	}
	inline void UpdateF(reg int k,reg int l,reg int r,reg int val){
		if(R(k)<l||r<L(k))
			return;
		if(l<=L(k)&&R(k)<=r){
			AddF(k,val);
			return;
		}
		pushdown(k);
		UpdateF(lson,l,r,val);
		UpdateF(rson,l,r,val);
		fire(k)=fire(lson);
		return;
	}
	inline int findI(reg int k,reg int val){
		if(ice(k)<val)
			return 0;
		if(L(k)==R(k))
			return L(k);
		pushdown(k);
		if(ice(rson)>=val)
			return findI(rson,val);
		else
			return findI(lson,val);
	}
	inline int findF(reg int k,reg int val){
		if(fire(k)<val)
			return 0;
		if(L(k)==R(k))
			return L(k);
		pushdown(k);
		if(fire(rson)>=val)
			return findF(rson,val);
		else
			return findF(lson,val);
	}
	inline int Query(reg int k,reg int pos){
		if(L(k)==R(k))
			return ice(k);
		pushdown(k);
		reg int mid=(L(k)+R(k))>>1;
		if(pos<=mid)
			return Query(lson,pos);
		else
			return Query(rson,pos);
	}
	#undef lson
	#undef rson
}

struct TreeArray{
	int size,unit[MAXQ];
	#define lowbit(x) ( (x) & ( - (x) ) )
	inline void add(reg int ID,reg int val){
		for(reg int i=ID;i<=size;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int pre(reg int ID){
		reg int res=0;
		for(reg int i=ID;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
	inline void Init(reg int S){
		size=S;
		//memset(unit,0,sizeof(unit));
		return;
	}
	inline int suf(reg int ID){
		return pre(size)-pre(ID-1);
	}
	#undef lowbit
};

TreeArray ice,fire;

inline void output(reg int p,reg int x){
	if(!x)
		pc('P'),pc('e'),pc('a'),pc('c'),pc('e'),pc('\n');
	else
		write(V[p].val),pc(' '),write(x<<1),pc('\n');
	return;
}

int main(void){
	reg int Q=read();
	reg int cnt=0;
	for(reg int i=1;i<=Q;++i){
		M[i].opt=read();
		if(M[i].opt==1)
			M[i].t=read(),M[i].x=read(),M[i].y=read(),V[++cnt]=Node(M[i].x,i);
		else
			M[i].x=read();
	}
	sort(V+1,V+cnt+1);
	for(reg int i=1,val=1;i<=cnt;++i){
		if(V[i].val!=V[i-1].val)
			val=i;
		M[V[i].id].x=val;
	}
	ice.Init(cnt),fire.Init(cnt);
	using namespace SegmentTree;
	Build(1,1,cnt);
	reg int cnt0=0,cnt1=0;
	for(reg int i=1;i<=Q;++i){
		switch(M[i].opt){
			case 1:{
				if(M[i].t==0){
					++cnt0;
					ice.add(M[i].x,M[i].y);
					UpdateI(1,M[i].x,cnt,-M[i].y);
				}
				else{
					++cnt1;
					fire.add(M[i].x,M[i].y);
					UpdateI(1,1,M[i].x,M[i].y);
					UpdateF(1,1,M[i].x,M[i].y);
				}
				break;
			}
			case 2:{
				reg int k=M[i].x;
				if(M[k].t==0){
					--cnt0;
					ice.add(M[k].x,-M[k].y);
					UpdateI(1,M[k].x,cnt,M[k].y);
				}
				else{
					--cnt1;
					fire.add(M[k].x,-M[k].y);
					UpdateI(1,1,M[k].x,-M[k].y);
					UpdateF(1,1,M[k].x,-M[k].y);
				}
				break;
			}
		}
		if(!cnt0||!cnt1)
			pc('P'),pc('e'),pc('a'),pc('c'),pc('e'),pc('\n');
		else{
			reg int p=findI(1,0);
			if(p==cnt)
				output(p,ice.pre(cnt));
			else if(p==0)
				output(findF(1,fire.suf(1)),fire.suf(1));
			else{
				reg int val=fire.suf(p+1);
				reg int p2=findF(1,val);
				reg int ans1=min(ice.pre(p),fire.suf(p)),ans2=min(ice.pre(p2),fire.suf(p2));
				if(ans1>ans2)
					output(p,ans1);
				else
					output(p2,ans2);
			}
		}
	}
	fwrite(wbuf,1,wp,stdout);
	return 0;
}