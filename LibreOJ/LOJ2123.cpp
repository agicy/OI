#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXS=2e3+5;

struct SAM{
	struct Node{
		int fa,len;
		int ch[26];
		#define fa(x) unit[(x)].fa
		#define len(x) unit[(x)].len
		#define ch(x) unit[(x)].ch
	};
	int tot,las;
	Node unit[MAXS<<1];
	inline void init(void){
		tot=las=1;
		return;
	}
	inline void insert(reg int c){
		reg int np=++tot,p=las;
		len(np)=len(p)+1;
		while(p&&!ch(p)[c])
			ch(p)[c]=np,p=fa(p);
		if(!p)
			fa(np)=1;
		else{
			reg int q=ch(p)[c];
			if(len(p)+1==len(q))
				fa(np)=q;
			else{
				reg int nq=++tot;
				unit[nq]=unit[q];
				len(nq)=len(p)+1;
				fa(np)=fa(q)=nq;
				while(p&&ch(p)[c]==q)
					ch(p)[c]=nq,p=fa(p);
			}
		}
		las=np;
		return;
	}
	inline void build(reg char str[],reg int len){
		init();
		for(reg int i=1;i<=len;++i)
			insert(str[i]-'a');
		return;
	}
	inline int st(void)const{
		return 1;
	}
	inline int getTrans(reg int x,reg int c)const{
		return ch(x)[c];
	}
	#undef fa
	#undef len
	#undef ch
};

struct SeqAM{
	struct Node{
		int ch[26];
		#define ch(x) unit[(x)].ch
	};
	Node unit[MAXS];
	inline void build(reg char str[],reg int len){
		for(reg int i=len;i>=1;--i){
			unit[i-1]=unit[i];
			ch(i-1)[str[i]-'a']=i;
		}
		return;
	}
	inline int st(void)const{
		return 0;
	}
	inline int getTrans(reg int x,reg int c)const{
		return ch(x)[c];
	}
	#undef ch
};

SAM sam1,sam2;
SeqAM seq1,seq2;

struct Node{
	int x,y,val;
	inline Node(reg int x=0,reg int y=0,reg int val=0):x(x),y(y),val(val){
		return;
	}
};

template<typename T1,typename T2>int bfs(const T1& a,const T2& b){
	static bool vis[MAXS<<1][MAXS<<1];
	memset(vis,false,sizeof(vis));
	queue<Node> Q;
	vis[a.st()][b.st()]=true,Q.push(Node(a.st(),b.st(),0));
	while(!Q.empty()){
		static Node s;
		s=Q.front();
		Q.pop();
		reg int Sa=s.x,Sb=s.y,len=s.val;
		for(reg int i=0;i<26;++i)
			if(a.getTrans(Sa,i)){
				if(b.getTrans(Sb,i)){
					reg int tSa=a.getTrans(Sa,i),tSb=b.getTrans(Sb,i);
					if(!vis[tSa][tSb])
						vis[tSa][tSb]=true,Q.push(Node(tSa,tSb,len+1));
				}
				else
					return len+1;
			}
	}
	return -1;
}

char s[MAXS];

int main(void){
	scanf("%s",s+1);
	sam1.build(s,strlen(s+1)),seq1.build(s,strlen(s+1));
	scanf("%s",s+1);
	sam2.build(s,strlen(s+1)),seq2.build(s,strlen(s+1));
	reg int ans1=bfs(sam1,sam2);
	reg int ans2=bfs(sam1,seq2);
	reg int ans3=bfs(seq1,sam2);
	reg int ans4=bfs(seq1,seq2);
	printf("%d\n%d\n%d\n%d\n",ans1,ans2,ans3,ans4);
	return 0;
}