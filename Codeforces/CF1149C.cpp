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
	while(*s!='('&&*s!=')')*s=getchar();
	while(*s=='('||*s==')')*(++s)=getchar();
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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e5+5;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int sum;
		int rMin,lMax;
		int ldMax,rdMax,cMid;
		int Max;
		#define sum(x) unit[(x)].sum
		#define rMin(x) unit[(x)].rMin
		#define lMax(x) unit[(x)].lMax
		#define ldMax(x) unit[(x)].ldMax
		#define rdMax(x) unit[(x)].rdMax
		#define cMid(x) unit[(x)].cMid
		#define Max(x) unit[(x)].Max
	};
	inline Node operator+(const Node& a,const Node& b){
		Node res;
		res.sum=a.sum+b.sum;
		res.lMax=max(a.lMax,a.sum+b.lMax),res.rMin=min(a.rMin+b.sum,b.rMin);
		res.ldMax=max(a.ldMax,max(a.cMid+b.lMax,b.ldMax-a.sum)),res.rdMax=max(b.rdMax,max(b.cMid-a.rMin,a.rdMax+b.sum)),res.cMid=max(a.cMid+b.sum,b.cMid-a.sum);
		res.Max=max(max(a.Max,b.Max),max(a.rdMax+b.lMax,b.ldMax-a.rMin));
		return res;
	}
	Node unit[MAXN<<3];
	inline void pushup(reg int k){
		unit[k]=unit[lson]+unit[rson];
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg char sum[]){
		if(l==r){
			if(sum[l]=='(')
				sum(k)=1,rMin(k)=0,lMax(k)=1;
			else
				sum(k)=-1,rMin(k)=-1,lMax(k)=0;
			ldMax(k)=rdMax(k)=cMid(k)=Max(k)=1;
			return;
		}
		build(lson,l,mid,sum),build(rson,mid+1,r,sum);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg char ch){
		if(l==r){
			if(ch=='(')
				sum(k)=1,rMin(k)=0,lMax(k)=1;
			else
				sum(k)=-1,rMin(k)=-1,lMax(k)=0;
			ldMax(k)=rdMax(k)=cMid(k)=Max(k)=1;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,ch);
		else
			update(rson,mid+1,r,pos,ch);
		pushup(k);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

int n,m;
char str[MAXN<<1];

int main(void){
	n=read(),m=read();
	read(str+1);
	n=(n-1)<<1;
	SegmentTree::build(1,1,n,str);
	writeln(SegmentTree::unit[1].Max);
	while(m--){
		static int l,r;
		l=read(),r=read();
		if(str[l]!=str[r]){
			str[l]^=str[r],str[r]^=str[l],str[l]^=str[r];
			SegmentTree::update(1,1,n,l,str[l]),SegmentTree::update(1,1,n,r,str[r]);
		}
		writeln(SegmentTree::unit[1].Max);
	}
	flush();
	return 0;
}