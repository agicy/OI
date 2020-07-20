#include<stdio.h>
#include<string.h>
#include<algorithm>
using std::sort;
#define max(a,b)	( (a) > (b) ? (a) : (b) )

struct Node{
	int a,b;
	void Read(void){
		scanf("%d%d",&this->a,&this->b);
		return;
	}
	bool operator<(Node &a)const{
		return this->a*this->b<a.a*a.b;
	}
};

int n;
int now[20010],sum[20010],ans[20010],add[20010];
Node p[1001];

void multiply(int);
void divide(int);
bool compare(void);


int main(void){
	register int i;
	scanf("%d",&n);
	for(i=0;i<=n;i++)
		p[i].Read();
	sort(p+1,p+n+1);
	ans[0]=1,ans[1]=1;
	for(i=1;i<=n;i++) {
		multiply(p[i-1].a),divide(p[i].b);
		if(compare())
			memcpy(sum,add,sizeof(add));
	}
	for(i=sum[0];i>=1;i--)
		printf("%d",sum[i]);
	return 0;
}

void multiply(int x){
	register int i;
	memset(add,0,sizeof(add));
	for(i=1;i<=ans[0];i++){
		ans[i]*=x;
		if(add[i]>=10)
			add[i+1]+=ans[i]/10,ans[i]%=10;
	}
	for(i=1;i<=ans[0]+4;i++){
		ans[i]+=add[i];
		if(ans[i]>=10)
			ans[i+1]+=ans[i]/10,ans[i]%=10;
		if(ans[i])
			ans[0]=max(ans[0],i);
	}
	return;
}

void divide(int x){
	memset(add,0,sizeof(add));
	register int i,q=0;
	for(i=ans[0];i>=1;i--){
		q=q*10+ans[i],add[i]=q/x;
		if(add[0]==0&&add[i])
			add[0]=i;
		q%=x;
	}
	return;
}

bool compare(void){
	register int i;
	if(!(sum[0]^add[0]))
		for(i=add[0];i>=1;i--)
			if(add[i]>sum[i])
				return true;
			else if(add[i]<sum[i])
				return false;
			else
				continue;
	else
		return add[0]>sum[0];
}
