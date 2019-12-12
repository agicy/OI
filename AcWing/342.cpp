#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F
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

const int MAXT=25000+5;
const int MAXR=50000+5;
const int MAXP=50000+5;

bool inque[MAXT];
int T,R,P,S;
int cnt,head[MAXT],to[(MAXR<<1)+MAXP],w[(MAXR<<1)+MAXP],Next[(MAXR<<1)+MAXP];
int dis[MAXT];

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
	T=read(),R=read(),P=read(),S=read();
	for(reg int i=1;i<=R;++i){
		static int a,b,c;
		a=read(),b=read(),c=read();
		Add_Edge(a,b,c);
		Add_Edge(b,a,c);
	}
	for(reg int i=1;i<=P;++i){
		static int a,b,c;
		a=read(),b=read(),c=read();
		Add_Edge(a,b,c);
	}
	return;
}

inline bool SPFA(int s){
	reg int i,ID;
	deque<int> Q;
	memset(inque,false,sizeof(inque));
	memset(dis,0X3F,sizeof(dis));
	while(!Q.empty())
		Q.pop_front();
	inque[s]=true,dis[s]=0,Q.push_front(s);
	while(!Q.empty()){
		ID=Q.front();
		Q.pop_front();
		inque[ID]=false;
		for(i=head[ID];i;i=Next[i])
			if(dis[to[i]]>dis[ID]+w[i]){
				dis[to[i]]=dis[ID]+w[i];
				if(!inque[to[i]]){
					inque[to[i]]=true;
					if(dis[to[i]]<dis[Q.front()])
						Q.push_front(to[i]);
					else
						Q.push_back(to[i]);
				}
			}
	}
	return true;
}

inline void Work(void){
	SPFA(S);
	for(reg int i=1;i<=T;++i)
		if(dis[i]==INF)
			puts("NO PATH");
		else
			printf("%d\n",dis[i]);
	return;
}
