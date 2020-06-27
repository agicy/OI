#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

int n,base;
int ans=-INF,pos=-INF;
vector<pair<int,int>/**/> T;
map<int,int> M;

inline void update(reg int x){
	if(abs(x)<abs(pos))
		pos=x;
	else if(abs(x)==abs(pos)&&x>pos)
		pos=x;
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static int opt,l,r,v;
		opt=read();
		switch(opt){
			case 1:{
				l=read(),r=read()+1,v=read();
				break;
			}
			case 2:{
				l=read(),r=l+1,v=read();
				break;
			}
			case 3:{
				l=read(),r=l+1,v=read();
				base^=v;
				break;
			}
			default:break;
		}
		M[l]^=v,M[r]^=v;
	}
	for(map<int,int>::iterator it=M.begin();it!=M.end();++it)
		T.push_back(make_pair(it->first,it->second));
	T.push_back(make_pair(-INF,0)),
	T.push_back(make_pair(INF,0));
	sort(T.begin(),T.end());
	reg int pre=base;
	for(reg int i=0,size=T.size();i<size-1;++i){
		pair<int,int> p=T[i];
		pre^=p.second;
		if(pre>ans){
			ans=pre,pos=p.first;
			update(T[i+1].first-1);
			if(p.first<=0&&0<=T[i+1].first-1)
				pos=0;
		}
		else if(pre==ans){
			update(p.first),update(T[i+1].first-1);
			if(p.first<=0&&0<=T[i+1].first-1)
				pos=0;
		}
	}
	printf("%d %d\n",ans,pos);
	return 0;
}