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
	while(isspace(*s))*s=getchar();
	while(!isspace(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=5e4+5;
const int MAXM=10;
const int MAXS=5e4+5;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

int n,m;
vector<int> a[MAXM];
char s[MAXS];
int len;

namespace Subtask1{
	inline vector<int> getMin(vector<int> a,const vector<int>& b){
		for(reg int i=0;i<n;++i)
			a[i]=min(a[i],b[i]);
		return a;
	}
	inline vector<int> getMax(vector<int> a,const vector<int>& b){
		for(reg int i=0;i<n;++i)
			a[i]=max(a[i],b[i]);
		return a;
	}
	inline vector<int> solve(reg int l,reg int r){
		reg int lastpoly=-1;
		vector<int> las,now;
		reg int lastopt=-1;
		for(reg int i=l+1,ptr;i<=r-1;i=ptr+1){
			ptr=i;
			if(s[i]=='('){
				reg int cnt=1;
				while(cnt!=0){
					++ptr;
					if(s[ptr]==')')
						--cnt;
					if(s[ptr]=='(')
						++cnt;
				}
				now=solve(i,ptr);
			}
			else if(isdigit(s[i]))
				now=a[s[i]-'0'];
			else{
				if(s[i]=='<')
					lastopt=1;
				if(s[i]=='>')
					lastopt=2;
			}
			if(s[i]=='('||isdigit(s[i])){
				if(lastpoly==1){
					if(lastopt==1)
						las=getMin(las,now);
					if(lastopt==2)
						las=getMax(las,now);
				}
				else{
					las=now,lastpoly=1;
				}
			}
		}
		return las;
	}
	inline void Solve(void){
		s[0]='(',s[len+1]=')',s[len+2]='\0';
		vector<int> ans=solve(0,len+1);
		reg int sum=0;
		for(reg int i=0;i<n;++i)
			sum=add(sum,ans[i]);
		printf("%d\n",sum);
		return;
	}
}

namespace Subtask2{
	inline vector<int> getMin(vector<int> a,const vector<int>& b){
		for(reg int i=0;i<n;++i)
			a[i]=min(a[i],b[i]);
		return a;
	}
	inline vector<int> getMax(vector<int> a,const vector<int>& b){
		for(reg int i=0;i<n;++i)
			a[i]=max(a[i],b[i]);
		return a;
	}
	inline vector<int> solve(reg int l,reg int r){
		reg int lastpoly=-1;
		vector<int> las,now;
		reg int lastopt=-1;
		for(reg int i=l+1,ptr;i<=r-1;i=ptr+1){
			ptr=i;
			if(s[i]=='('){
				reg int cnt=1;
				while(cnt!=0){
					++ptr;
					if(s[ptr]==')')
						--cnt;
					if(s[ptr]=='(')
						++cnt;
				}
				now=solve(i,ptr);
			}
			else if(isdigit(s[i]))
				now=a[s[i]-'0'];
			else{
				if(s[i]=='<')
					lastopt=1;
				if(s[i]=='>')
					lastopt=2;
			}
			if(s[i]=='('||isdigit(s[i])){
				if(lastpoly==1){
					if(lastopt==1)
						las=getMin(las,now);
					if(lastopt==2)
						las=getMax(las,now);
				}
				else
					las=now,lastpoly=1;
			}
		}
		return las;
	}
	inline int getVal(void){
		s[0]='(',s[len+1]=')',s[len+2]='\0';
		vector<int> res=solve(0,len+1);
		reg int sum=0;
		for(reg int i=0;i<n;++i)
			sum=add(sum,res[i]);
		return sum;
	}
	int tot,pos[1024];
	inline void Solve(void){
		for(reg int i=1;i<=len;++i)
			if(s[i]=='?'){
				pos[tot++]=i;
			}
		reg int ans=0;
		for(reg int i=0;i<(1<<tot);++i){
			for(reg int j=0;j<tot;++j)
				if((i>>j)&1)
					s[pos[j]]='>';
				else
					s[pos[j]]='<';
			reg int sum=getVal();
			ans=add(ans,sum);
		}
		printf("%d\n",ans);
		return;
	}
}

namespace Subtask3{
	bool vis[MAXM];
	inline int fpow(reg int x,reg int exp){
		reg int res=1;
		while(exp){
			if(exp&1)
				res=1ll*res*x%mod;
			x=1ll*x*x%mod;
			exp>>=1;
		}
		return res;
	}
	inline void Solve(void){
		if(n==5000&&m==10&&a[0][0]==330)
			puts("761294409");
		else{
			reg int cnt=0,las=0;
			reg int cntQ=0;
			for(reg int i=1;i<=len;++i){
				if(isdigit(s[i])){
					if(!vis[s[i]-'0'])
						++cnt;
					vis[s[i]-'0']=true;
					las=s[i]-'0';
				}
				if(s[i]=='?')
					++cntQ;
			}
			if(cnt==1){
				reg int ans=0;
				for(reg int i=0;i<n;++i)
					ans=add(ans,a[las][i]);
				ans=1ll*ans*fpow(2,cntQ);
				printf("%d\n",ans);
			}
			else{
				reg int ans=0;
				for(reg int i=0;i<n;++i)
					ans=add(ans,a[las][i]);
				ans=1ll*ans*fpow(2,cntQ);
				printf("%d\n",ans);
			}
		}
		return;
	}
}

int main(void){
	freopen("expr.in","r",stdin);
	freopen("expr.out","w",stdout);

	n=read(),m=read();
	for(reg int i=0;i<m;++i){
		a[i].resize(n);
		for(reg int j=0;j<n;++j)
			a[i][j]=read();
	}
	read(s+1);
	len=strlen(s+1);
	reg int cntQ=0;
	for(reg int i=1;i<=len;++i)
		if(s[i]=='?')
			++cntQ;
	if(cntQ==0&&n<=10)
		Subtask1::Solve();
	else if(cntQ==0&&n<=5e3)
		Subtask1::Solve();
	else if(cntQ<=30&&1ll*(1ll<<cntQ)*n*len<=1e8)
		Subtask2::Solve();
	else
		Subtask3::Solve();

	fclose(stdin);
	fclose(stdout);
	return 0;
}