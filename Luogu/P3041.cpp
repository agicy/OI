#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=20+5;
const int MAXK=1000+5;
const int MAXLEN=15+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

const int MAXSIZE=MAXN*MAXK*3;

struct Accepted_Automachine{
	int tot;
	int trie[MAXSIZE][3];
	int fail[MAXSIZE];
	int val[MAXSIZE];
	inline void insert(reg char str[]){
		reg int ID=0;
		reg int len=strlen(str);
		for(reg int i=0;i<len;++i){
			reg int ch=str[i]-'A';
			if(!trie[ID][ch])
				trie[ID][ch]=++tot;
			ID=trie[ID][ch];
		}
		++val[ID];
		return;
	}
	inline void BFS(void){
		queue<int> Q;
		while(!Q.empty())
			Q.pop();
		for(reg int i=0;i<3;++i)
			if(trie[0][i])
				Q.push(trie[0][i]);
		while(!Q.empty()){
			reg int ID=Q.front();
			Q.pop();
			for(reg int i=0;i<3;++i){
				if(trie[ID][i])
					fail[trie[ID][i]]=trie[fail[ID]][i],Q.push(trie[ID][i]);
				else
					trie[ID][i]=trie[fail[ID]][i];
			}
			val[ID]+=val[fail[ID]];
		}
		return;
	}
};

int n,K;
Accepted_Automachine AC;

inline void Read(void){
	n=read(),K=read();
	for(reg int i=1;i<=n;++i){
		static char str[MAXLEN];
		scanf("%s",str);
		AC.insert(str);
	}
	return;
}

int ans;
int f[MAXK][MAXSIZE];

inline void DP(void){
	for(reg int T=0;T<=K;++T)
		for(reg int i=1;i<=AC.tot;++i)
			f[T][i]=-1000;
	for(reg int T=1;T<=K;++T)
		for(reg int i=0;i<=AC.tot;++i)
			for(reg int j=0;j<3;++j)
				f[T][AC.trie[i][j]]=max(f[T][AC.trie[i][j]],f[T-1][i]+AC.val[AC.trie[i][j]]);
	for(reg int i=0;i<=AC.tot;++i)
		ans=max(ans,f[K][i]);
	return;
}

inline void Work(void){
	AC.BFS();
	DP();
	printf("%d\n",ans);
	return;
}
