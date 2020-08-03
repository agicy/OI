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

const int MAXW=2e6+5;
const int MAX1=1.6e5+5;
const int MAX2=1e4+5;

struct operations{
	int tim,x,y,val,type;
	inline operations(reg int tim=0,reg int x=0,reg int y=0,reg int val=0,reg int type=0):tim(tim),x(x),y(y),val(val),type(type){
		return;
	}
	inline bool operator<(const operations& a){
		return x<a.x||(x==a.x&&y<a.y);
	}
};

namespace TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n;
	int unit[MAXW];
	inline void Init(reg int S){
		n=S;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(reg int u,reg int val){
		for(reg int i=u;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int u){
		reg int res=0;
		for(reg int i=u;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
	#undef lowbit
}

int w;
int tot;
operations O[MAX1+4*MAX2];

inline void CDQ(reg int l,reg int r){
	if(l==r)
		return;
	reg int mid=(l+r)>>1;
	CDQ(l,mid),CDQ(mid+1,r);
	sort(O+l,O+mid+1),sort(O+mid+1,O+r+1);
	reg int j=l;
	for(reg int i=mid+1;i<=r;++i){
		while(j<=mid&&O[j].x<=O[i].x){
			if(O[j].type==0)
				TreeArray::update(O[j].y,O[j].val);
			++j;
		}
		if(O[i].type==1)
			O[i].val+=TreeArray::query(O[i].y);
	}
	for(reg int i=l;i<j;++i)
		if(O[i].type==0)
			TreeArray::update(O[i].y,-O[i].val);
	return;
}

inline bool cmp(const operations& a,const operations& b){
	return a.tim<b.tim;
}

int main(void){
	read(),w=read()+1;
	reg int cnt=0;
	for(reg int i=1,flag=true;flag;++i){
		static int type;
		static int x,y,a,x1,y1,x2,y2;
		type=read();
		switch(type){
			case 1:{
				x=read()+1,y=read()+1,a=read();
				++cnt;
				O[cnt]=operations(cnt,x,y,a,0);
				break;
			}
			case 2:{
				x1=read(),y1=read(),x2=read()+1,y2=read()+1;
				++cnt;
				O[cnt]=operations(cnt,x1,y1,0,1);
				++cnt;
				O[cnt]=operations(cnt,x2,y2,0,1);
				++cnt;
				O[cnt]=operations(cnt,x2,y1,0,1);
				++cnt;
				O[cnt]=operations(cnt,x1,y2,0,1);
				break;
			}
			case 3:{
				flag=false;
				break;
			}
		}
	}
	TreeArray::Init(w);
	CDQ(1,cnt);
	sort(O+1,O+cnt+1,cmp);
	for(reg int i=1;i<=cnt;++i)
		if(O[i].type==1){
			printf("%d\n",O[i].val+O[i+1].val-O[i+2].val-O[i+3].val);
			i+=3;
		}
	return 0;
}