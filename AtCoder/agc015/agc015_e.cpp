#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=2e5+5;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

struct Node{
	int x,v;
	inline bool operator<(const Node& a)const{
		return v<a.v;
	}
};

int n;
Node a[MAXN];
vector<int> V;
int id[MAXN],l[MAXN],r[MAXN];
int f[MAXN],sum[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		a[i].x=read(),a[i].v=read();
		V.push_back(a[i].x);
	}
	sort(a+1,a+n+1);
	sort(V.begin(),V.end()),V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i){
		a[i].x=lower_bound(V.begin(),V.end(),a[i].x)-V.begin()+1;
		id[a[i].x]=i;
	}
	for(reg int i=1;i<=n;++i)
		r[i]=max(r[i-1],id[i]);
	l[n]=id[n];
	for(reg int i=n-1;i>=1;--i)
		l[i]=min(l[i+1],id[i]);
	f[0]=sum[0]=1;
	reg int las=0;
	for(reg int i=1;i<=n;++i){
		while(r[las]<l[i]-1)
			++las;
		f[i]=sub(sum[i-1],sum[las-1]);
		sum[i]=add(sum[i-1],f[i]);
	}
	while(r[las]<n)
		++las;
	printf("%d\n",sub(sum[n],sum[las-1]));
	return 0;
}