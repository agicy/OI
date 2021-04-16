#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXS=1e6+5;

int lg[MAXS];

namespace AC{
	const int MAXSIZE=500;
	struct Node{
		int ch[26],fail;
		int sum,val;
		#define ch(x) unit[(x)].ch
		#define fail(x) unit[(x)].fail
		#define sum(x) unit[(x)].sum
		#define val(x) unit[(x)].val
	};
	int tot;
	Node unit[MAXS];
	inline int getId(void){
		return ++tot;
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
	int Q[MAXS];
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
	inline int query(reg int id,reg char *s){
		reg int rt=Rt[id],p=rt,res=0;
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
	inline int query(reg char *s){
		reg int res=0;
		for(reg int i=1;i<=cnt;++i)
			res+=query(i,s);
		return res;
	}
}

int n;
char s[MAXS];

int main(void){
	scanf("%d",&n);
	lg[0]=-1;
	for(reg int i=1;i<MAXS;++i)
		lg[i]=lg[i>>1]+1;
	AC::Init();
	while(n--){
		static int opt;
		scanf("%d%s",&opt,s);
		switch(opt){
			case 1:{
				AC::insert(s,1);
				break;
			}
			case 2:{
				AC::insert(s,-1);
				break;
			}
			case 3:{
				printf("%d\n",AC::query(s));
				fflush(stdout);
				break;
			}
		}
	}
	return 0;
}