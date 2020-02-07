#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

struct Node{
	int ID,val;
	inline Node(reg int ID=0,reg int val=0):ID(ID),val(val){
		return;
	}
	bool operator<(const Node &a)const{
		return val<a.val;
	}
	bool operator==(const Node &a)const{
		return val==a.val;
	}
};

int n;
Node a[MAXN];

bool cmp(const Node &a,const Node &b){
	return a.ID<b.ID;
}

int main(void){
	reg int T=read();
	while(T--){
		n=read();
		for(reg int i=1;i<=n;++i)
			a[i]=Node(i,read());
		stable_sort(a+1,a+n+1);
		reg int len=unique(a+1,a+n+1)-(a+1);
		sort(a+1,a+len+1,cmp);
		for(reg int i=1;i<=len;++i)
			printf("%d%c",a[i].val,i==len?'\n':' ');
	}
	return 0;
}
