#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned short us;

const int MAXN=100000+5;
const int MAXM=100000+5;
const int MAXS=3000000+5;
const int MAXT=5000000+5;
const int MAXSIZE=MAXS;

int n,m;
vector<us> empty;

struct Trie{
	int tot;
	int ch[MAXSIZE*3][3];
	vector<us> end[MAXSIZE*3];
	inline void Init(void){
		tot=0;
		return;
	}
	inline void insert(int x,reg char str[]){
		reg int ID=0,p;
		for(reg int i=0;str[i];++i){
			p=str[i]-'a';
			if(ch[ID][p]==0)
				ch[ID][p]=++tot;
			ID=ch[ID][p];
			end[ID].push_back(x);
			//printf("end[%d]=:\n",ID);
			//Print(end[ID]);
		}
		return;
	}
	inline vector<us> query(reg char str[]){
		reg int ID=0,p;
		for(reg int i=0;str[i];++i){
			p=str[i]-'a';
			if(!ch[ID][p])
				return empty;
			ID=ch[ID][p];
		}
		return end[ID];
	}
};

Trie T;
char str[MAXT];

int main(void){
	empty.clear();
	scanf("%d%d",&n,&m);
	T.Init();
	for(reg int i=1;i<=n;++i){
		scanf("%s",str);
		T.insert(i,str);
	}
	vector<us> res,temp;
	for(reg int i=1;i<=m;++i){
		scanf("%s",str);
		//printf("str=%s\n",str);
		res.clear();
		temp=T.query(str);
		res.push_back(0);
		for(reg int j=0;j<(int)temp.size();++j)
			res.push_back(temp[j]);
		res.push_back(n+1);
		reg int ans=0;
		for(reg int i=0;i<(int)res.size()-1;++i)
			ans=max((int)ans,(int)res[i+1]-res[i]-1);
		//printf("res=\n");
		//Print(res);
		printf("%d\n",ans);
	}
	return 0;
}
