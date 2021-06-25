#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e6+5;
const int inf=0x3f3f3f3f;

int n,m;
int a[MAXN],b[MAXN];
vector<int> V;
int id[MAXN<<1];

inline bool isA(reg int pos){
	return a[id[pos]]==pos;
}

inline bool isB(reg int pos){
	return b[id[pos]]==pos;
}

inline bool in(reg int x,reg int l,reg int r){
	return l<=x&&x<=r;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		b[i]=read();
	V.resize(n<<1);
	for(reg int i=0;i<n;++i)
		V[i<<1]=a[i+1],V[i<<1|1]=b[i+1];
	sort(V.begin(),V.end()),V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i){
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
		b[i]=lower_bound(V.begin(),V.end(),b[i])-V.begin()+1;
		id[a[i]]=id[b[i]]=i;
	}
	reg int l=1,r=0,cnt=0,used=0;
	reg int ans=inf;
	while(l<=(n<<1)){
		while(r<(n<<1)&&(cnt<n||used>m)){
			++r;
			if(isA(r))
				if(in(b[id[r]],l,r))
					--used;
				else
					++cnt;
			else if(!in(a[id[r]],l,r))
				++cnt,++used;
		}
		if(cnt==n&&used<=m)
			ans=min(ans,V[r-1]-V[l-1]);
		if(isA(l))
			if(in(b[id[l]],l,r))
				++used;
			else
				--cnt;
		else if(!in(a[id[l]],l,r))
			--cnt,--used;
		++l;
	}
	printf("%d\n",ans);
	return 0;
}