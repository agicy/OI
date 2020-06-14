#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef unsigned int uint;
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

namespace Trie{
	const int MAXSIZE=1000000*32+5;
	int tot;
	int ch[MAXSIZE][2];
	int tag[MAXSIZE];
	inline void insert(reg uint ip,reg int id,reg int l){
		reg int ID=0;
		for(reg int i=31;i>=32-l;--i){
			if(!ch[ID][(ip>>i)&1])
				ch[ID][(ip>>i)&1]=++tot;
			ID=ch[ID][(ip>>i)&1];
		}
		tag[ID]=id;
		return;
	}
	int S[MAXSIZE],top;
	inline int query(reg uint ip,reg int a,reg int b){
		reg int ID=0;
		for(reg int i=31;i>=0;--i){
			if(!ch[ID][(ip>>i)&1])
				break;
			ID=ch[ID][(ip>>i)&1];
			if(tag[ID]){
				while(top&&tag[ID]<S[top])
					--top;
				S[++top]=tag[ID];
			}
		}
		reg int res=0;
		while(top){
			reg int x=S[top--];
			if(a<=x&&x<=b)
				++res;
		}
		return res;
	}
}

using namespace Trie;

inline uint GetIP(void){
	reg uint a=read(),b=read(),c=read(),d=read();
	return (a<<24)|(b<<16)|(c<<8)|(d);
}

int main(void){
	reg int m=read();
	reg int cnt=0;
	while(m--){
		static char opt;
		static uint d;
		static int l,a,b;
		do
			opt=getchar();
		while(opt!='A'&&opt!='Q');
		d=GetIP();
		switch(opt){
			case 'A':{
				l=read();
				insert(d,++cnt,l);
				break;
			}
			case 'Q':{
				a=read(),b=read();
				printf("%d\n",query(d,a,b));
				break;
			}
			default:break;
		}
	}
	return 0;
}