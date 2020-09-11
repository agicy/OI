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

const int MAXN=1e5+5;

int n;
int a[MAXN];

namespace Subtask1{
	struct Q2Q{
		priority_queue<int,vector<int>,less<int>/**/> fr;
		priority_queue<int,vector<int>,greater<int>/**/> ba;
		inline void Init(void){
			while(!fr.empty())fr.pop();
			while(!ba.empty())ba.pop();
			return;
		}
		inline void push(int x){
			if(fr.empty())
				fr.push(x);
			else
				ba.push(x);
			while(fr.size()>ba.size()){
				ba.push(fr.top());
				fr.pop();
			}
			while(ba.size()>fr.size()+1){
				fr.push(ba.top());
				ba.pop();
			}
			while(!ba.empty()&&!fr.empty()&&fr.top()>ba.top()){
				int tmp1=fr.top(),tmp2=ba.top();
				fr.pop(),ba.pop();
				fr.push(tmp2),ba.push(tmp1);
			}
			return;
		}
		inline int top(void){
			return ba.top();
		}
	};
	Q2Q q,Q;
	inline void Solve(void){
		Q.Init();
		for(reg int i=1;i<=n;++i){
			q.Init();
			for(reg int j=i;j<=n;++j){
				q.push(a[j]);
				Q.push(q.top());
			}
		}
		printf("%d\n",Q.top());
		return;
	}
}

namespace Subtask2{
	struct Q2Q{
		priority_queue<int,vector<int>,less<int>/**/> fr;
		priority_queue<int,vector<int>,greater<int>/**/> ba;
		inline void Init(void){
			while(!fr.empty())fr.pop();
			while(!ba.empty())ba.pop();
			return;
		}
		inline void push(int x){
			if(fr.empty())
				fr.push(x);
			else
				ba.push(x);
			while(fr.size()>ba.size()){
				ba.push(fr.top());
				fr.pop();
			}
			while(ba.size()>fr.size()+1){
				fr.push(ba.top());
				ba.pop();
			}
			while(!ba.empty()&&!fr.empty()&&fr.top()>ba.top()){
				int tmp1=fr.top(),tmp2=ba.top();
				fr.pop(),ba.pop();
				fr.push(tmp2),ba.push(tmp1);
			}
			return;
		}
		inline int top(void){
			return ba.top();
		}
	};
	Q2Q q,Q;
	vector<int> V;
	int S[MAXN];
	inline double sqr(reg double x){
		return x*x;
	}
	inline void Solve(void){
		reg double sum=0;
		for(reg int i=1;i<=n;++i)
			sum+=a[i];
		reg double bar=sum/n;
		reg double s2n=0;
		for(reg int i=1;i<=n;++i)
			s2n+=sqr(a[i]-bar);
		reg double s2=s2n/n;
		reg double s=sqrt(s2);

		const double alpha=0.7;
		reg double delta=s*alpha;

		reg double l=bar-delta,r=bar+delta;
		
		reg int top=0;
		for(reg int i=1;i<=n;++i)
			if(l<=a[i]&&a[i]<=r)
				S[++top]=a[i];
		
		Q.Init();
		for(reg int i=1;i<=top;++i){
			q.Init();
			for(reg int j=i;j<=top;++j){
				q.push(S[j]);
				Q.push(q.top());
			}
		}
		printf("%d\n",Q.top());
		return;
	}
}

namespace Subtask3{
	vector<int> V;
	int tmp[MAXN];

	int T[MAXN*2];
	const int delta=MAXN;
	inline void Solve(reg int l,reg int r){
		reg int mid=(l+r)>>1;
		reg int sum=0;
		for(reg int i=mid;i>=l;--i){
			sum+=tmp[i];
			++T[sum+delta];
		}
		for(reg int i=mid+1;i<=r;++i){
			
		}
		return;
	}
	inline void check(reg int mid){
		for(reg int i=1;i<=n;++i)
			tmp[i]=(a[i]<mid)?-1:1;
		
		return;
	}
	inline void Solve(void){
		V.resize(n);
		for(reg int i=1;i<=n;++i)
			V[i-1]=a[i];
		sort(V.begin(),V.end());
		V.erase(unique(V.begin(),V.end()),V.end());
		for(reg int i=1;i<=n;++i)
			a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
		reg int l=1,r=V.size(),mid;
		while(l<r){
			mid=(l+r)>>1;
			if(check(mid))

			else

		}
	}
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	reg bool flag=true;
	for(reg int i=2;i<=n;++i)
		if(a[i]!=a[i-1]){
			flag=false;
			break;
		}
	if(flag)
		printf("%d\n",a[n]);
	else{
		if(n<=300)
			Subtask1::Solve();
		else
			Subtask2::Solve();
	}
	return 0;
}