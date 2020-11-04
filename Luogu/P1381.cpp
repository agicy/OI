#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=1e3+5;
const int MAXM=1e5+5;
const int MAXLEN=16;
const ull base=1331;

int n,m;
unordered_map<ull,int> M;
bool vis[MAXN];
int p[MAXM];
int cnt;
int T[MAXN];

inline void add(reg int x){
	if(x){
		if(!T[x])
			++cnt;
		++T[x];
	}
	return;
}

inline void del(reg int x){
	if(x){
		--T[x];
		if(!T[x])
			--cnt;
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static char word[MAXLEN];
		scanf("%s",word+1);
		reg int len=strlen(word+1);
		ull H=0;
		for(reg int j=1;j<=len;++j)
			H=H*base+(word[j]-'a'+1);
		M[H]=i;
	}
	m=read();
	reg int tot=0;
	for(reg int i=1;i<=m;++i){
		static char word[MAXLEN];
		scanf("%s",word+1);
		reg int len=strlen(word+1);
		ull H=0;
		for(reg int j=1;j<=len;++j)
			H=H*base+(word[j]-'a'+1);
		if(M.count(H)){
			p[i]=M[H];
			if(!vis[M[H]])
				++tot,vis[M[H]]=true;
		}
		else
			p[i]=0;
	}
	int ans=m;
	for(reg int l=1,r=0;l<=m;del(p[l++])){
		while(r<m&&cnt<tot)
			add(p[++r]);
		if(cnt<tot)
			break;
		if(cnt==tot)
			cMin(ans,max(r-l+1,0));
	}
	printf("%d\n%d\n",tot,ans);
	return 0;
}