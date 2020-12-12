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

const int MAXN=(1<<20)+5;
const int MAXS=26;

int n;
char s[MAXN];
int Z[MAXN];
int sum[MAXS];
bool T_O[MAXS],T_E[MAXS];

int main(void){
	reg int t=read();
	while(t--){
		read(s);
		n=strlen(s);
		for(reg int i=1,mid=-1,r=-1;i<n;++i){
			if(i<=r)
				Z[i]=min(Z[i-mid],r-i+1);
			else
				Z[i]=0;
			while(i+Z[i]<n&&s[Z[i]]==s[i+Z[i]])
				++Z[i];
			if(i+Z[i]>r)
				mid=i,r=i+Z[i]-1;
		}
		for(reg int i=0;i<26;++i)
			sum[i]=T_O[i]=T_E[i]=0;
		reg int cntO=0,cntE=0;
		for(reg int i=0;i<n;++i)
			T_O[s[i]-'a']^=1;
		for(reg int i=0;i<26;++i)
			cntO+=T_O[i];
		reg int cnt=0;
		reg ll ans=0;
		for(reg int i=1,ptrA=0,ptrC=cntO;i<n;++i){
			if(T_O[s[i-1]-'a'])
				cnt-=sum[ptrC--];
			else
				cnt+=sum[++ptrC];
			T_O[s[i-1]-'a']^=1;
			reg int tot=min(Z[i],n-i-1)/i+1;
			reg int cnt1=(tot+1)>>1,cnt2=(tot)>>1;
			ans+=1ll*cnt*cnt1;
			if(T_E[s[i-1]-'a'])
				--ptrA;
			else
				++ptrA;
			T_E[s[i-1]-'a']^=1;
			++sum[ptrA];
			if(ptrA<=ptrC)
				++cnt;
			ans+=1ll*cntE*cnt2;
			if(ptrA<=cntO)
				++cntE;
		}
		printf("%lld\n",ans);
	}
	return 0;
}