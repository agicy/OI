#pragma GCC optimize(2)

#include<cstdio>
#include<algorithm>
using std::max;
using std::sort;
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)

const int MAXN=10000+5;

static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	register char ch=getchar();
	int x=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')x=x*10+ch-48,ch=getchar();
	return x;
}

bool vis[MAXN];
int n,k;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
int MaxPart,pos;
int size[MAXN];
int a[MAXN];
int d[MAXN],b[MAXN];
int Cnt[MAXN];
int Node_cnt;
int ans;

void GetRoot(int,int);
void GetSonTreeInformation(int,int);
void Calc(int,int);
void Solve(int);
void Add_Edge(int,int,int);
bool cmp(int,int);

int main(void){
	register int i,u,v,l;
	n=read(),k=read();
	for(i=1;i<n;++i){
		u=read(),v=read(),l=read();
		Add_Edge(u,v,l);
		Add_Edge(v,u,l);
	}
	pos=0,MaxPart=INF;
	GetRoot(1,0);
	Solve(pos);
	printf("%d\n",ans);
	return 0;
}

void GetRoot(int ID,int fa){
	int i,Max=0;
	size[ID]=1;
	for(i=head[ID];i;i=Next[i]){
		if(to[i]!=fa&&!vis[to[i]]){
			GetRoot(to[i],ID);
			size[ID]+=size[to[i]];
			Max=max(Max,size[to[i]]);
		}
	}
	Max=max(Max,n-size[ID]);
	if(Max<MaxPart){
		pos=ID;
		MaxPart=Max;
	}
	return;
}

void GetSonTreeInformation(int ID,int fa){
	register int i;
	for(i=head[ID];i;i=Next[i]){
		if(to[i]!=fa&&!vis[to[i]]){
			d[to[i]]=d[ID]+w[i];
			if(d[to[i]]<=k){
				a[++Node_cnt]=to[i];
				if(b[ID]==0)
					b[to[i]]=to[i];
				else
					b[to[i]]=b[ID];
				GetSonTreeInformation(to[i],ID);
			}
		}
	}
	return;
}

void Calc(int p,int fa){
	register int i,l,r;
	d[p]=b[p]=Node_cnt=0;
	GetSonTreeInformation(p,fa);
	ans+=Node_cnt;
	if(Node_cnt<=1)
		return;
	for(i=1;i<=Node_cnt;++i)
		++Cnt[b[a[i]]];
	sort(a+1,a+Node_cnt+1,cmp);
	for(l=1,r=Node_cnt;l<=r;++l){
		while(l<r&&d[a[l]]+d[a[r]]>k)
			--Cnt[b[a[r--]]];
		if(l<=r){
			--Cnt[b[a[l]]];
			ans+=r-l-Cnt[b[a[l]]];
		}
	}
	return;
}

void Solve(int ID){
	register int i;
	Calc(ID,0);
	vis[ID]=true;
	for(i=head[ID];i;i=Next[i]){
		if(!vis[to[i]]){
			pos=0,MaxPart=INF;
			GetRoot(to[i],ID);
			Solve(pos);
		}
	}
	return;
}

void Add_Edge(int u,int v,int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool cmp(int a,int b){
	return d[a]<d[b];
}
