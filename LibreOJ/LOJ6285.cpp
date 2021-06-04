#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
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
	if(x<0) x=-x,putchar('-');
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;
const int B=80;
const int MAXCNT=MAXN/B+5;

int n;
int a[MAXN];
int lef[MAXN],rig[MAXN],id[MAXN];
int f[MAXCNT][MAXCNT];
vector<int> pos[MAXN];
int T[MAXN];
bool inque[MAXN];
queue<int> Q;

inline int getCnt(reg int val,reg int l,reg int r){
	if(pos[val].empty()||pos[val].front()>r||pos[val].back()<l)
		return 0;
	reg int __l,__r,__mid;
	__l=0,__r=pos[val].size()-1;
	while(__l<__r){
		__mid=(__l+__r)>>1;
		if(pos[val][__mid]>=l)
			__r=__mid;
		else
			__l=__mid+1;
	}
	reg int lef=__l;
	__l=0,__r=pos[val].size()-1;
	while(__l<__r){
		__mid=(__l+__r)>>1;
		if(pos[val][__mid+1]<=r)
			__l=__mid+1;
		else
			__r=__mid;
	}
	reg int rig=__l;
	return rig-lef+1;
}

inline int query(reg int l,reg int r){
	reg int lid=id[l],rid=id[r];
	if(lid==rid){
		reg int Max=0;
		for(reg int i=l;i<=r;++i){
			if(!inque[a[i]])
				inque[a[i]]=true,Q.push(a[i]);
			++T[a[i]];
			if(T[a[i]]>T[Max])
				Max=a[i];
			else if(T[a[i]]==T[Max]&&a[i]<Max)
				Max=a[i];
		}
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			inque[u]=false,T[u]=0;
		}
		return Max;
	}
	else{
		if(lid+1<=rid-1){
			reg int Max=f[lid+1][rid-1];
			reg int cnt=getCnt(Max,l,r);
			for(reg int i=l;i<=rig[lid];++i){
				reg int val=getCnt(a[i],l,r);
				if(val>cnt)
					Max=a[i],cnt=val;
				else if(val==cnt&&a[i]<Max)
					Max=a[i];
			}
			for(reg int i=lef[rid];i<=r;++i){
				reg int val=getCnt(a[i],l,r);
				if(val>cnt)
					Max=a[i],cnt=val;
				else if(val==cnt&&a[i]<Max)
					Max=a[i];
			}
			return Max;
		}
		else{
			reg int Max=0;
			for(reg int i=l;i<=rig[lid];++i){
				if(!inque[a[i]])
					inque[a[i]]=true,Q.push(a[i]);
				++T[a[i]];
				if(T[a[i]]>T[Max])
					Max=a[i];
				else if(T[a[i]]==T[Max]&&a[i]<Max)
					Max=a[i];
			}
			for(reg int i=lef[rid];i<=r;++i){
				if(!inque[a[i]])
					inque[a[i]]=true,Q.push(a[i]);
				++T[a[i]];
				if(T[a[i]]>T[Max])
					Max=a[i];
				else if(T[a[i]]==T[Max]&&a[i]<Max)
					Max=a[i];
			}
			while(!Q.empty()){
				reg int u=Q.front();
				Q.pop();
				inque[u]=false,T[u]=0;
			}
			return Max;
		}
	}
}

int main(void){
	n=read();
	vector<int> V;
	V.reserve(n);
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		V.push_back(a[i]);
	}
	sort(V.begin(),V.end()),V.erase(unique(V.begin(),V.end()),V.end());
	for(int i=1;i<=n;++i){
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
		pos[a[i]].push_back(i);
	}
	reg int tot=(n+B-1)/B;
	for(reg int i=1;i<=tot;++i){
		lef[i]=(i-1)*B+1,rig[i]=min(i*B,n);
		for(reg int j=lef[i];j<=rig[i];++j)
			id[j]=i;
	}
	for(reg int i=1;i<=tot;++i){
		reg int ptr=lef[i];
		reg int Max=0;
		for(reg int j=i;j<=tot;++j){
			while(ptr<=rig[j]){
				if(!inque[a[ptr]])
					inque[a[ptr]]=true,Q.push(a[ptr]);
				++T[a[ptr]];
				if(T[a[ptr]]>T[Max])
					Max=a[ptr];
				else if(T[a[ptr]]==T[Max]&&a[ptr]<Max)
					Max=a[ptr];
				++ptr;
			}
			f[i][j]=Max;
		}
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			inque[u]=false,T[u]=0;
		}
	}
	for(reg int i=1;i<=n;++i){
		static int l,r;
		l=read(),r=read();
		writeln(V[query(l,r)-1]);
	}
	flush();
	return 0;
}