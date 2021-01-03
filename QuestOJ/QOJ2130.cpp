#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c)(wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=2e5+5;

int n,m;
int a[MAXN][2];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	bool unit[MAXN<<2][2][2];
	inline void pushup(reg int k,reg int l,reg int r){
		unit[k][0][0]=unit[k][0][1]=unit[k][1][0]=unit[k][1][1]=false;
		if(r-l>1){
			if(a[mid][0]<=a[mid+1][0]){
				unit[k][0][0]=unit[k][0][0]||(unit[lson][0][0]&&unit[rson][0][0]);
				unit[k][0][1]=unit[k][0][1]||(unit[lson][0][0]&&unit[rson][0][1]);
				unit[k][1][0]=unit[k][1][0]||(unit[lson][1][0]&&unit[rson][0][0]);
				unit[k][1][1]=unit[k][1][1]||(unit[lson][1][0]&&unit[rson][0][1]);
			}
			if(a[mid][0]<=a[mid+1][1]){
				unit[k][0][0]=unit[k][0][0]||(unit[lson][0][0]&&unit[rson][1][0]);
				unit[k][0][1]=unit[k][0][1]||(unit[lson][0][0]&&unit[rson][1][1]);
				unit[k][1][0]=unit[k][1][0]||(unit[lson][1][0]&&unit[rson][1][0]);
				unit[k][1][1]=unit[k][1][1]||(unit[lson][1][0]&&unit[rson][1][1]);
			}
			if(a[mid][1]<=a[mid+1][0]){
				unit[k][0][0]=unit[k][0][0]||(unit[lson][0][1]&&unit[rson][0][0]);
				unit[k][0][1]=unit[k][0][1]||(unit[lson][0][1]&&unit[rson][0][1]);
				unit[k][1][0]=unit[k][1][0]||(unit[lson][1][1]&&unit[rson][0][0]);
				unit[k][1][1]=unit[k][1][1]||(unit[lson][1][1]&&unit[rson][0][1]);
			}
			if(a[mid][1]<=a[mid+1][1]){
				unit[k][0][0]=unit[k][0][0]||(unit[lson][0][1]&&unit[rson][1][0]);
				unit[k][0][1]=unit[k][0][1]||(unit[lson][0][1]&&unit[rson][1][1]);
				unit[k][1][0]=unit[k][1][0]||(unit[lson][1][1]&&unit[rson][1][0]);
				unit[k][1][1]=unit[k][1][1]||(unit[lson][1][1]&&unit[rson][1][1]);
			}
		}
		else{
			unit[k][0][0]=a[mid][0]<=a[mid+1][0];
			unit[k][0][1]=a[mid][0]<=a[mid+1][1];
			unit[k][1][0]=a[mid][1]<=a[mid+1][0];
			unit[k][1][1]=a[mid][1]<=a[mid+1][1];
		}
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		if(l==r){
			unit[k][0][0]=unit[k][1][1]=true;
			unit[k][0][1]=a[l][0]<=a[l][1];
			unit[k][1][0]=a[l][1]<=a[l][0];
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k,l,r);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos){
		if(l==r){
			unit[k][0][0]=unit[k][1][1]=true;
			unit[k][0][1]=a[l][0]<=a[l][1];
			unit[k][1][0]=a[l][1]<=a[l][0];
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos);
		else
			update(rson,mid+1,r,pos);
		pushup(k,l,r);
		return;
	}
	inline bool query(void){
		return unit[1][0][0]||unit[1][0][1]||unit[1][1][0]||unit[1][1][1];
	}
	#undef lson
	#undef rson
	#undef mid
}

inline void swap(reg int &a,reg int &b){
	a^=b,b^=a,a^=b;
	return;
}

inline void SDFZHAPPY(void){
	putchar('S'),putchar('D'),putchar('F'),putchar('Z'),putchar('H'),putchar('A'),putchar('P'),putchar('P'),putchar('Y'),putchar('\n');
}

inline void SDFZSAD(void){
	putchar('S'),putchar('D'),putchar('F'),putchar('Z'),putchar('S'),putchar('A'),putchar('D'),putchar('\n');
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i][0]=read(),a[i][1]=read();
	SegmentTree::build(1,1,n);
	while(m--){
		static int u,v;
		u=read(),v=read();
		if(u!=v)
			swap(a[u][0],a[v][0]),swap(a[u][1],a[v][1]),SegmentTree::update(1,1,n,u),SegmentTree::update(1,1,n,v);
		reg bool f=SegmentTree::query();
		if(f)
			SDFZHAPPY();
		else
			SDFZSAD();
	}
	flush();
	return 0;
}