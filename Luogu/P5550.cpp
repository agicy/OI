#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=80+5;

int n,s,m,k;

struct Node{
	int n;
	ll unit[MAXN];
	inline void Read(reg int size){
		n=size;
		for(reg int i=1;i<=n;++i)
			unit[i]=read();
		return;
	}
	inline bool operator<(const Node& a)const{
		for(reg int i=1;i<=n;++i)
			if(unit[i]<a.unit[i])
				return true;
		return false;
	}
	inline void opt(void){
		swap(unit[s],unit[m]);
		reg int temp=unit[1];
		for(reg int i=2;i<=n;++i)
			unit[i-1]=unit[i];
		unit[n]=temp;
		return;
	}
	inline void Print(void){
		for(reg int i=1;i<=n;++i)
			printf("%lld%c",unit[i],i==n?'\n':' ');
		return;
	}
};

Node st;
map<Node,int> M;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read(),s=read(),m=read(),k=read();
	st.Read(n);
	return;
}

inline void Work(void){
	M[st]=0;
	reg int cnt=0;
	int cnr=-1;
	while(k--){
		st.opt();
		++cnt;
		if(M[st]){
			cnr=cnt-M[st];
			break;
		}
		M[st]=cnt;
	}
	if(cnr==-1)
		st.Print();
	else{ 
		k%=cnr;
		while(k--)
			st.opt();
		st.Print();
	}
	return;
}