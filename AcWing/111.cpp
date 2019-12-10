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
	while(ch<'0'||'9'<ch)f|=(ch='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=50000+5;

struct Node{
	int ID,s,t;
	inline bool operator<(const Node& a)const{
		return s<a.s;
	}
	inline void Read(reg int i){
		s=read(),t=read();
		ID=i;
		return;
	}
};

struct Element{
	int ID,last;
	inline Element(void){
		ID=last=0;
		return;
	}
	inline Element(reg int a,reg int b){
		ID=a,last=b;
		return;
	}
	inline bool operator<(const Element& a)const{
		return last<a.last;
	}
	inline bool operator>(const Element& a)const{
		return last>a.last;
	}
};

int n;
int cnt;
int ans[MAXN];
Node I[MAXN];
priority_queue<Element,vector<Element>,greater<Element>/**/> Q;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		I[i].Read(i);
	return;
}

inline void Work(void){
	sort(I+1,I+n+1);
	for(reg int i=1;i<=n;++i)
		if(Q.empty()||Q.top().last>=I[i].s){
			Q.push(Element(++cnt,I[i].t));
			ans[I[i].ID]=cnt;
		}
		else{
			Element temp=Q.top();
			Q.pop();
			Q.push(Element(temp.ID,I[i].t));
			ans[I[i].ID]=temp.ID;
		}
	printf("%d\n",cnt);
	for(reg int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
	return;
}
