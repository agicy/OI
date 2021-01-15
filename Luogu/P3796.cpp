#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
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

const int MAXN=150+5;
const int MAXS=70+5;
const int MAXT=1e6+5;
const int MAXSIZE=MAXN*MAXS;

struct Node{
	int id,cnt;
	inline bool operator<(const Node& a)const{
		return cnt==a.cnt?id<a.id:cnt>a.cnt;
	}
};

Node ans[MAXN];

namespace AC{
	struct Node{
		int ch[26],fail;
		int end;
		#define ch(x) unit[(x)].ch
		#define fail(x) unit[(x)].fail
		#define end(x) unit[(x)].end
	};
	Node unit[MAXSIZE];
	int tot;
	inline void Init(void){
		tot=0;
		memset(ch(0),0,sizeof(ch(0))),fail(0)=end(0)=0;
		return;
	}
	inline int New(void){
		reg int p=++tot;
		memset(ch(p),0,sizeof(ch(p))),fail(p)=end(p)=0;
		return p;
	}
	inline void insert(reg char *s,reg int len,reg int id){
		reg int p=0;
		for(reg int i=0;i<len;++i){
			reg int c=s[i]-'a';
			if(!ch(p)[c])
				ch(p)[c]=New();
			p=ch(p)[c];
		}
		end(p)=id;
		return;
	}
	inline void build(void){
		queue<int> Q;
		for(reg int i=0;i<26;++i)
			if(ch(0)[i])
				Q.push(ch(0)[i]);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			for(reg int i=0;i<26;++i)
				if(ch(u)[i])
					fail(ch(u)[i])=ch(fail(u))[i],Q.push(ch(u)[i]);
				else
					ch(u)[i]=ch(fail(u))[i];
		}
		return;
	}
	inline void query(reg char *s,reg int len){
		reg int p=0;
		for(reg int i=0;i<len;++i){
			reg int c=s[i]-'a';
			p=ch(p)[c];
			for(reg int j=p;j;j=fail(j))
				++ans[end(j)].cnt;
		}
		return;
	}
}

char s[MAXN][MAXS];
char t[MAXT];

int main(void){
	reg int n;
	while(n=read(),n){
		AC::Init();
		for(reg int i=1;i<=n;++i){
			read(s[i]);
			ans[i].id=i,ans[i].cnt=0;
			AC::insert(s[i],strlen(s[i]),i);
		}
		AC::build();
		read(t);
		AC::query(t,strlen(t));
		sort(ans+1,ans+n+1);
		printf("%d\n%s\n",ans[1].cnt,s[ans[1].id]);
		for(reg int i=2;i<=n;++i)
			if(ans[i].cnt==ans[i-1].cnt)
				printf("%s\n",s[ans[i].id]);
			else
				break;
	}
	return 0;
}