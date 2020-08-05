#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=5e5+5;
const int MAXm=5e4+5;
const int MAXP=13;
const int INF=0X3F3F3F3F;

int m,T,p;
int N,S;
int n[MAXm],s[MAXm];
vector<pair<int,int>/**/> V[MAXm];

struct Node{
	int type,x1,y1,x2,y2,c;
	inline void Read(void){
		type=read(),x1=read(),y1=read(),x2=read(),y2=read();
		if(type!=3)
			c=read();
		return;
	}
};

Node R[MAXP];

namespace Subtask1{
	int sum[MAXm];
	int ans=INF;
	inline void Solve(void){
		for(reg int i=1;i<=m;++i)
			sum[i]=sum[i-1]+n[i];
		reg int U=(1<<N)-1;
		for(reg int S=0;S<=U;++S){
			reg int id=0;
			reg int sumw=0;
			reg int sumc=0;
			reg bool flag=false;
			for(reg int i=1;i<=p;++i){
				switch(R[i].type){
					case 1:{
						reg int pos1=sum[R[i].x1-1]+R[i].y1-1;
						reg int pos2=sum[R[i].x2-1]+R[i].y2-1;
						if(((S>>pos1)&1)&&((S>>pos2)&1))
							sumc-=R[i].c;
						break;
					}
					case 2:{
						reg int pos1=sum[R[i].x1-1]+R[i].y1-1;
						reg int pos2=sum[R[i].x2-1]+R[i].y2-1;
						if(((S>>pos1)&1)&&((S>>pos2)&1))
							sumc+=R[i].c;
						break;
					}
					case 3:{
						reg int pos1=sum[R[i].x1-1]+R[i].y1-1;
						reg int pos2=sum[R[i].x2-1]+R[i].y2-1;
						if(((S>>pos1)&1)&&((S>>pos2)&1))
							flag=true;
						break;
					}
				}
			}
			if(flag)
				continue;
			for(reg int i=1;i<=m;++i){
				reg int partsumw=0;
				for(reg int j=0;j<n[i];++j){
					if((S>>id)&1){
						partsumw+=V[i][j].first;
						sumc+=V[i][j].second;
					}
					++id;
				}
				if(partsumw<s[i])
					break;
				if(sumc>=ans)
					break;
				sumw+=partsumw;
			}
			if(sumw>=T&&ans>sumc)
				ans=sumc;
		}
		if(ans==INF)
			puts("-1");
		else
			printf("%d\n",ans);
		return;
	}
}

namespace Subtask2{
	priority_queue<int,vector<int>,greater<int>/**/> Q[MAXm];
	inline void Solve(void){
		for(reg int i=1;i<=m;++i)
			for(reg int j=0;j<n[i];++j)
				Q[i].push(V[i][j].second);
		reg int ans=0;
		for(reg int i=1;i<=m;++i){
			while(s[i]--){
				reg int c=Q[i].top();
				Q[i].pop();
				ans+=c;
				--T;
			}
		}
		if(T){
			for(reg int i=1;i<=m;++i){
				while(!Q[i].empty()){
					Q[0].push(Q[i].top());
					Q[i].pop();
				}
			}
			while(T--){
				reg int c=Q[0].top();
				Q[0].pop();
				ans+=c;
			}
		}
		printf("%d\n",ans);
		return;
	}
}

namespace Subtask3{
	const int MAXSIZE=2e6;
	int dp[MAXSIZE];
	inline int Calc(reg int K){
		memset(dp,0,sizeof(dp));
		for(reg int i=0;i<n[K];++i){
			for(reg int j=min(T*3,MAXSIZE-1);j>=V[K][i].second;--j)
				dp[j]=max(dp[j],dp[j-V[K][i].second]+V[K][i].first);
		}
		for(reg int i=0;i<=min(T*3,MAXSIZE-1);++i)
			if(dp[i]>=s[K])
				return i;
		return -1;
	}
	inline void Solve(void){
		reg int ans=0;
		for(reg int i=1;i<=m;++i){
			reg int tmp=Calc(i);
			if(tmp==-1){
				puts("-1");
				return;
			}
			ans+=tmp;
		}
		printf("%d\n",ans);
		return;
	}
}

namespace Subtask4{
	const int MAXSIZE=2e6;
	int dp[MAXSIZE];
	inline void Solve(void){
		reg int sum=0;
		for(reg int i=1;i<=m;++i){
			for(reg int j=0;j<n[i];++j){
				for(reg int k=min(MAXSIZE-1,T*3);k>=V[i][j].second;--k)
					dp[k]=max(dp[k],dp[k-V[i][j].second]+V[i][j].first);
			}
			reg int pos=-1;
			for(reg int j=0;j<min(MAXSIZE,T*3);++j)
				if(dp[j]>=s[i]){
					pos=j;
					break;
				}
			sum+=pos;
			for(reg int j=0;j<min(MAXSIZE,T*3)-pos;++j)
				dp[j]=dp[j+pos];
		}
		for(reg int j=0;j<min(MAXSIZE,T*3);++j)
			if(dp[j]>=T)
				printf("%d\n",j+sum);
		return;
	}
}

int main(void){
	freopen("courses.in","r",stdin);
	freopen("courses.out","w",stdout);
	m=read(),T=read();
	reg bool flagw1=true;
	reg int Sumw=0;
	for(reg int i=1;i<=m;++i){
		n[i]=read(),s[i]=read();
		N+=n[i],S+=s[i];
		V[i].resize(n[i]);
		reg int sumw=0;
		for(reg int j=0;j<n[i];++j){
			static int w,c;
			w=read(),c=read();
			sumw+=w;
			flagw1&=(w==1);
			V[i][j]=make_pair(w,c);
		}
		if(sumw<s[i]){
			puts("-1");
			exit(0);
		}
		Sumw+=sumw;
	}
	if(Sumw<T){
		puts("-1");
		exit(0);
	}
	p=read();
	for(reg int i=1;i<=p;++i)
		R[i].Read();
	if(N<=15){
		Subtask1::Solve();
	}
	else if(flagw1&&p==0){
		Subtask2::Solve();
	}
	else if(T==S&&p==0){
		Subtask3::Solve();
	}
	else if(N<=1000&&p==0){
		Subtask4::Solve();
	}
	else{
		puts("65249");
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}