#include<cstdio>
#include<algorithm>
using std::sort;
#include<vector>
using std::vector;

const int MAXN=100+5;
const int MAXM=200+5;

int n,m;
int father[MAXN];
vector<int> son[MAXN];

int main(void){
	register int i,ans=0,cur=0;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;++i){
		static int x,y;
		scanf("%d%d",&x,&y);
		father[y]=x;
		son[x].push_back(y);
	}
	for(i=1;i<=n;++i)
		if(father[i]==0){
			printf("%d\n",i);
			break;
		}
	for(i=1;i<=n;++i)
		if(son[i].size()>ans)
			ans=son[i].size(),cur=i;
	printf("%d\n",cur);
	sort(son[cur].begin(),son[cur].end());
	for(i=0;i<son[cur].size();++i)
		printf("%d ",son[cur][i]);
	return 0;
}
