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
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXS=2e6+5;
const int MAXT=2e6+5;

int lg[MAXS];

namespace AC{
	const int MAXSIZE=500;
	struct Node{
		int ch[26];
		int fail;
		int sum,val;
		#define ch(x) unit[(x)].ch
		#define fail(x) unit[(x)].fail
		#define sum(x) unit[(x)].sum
		#define val(x) unit[(x)].val
	};
	int tot;
	Node unit[MAXS+MAXT];
	inline int getId(void){
		return tot++;
	}
	inline int New(void){
		reg int p=getId();
		memset(&unit[p],0,sizeof(Node));
		return p;
	}
	int cnt,Rt[MAXSIZE],siz[MAXSIZE];
	inline void insert(reg int id,reg char *s,reg int Val){
		reg int rt=Rt[id],p=rt;
		while(*s){
			reg int c=*(s++)-'a';
			if(!ch(p)[c])
				ch(p)[c]=New(),++siz[id];
			p=ch(p)[c];
		}
		sum(p)+=Val,val(p)+=Val;
		return;
	}
	int Q[MAXS+MAXT];
	inline void build(reg int rt){
		reg int _head=0,_tail=0;
		for(reg int i=0;i<26;++i)
			if(ch(rt)[i])
				fail(ch(rt)[i])=rt,Q[_tail++]=ch(rt)[i];
		while(_head<_tail){
			reg int u=Q[_head++];
			for(reg int i=0;i<26;++i)
				if(ch(u)[i]){
					reg int v=ch(u)[i],f=fail(u);
					while(f!=rt&&!ch(f)[i])
						f=fail(f);
					if(ch(f)[i])
						fail(v)=ch(f)[i],sum(v)+=sum(fail(v));
					else
						fail(v)=rt;
					Q[_tail++]=v;
				}
		}
		return;
	}
	inline ll query(reg int id,reg char *s){
		reg int rt=Rt[id],p=rt;
		reg ll res=0;
		while(*s){
			reg int c=*(s++)-'a';
			while(p!=rt&&!ch(p)[c])
				p=fail(p);
			if(ch(p)[c])
				p=ch(p)[c],res+=sum(p);
		}
		return res;
	}
	inline void Init(void){
		cnt=1,tot=0;
		Rt[1]=New(),siz[1]=0;
		return;
	}
	inline void dfs1(reg int ida,reg int a,reg int b){
		for(reg int i=0;i<26;++i)
			if(ch(b)[i]){
				if(!ch(a)[i])
					ch(a)[i]=New(),++siz[ida];
				val(ch(a)[i])+=val(ch(b)[i]);
				dfs1(ida,ch(a)[i],ch(b)[i]);
			}
		return;
	}
	inline void dfs2(reg int p){
		sum(p)=val(p);
		for(reg int i=0;i<26;++i)
			if(ch(p)[i])
				dfs2(ch(p)[i]);
		return;
	}
	inline void insert(reg char *s,reg int Val){
		insert(cnt,s,Val),build(Rt[cnt]);
		while(cnt>1&&lg[siz[cnt]]>=lg[siz[cnt-1]])
			dfs1(cnt-1,Rt[cnt-1],Rt[cnt]),dfs2(Rt[cnt-1]),build(Rt[cnt-1]),--cnt;
		++cnt,Rt[cnt]=New(),siz[cnt]=0;
		return;
	}
	inline ll query(reg char *s){
		reg ll res=0;
		for(reg int i=1;i<=cnt;++i)
			res+=query(i,s);
		return res;
	}
}

int n,type;
char s[MAXS];

int main(void){
	n=read(),type=read();
	lg[0]=-1;
	for(reg int i=1;i<MAXS;++i)
		lg[i]=lg[i>>1]+1;
	reg ll lastans=0;
	AC::Init();
	while(n--){
		static int opt;
		opt=read(),read(s);
		if(type){
			reg char *tmp=s;
			while(*tmp)
				*tmp=((*tmp-'a'+0ll)^lastans)%26+'a',++tmp;
		}
		switch(opt){
			case 0:{
				AC::insert(s,read());
				break;
			}
			case 1:{
				writeln(lastans=AC::query(s));
				break;
			}
		}
	}
	flush();
	return 0;
}