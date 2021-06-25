#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s)) *s=getchar();
	while(isalpha(*s)) *(++s)=getchar();
	*s='\0';
	return;
}

const int MAXS=2e6+5;
const ull base=1331;

int n;
map<ull,int> M;

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		reg int len=read();
		static char str[MAXS];
		read(str+1);
		static int kmp[MAXS];
		kmp[1]=0;
		for(reg int i=2,j=0;i<=len;++i){
			while(j&&str[i]!=str[j+1])
				j=kmp[j];
			if(str[i]==str[j+1])
				++j;
			kmp[i]=j;
		}
		reg int cir=len-(len%(len-kmp[len])?0:kmp[len]);
		ull val=0;
		for(reg int i=1;i<=cir;++i)
			val=val*base+str[i]-'a'+1;
		++M[val];
	}
	reg ll ans=0;
	for(map<ull,int>::iterator it=M.begin();it!=M.end();++it)
		ans+=1ll*it->second*it->second;
	printf("%lld\n",ans);
	return 0;
}