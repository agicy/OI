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
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+5;
const int MAXM=100000+5;

bool flag;
bool inque[MAXN];
int n,m,t,a,b;
int cnt,head[MAXN],to[(MAXM<<1)+MAXN],w[(MAXM<<1)+MAXN],Next[(MAXM<<1)+MAXN];
ll dis[MAXN],ans;
int inQue[MAXN];
deque<int> Q;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i)
		switch(t=read(),a=read(),b=read(),t){
			case 1:Add_Edge(a,b,0),Add_Edge(b,a,0);break;
			case 2:Add_Edge(a,b,1),flag|=(a==b);break;
			case 3:Add_Edge(b,a,0);break;
			case 4:Add_Edge(b,a,1),flag|=(a==b);break;
			case 5:Add_Edge(a,b,0);break;
			default:puts("Fuck");break;
		}
	for(reg int i=n;i>=1;--i)
		Add_Edge(0,i,1);
	return;
}

inline bool SPFA(int s){
	reg int i,ID;
	inque[s]=true,dis[s]=0,inQue[s]=1,Q.push_front(s);
	while(!Q.empty())
		for(ID=Q.front(),Q.pop_front(),inque[ID]=false,i=head[ID];i;i=Next[i])
			(dis[to[i]]<dis[ID]+w[i]&&(dis[to[i]]=dis[ID]+w[i],!inque[to[i]]))?((inque[to[i]]=true,++inQue[to[i]],inQue[to[i]]>n)?(puts("-1"),exit(0),0):(dis[to[i]]>dis[Q.front()])?(Q.push_front(to[i]),0):(Q.push_back(to[i]),0)):0;
	return true;
}

inline void Work(void){
	if(!flag&&SPFA(0)){
		for(reg int i=1;i<=n;++i)
			ans+=dis[i];
		printf("%lld\n",ans);
	}
	else
		puts("-1");
	return;
}
