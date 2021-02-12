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

const int MAXK=1e5+5;
const int MAXN=1e5+5;

int k,n,m;
int a[MAXK],op[MAXN];
pair<int,int> eva[MAXK];
vector<pair<int,int>/**/> add[MAXK];
vector<pair<double,int>/**/> mul;
vector<int> ans;

inline bool cmp(reg int x,reg int y){
	return op[x]<op[y];
}

int main(void){
	k=read(),n=read(),m=read();
	for(reg int i=1;i<=k;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i){
		static int x,y;
		op[i]=read(),x=read(),y=read();
		switch(op[i]){
			case 1:{
				eva[x]=max(eva[x],make_pair(y,i));
				break;
			}
			case 2:{
				add[x].push_back(make_pair(y,i));
				break;
			}
			case 3:{
				mul.push_back(make_pair(y,i));
				break;
			}
		}
	}
	for(reg int i=1;i<=k;++i)
		if(eva[i].first>a[i])
			add[i].push_back(make_pair(eva[i].first-a[i],eva[i].second));
	for(reg int i=1;i<=k;++i){
		sort(add[i].begin(),add[i].end(),greater<pair<int,int>/**/>());
		reg ll num=a[i];
		for(vector<pair<int,int>/**/>::iterator it=add[i].begin();it!=add[i].end();++it){
			mul.emplace_back(1.0*(num+it->first)/num,it->second);
			num+=it->first;
		}
	}
	sort(mul.begin(),mul.end(),greater<pair<double,int>/**/>());
	m=min((int)mul.size(),m);
	printf("%d\n",m);
	for(reg int i=0;i<m;++i)
		ans.push_back(mul[i].second);
	sort(ans.begin(),ans.end(),cmp);
	for(reg int i=0,siz=ans.size();i<siz;++i)
		printf("%d%c",ans[i],i==siz-1?'\n':' ');
	return 0;
}