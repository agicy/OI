#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int lowbit(reg int x){
	return x&(-x);
}

inline ull zip(reg ull x,reg ull y){
	return (x<<32)|y;
}

const int MAXN=1e5+5;
const int inf=0x3f3f3f3f;

struct Matrix{
	int x1,y1,x2,y2;
};

int n,m;
Matrix M[MAXN];
int lastans;
vector<int> Vx,Vy;

struct BIT{
	int head[MAXN]
	unordered_map<ull,int> val;
	inline void update(reg int x,reg int y,reg int v){
		for(reg int i=x;i<=Vx.size();i+=lowbit(i))
			for(reg int j=y;j<=Vy.size();j+=lowbit(j)){
				unordered_map<ull,int>::iterator it=val.find(zip(i,j));
				if(it==val.end())
					val[zip(i,j)]=v;
				else
					it->second+=v;
			}
		return;
	}
	inline int query(reg int x,reg int y){
		reg int res=0;
		for(reg int i=x;i;i^=lowbit(i))
			for(reg int j=y;j;j^=lowbit(j)){
				unordered_map<ull,int>::iterator it=val.find(zip(i,j));
				if(it!=val.end())
					res+=it->second;
			}
		return res;
	}
	inline int query(reg int x1,reg int x2,reg int y1,reg int y2){
		return query(x2,y2)+query(x1-1,y1-1)-query(x1-1,y2)-query(x2,y1-1);
	}
};

BIT BIT1,BIT2;

bool ed;

int main(void){
	n=read(),m=read();
	Vx.push_back(-inf),Vx.push_back(inf),Vx.reserve(n*2);
	Vy.push_back(-inf),Vy.push_back(inf),Vy.reserve(n*2);
	for(reg int i=1;i<=n;++i){
		M[i].x1=read(),M[i].y1=read();
		M[i].x2=read(),M[i].y2=read();
		Vx.push_back(M[i].x1-1),Vx.push_back(M[i].x2);
		Vy.push_back(M[i].y1-1),Vy.push_back(M[i].y2);
	}
	sort(Vx.begin(),Vx.end()),Vx.erase(unique(Vx.begin(),Vx.end()),Vx.end());
	sort(Vy.begin(),Vy.end()),Vy.erase(unique(Vy.begin(),Vy.end()),Vy.end());
	for(reg int i=1;i<=n;++i){
		M[i].x1=lower_bound(Vx.begin(),Vx.end(),M[i].x1)-Vx.begin()+1;
		M[i].x2=lower_bound(Vx.begin(),Vx.end(),M[i].x2)-Vx.begin()+1;
		M[i].y1=lower_bound(Vy.begin(),Vy.end(),M[i].y1)-Vy.begin()+1;
		M[i].y2=lower_bound(Vy.begin(),Vy.end(),M[i].y2)-Vy.begin()+1;
		BIT2.update(M[i].x1,M[i].y1,1);
		BIT2.update(M[i].x1,M[i].y2+1,-1);
		BIT2.update(M[i].x2+1,M[i].y1,-1);
		BIT2.update(M[i].x2+1,M[i].y2+1,1);
	}
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read(),y=read();
		x=lower_bound(Vx.begin(),Vx.end(),x)-Vx.begin()+1;
		y=lower_bound(Vy.begin(),Vy.end(),y)-Vy.begin()+1;
		BIT1.update(x,y,1);
	}
	reg int q=read();
	reg int a=read();
	while(q--){
		static int type,x,y,k;
		type=read();
		switch(type){
			case 1:{
				x=read()+lastans*a,y=read()+lastans*a;
				x=lower_bound(Vx.begin(),Vx.end(),x)-Vx.begin()+1;
				y=lower_bound(Vy.begin(),Vy.end(),y)-Vy.begin()+1;
				BIT1.update(x,y,1);
				break;
			}
			case 2:{
				k=read()+lastans*a;
				lastans=BIT1.query(M[k].x1,M[k].x2,M[k].y1,M[k].y2);
				writeln(lastans);
				break;
			}
			case 3:{
				x=read()+lastans*a,y=read()+lastans*a;
				x=lower_bound(Vx.begin(),Vx.end(),x)-Vx.begin()+1;
				y=lower_bound(Vy.begin(),Vy.end(),y)-Vy.begin()+1;
				lastans=BIT2.query(x,y);
				writeln(lastans);
				break;
			}
		}
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}