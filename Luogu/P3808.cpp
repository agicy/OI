#include<bits/stdc++.h>
using namespace std;
#define reg register
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXSIZE=500000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct Accepted_Automachine{
	int tot;
	int trie[MAXSIZE][26];
	int fail[MAXSIZE];
	int val[MAXSIZE];
	inline void insert(reg char str[MAXSIZE]){
		reg int ID=0;
		reg int len=strlen(str);
		for(reg int i=0;i<len;++i){
			reg int ch=str[i]-'a';
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
		for(reg int i=0;i<26;++i)
			if(trie[0][i]){
				fail[trie[0][i]]=0;
				Q.push(trie[0][i]);
			}
		while(!Q.empty()){
			reg int ID=Q.front();
			Q.pop();
			for(reg int i=0;i<26;++i){
				if(trie[ID][i])
					fail[trie[ID][i]]=trie[fail[ID]][i],Q.push(trie[ID][i]);
				else
					trie[ID][i]=trie[fail[ID]][i];
			}
		}
		return;
	}
	inline int Query(reg char str[]){
		reg int res=0,ID=0,len=strlen(str);
		for(reg int i=0;i<len;++i){
			reg int ch=str[i]-'a';
			ID=trie[ID][ch];
			for(reg int j=ID;j&&(~val[j]);j=fail[j]){
				res+=val[j];
				val[j]=-1;
			}
		}
		return res;
	}
};

int n;
char str[1000000+4];
Accepted_Automachine AC;

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		scanf("%s",str);
		AC.insert(str);
	}
	return;
}

inline void Work(void){
	AC.BFS();
	scanf("%s",str);
	reg int ans=AC.Query(str);
	printf("%d\n",ans);
	return;
}
