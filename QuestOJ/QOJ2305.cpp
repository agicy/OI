#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
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

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0)
		putchar('0');
	else
		while(x)
			buf[++p]=(x%10)^'0',x/=10;
	while(~p)
		putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline void cMax(reg int &a,reg int b){
	if(a<b)
		a=b;
	return;
}

const int MAXN=1e5+5;

struct BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN*3];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			cMax(unit[i],val);
		return;
	}
	inline int query(reg int id){
		int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			cMax(res,unit[i]);
		return res;
	}
};

int n;
int a[MAXN][3];
BIT T[6];
vector<int> V;

int main(void){
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);

	n=read();
	V.resize(3*n);
	for(reg int i=0;i<3;++i)
		for(reg int j=1;j<=n;++j)
			V[i*n+j-1]=a[j][i]=read();
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	reg int siz=V.size();
	for(reg int i=0;i<3;++i)
		for(reg int j=1;j<=n;++j)
			a[j][i]=lower_bound(V.begin(),V.end(),a[j][i])-V.begin()+1;
	T[0].Init(3*n),T[1].Init(3*n),T[2].Init(3*n),T[3].Init(3*n),T[4].Init(3*n),T[5].Init(3*n);
	for(reg int i=1;i<=n;++i){
		reg int x1=max(T[0].query(a[i][0]),max(T[2].query(a[i][0]),T[4].query(a[i][0])))+1;
		reg int x2=max(T[1].query(siz-a[i][1]+1),max(T[3].query(siz-a[i][1]+1),T[5].query(siz-a[i][1]+1)))+1;
		reg int x3=max(T[0].query(a[i][2]),T[2].query(a[i][2]))+1;
		reg int x4=max(T[1].query(siz-a[i][2]+1),T[5].query(siz-a[i][2]+1))+1;
		T[0].update(a[i][0],x1),T[0].update(a[i][1],x2);
		T[1].update(siz-a[i][0]+1,x1),T[1].update(siz-a[i][1]+1,x2);
		T[2].update(a[i][2],x3);
		T[3].update(siz-a[i][2]+1,x3);
		T[4].update(a[i][2],x4);
		T[5].update(siz-a[i][2]+1,x4);
	}
	writeln(max(T[0].query(siz),max(T[2].query(siz),T[4].query(siz))));
	flush();

	fclose(stdin);
	fclose(stdout);
	return 0;
}