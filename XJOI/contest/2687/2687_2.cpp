#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

int n,m;

struct Node{
	int cnt,lim;
	inline Node(reg int cnt=0,reg int lim=0):cnt(cnt),lim(lim){
		return;
	}
};

inline int mod(reg int x){
	if(x<0)
		return x+13;
	else
		return x;
}

struct State{
	int _sum,cnt[13];
	//0 1 2 3 4 5 6 7 8 9 0 1 2
	//3 4 5 6 7 8 9 0 J Q K A 2
	inline State(void){
		memset(cnt,0,sizeof(cnt));
		return;
	}
	inline int sum(void)const{
		return _sum;
	}
	inline bool empty(void)const{
		return !_sum;
	}
	inline bool check(const Node& a)const{
		if(a.cnt>=5){
			if(a.lim+a.cnt-1>11)
				return false;
			for(reg int i=0;i<a.cnt;++i)
				if(!cnt[mod(i+a.lim)])
					return false;
			return true;
		}
		else
			return cnt[a.lim]>=a.cnt;
	}
	inline State chg(const Node& a)const{
		State res=*this;
		res._sum-=a.cnt;
		if(a.cnt>=5)
			for(reg int i=0;i<a.cnt;++i)
				--res.cnt[mod(i+a.lim)];
		else
			res.cnt[a.lim]-=a.cnt;
		return res;
	}
};

/*
inline void print(State x){
	printf("3 4 5 6 7 8 9 0 J Q K A 2\n");
	for(reg int i=0;i<13;++i)
		printf("%d ",x.cnt[i]);
	puts("");
	return;
}
*/

const int inf=1e9;

inline bool check(const Node& a,const Node& b){
	//assert(a.cnt);
	if(b.cnt==0)
		return true;
	else if(a.cnt==4)
		if(b.cnt!=4)
			return true;
		else
			return a.lim>b.lim;
	else if(b.cnt==4)
		return false;
	else if(a.cnt!=b.cnt)
		return false;
	else
		return a.lim>b.lim;
}

int ans;

inline void dfs(reg bool opt,State oldman,State roland,const Node& las){
	/*
	printf("opt=%d\n",opt);
	print(oldman),print(roland);
	printf("las=(%d,%d)\n",las.cnt,las.lim);
	puts("================");
	*/
	if(roland.sum()<=ans)
		return;
	if(oldman.empty()||roland.empty()){
		ans=max(ans,roland.sum()-oldman.sum());
		return;
	}
	if(opt){ //roland
		if(!las.cnt)
			for(reg int i=roland.sum();i>=1;--i)
				for(reg int j=(i>=5)?-2:0;j<13;++j){
					if(roland.check(Node(i,j))&&check(Node(i,j),las))
						return dfs(!opt,oldman,roland.chg(Node(i,j)),Node(i,j));
				}
		else{
			for(reg int i=3;i>=1;--i)
				for(reg int j=0;j<13;++j)
					if(roland.check(Node(i,j))&&check(Node(i,j),las))
						return dfs(!opt,oldman,roland.chg(Node(i,j)),Node(i,j));
			for(reg int i=roland.sum();i>=4;--i)
				for(reg int j=(i>=5)?-2:0;j<13;++j)
					if(roland.check(Node(i,j))&&check(Node(i,j),las))
						return dfs(!opt,oldman,roland.chg(Node(i,j)),Node(i,j));
			return dfs(!opt,oldman,roland,Node(0,0));
		}
	}
	else{ //oldman
		for(reg int i=oldman.sum();i>=1;--i)
			for(reg int j=(i>=5)?-2:0;j<13;++j)
				if(oldman.check(Node(i,j))&&check(Node(i,j),las))
					dfs(!opt,oldman.chg(Node(i,j)),roland,Node(i,j));
		dfs(!opt,oldman,roland,Node(0,0));
	}
	return;
}

bool ed;

int main(void){
	while(n=read(),m=read(),n|m){
		State oldman,roland;
		oldman._sum=n,roland._sum=m;
		for(reg int i=1;i<=n;++i){
			static char opt;
			do
				opt=getchar();
			while(!isalnum(opt));
			switch(opt){
				case '3' ... '9':++oldman.cnt[opt-'3'];break;
				case '1':++oldman.cnt[7];cin>>opt;break;
				case 'J':++oldman.cnt[8];break;
				case 'Q':++oldman.cnt[9];break;
				case 'K':++oldman.cnt[10];break;
				case 'A':++oldman.cnt[11];break;
				case '2':++oldman.cnt[12];break;
			}
		}
		for(reg int i=1;i<=m;++i){
			static char opt;
			do
				opt=getchar();
			while(!isalnum(opt));
			switch(opt){
				case '3' ... '9':++roland.cnt[opt-'3'];break;
				case '1':++roland.cnt[7];cin>>opt;break;
				case 'J':++roland.cnt[8];break;
				case 'Q':++roland.cnt[9];break;
				case 'K':++roland.cnt[10];break;
				case 'A':++roland.cnt[11];break;
				case '2':++roland.cnt[12];break;
			}
		}
		ans=-inf;
		dfs(0,oldman,roland,Node(0,0));
		if(ans>0)
			printf("Lose\n%d\n",ans);
		else
			printf("Win\n%d\n",-ans);
	}
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}