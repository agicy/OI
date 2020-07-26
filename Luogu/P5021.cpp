#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=50000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<n;++i){
		static int a,b,l;
		a=read(),b=read(),l=read();
		Add_Edge(a,b,l);
		Add_Edge(b,a,l);
	}
	return;
}

int MaxDis;

inline int DFS1(reg int ID,reg int father){
	int sum1=0,sum2=0;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			sum2=max(sum2,DFS1(to[i],ID)+w[i]);
			if(sum1<sum2)
				swap(sum1,sum2);
		}
	MaxDis=max(MaxDis,sum1+sum2);
	return sum1;
}

int tot;
multiset<int> S[MAXN];

inline int DFS(reg int ID,reg int father,reg int k){
	S[ID].clear();
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			int val=DFS(to[i],ID,k)+w[i];
			if(val>=k)
				++tot;
			else
				S[ID].insert(val);
		}
	int Max=0;
	while(!S[ID].empty()){
		static multiset<int>::iterator it;
		if(S[ID].size()==1)
			return max(Max,*S[ID].begin());
		it=S[ID].lower_bound(k-*S[ID].begin());
		if(it==S[ID].begin()&&S[ID].count(*it)==1)
			++it;
		if(it==S[ID].end())
			Max=max(Max,*S[ID].begin());
		else{
			++tot;
			S[ID].erase(S[ID].find(*it));
		}
		S[ID].erase(S[ID].find(*S[ID].begin()));
	}
	return Max;
}

inline bool check(reg int mid){
	tot=0;
	DFS(1,0,mid);
	return tot>=m;
}

inline void Work(void){
	DFS1(1,0);
	reg int l=1,r=MaxDis,mid;
	while(l<r){
		mid=(l+r+1)>>1;
		if(check(mid))
			l=mid;
		else
			r=mid-1;
	}
	printf("%d\n",l);
	return;
}
