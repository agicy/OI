#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1000000+5;
const int MAXQ=100+5;

int n;
int cnt,cnta=1,cntb;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct Node{
	bool flag;//符号， true -> '+', false -> '-'
	int val;//绝对值
	inline Node(void){
		flag=false,val=0;
		return;
	}
	inline Node(reg bool a,reg int b){
		flag=a,val=b;
		return;
	}
};

Node a[MAXQ];

inline void Read(void){
	n=-1;//其实并不需要这一行
	a[1]=Node(true,0);//第一个是正的，绝对值不确定。
	static char ch;
	reg int i=1;
	cin>>ch;//吞掉开头的 '?'
	do{
		cin>>ch;//读入数学符号 '+', '-', '='
		if(ch=='+')
			++cnta,a[++i]=Node(true,0);//正
		else if(ch=='-')
			++cntb,a[++i]=Node(false,0);//负
		else if(ch=='='){
			cin>>n;
			break;
		}
		cin>>ch;
	}while(n==-1);
	cnt=cnta+cntb;//cnt -> Q
	return;
}

inline void Work(void){
	reg int Max=cnta*n-cntb,Min=-cntb*n+cnta;
	//Max 为最大，Min 为最小
	if(n<Min||n>Max){//不在值域之内
		puts("Impossible");
		return;
	}
	for(reg int i=1;i<=cnt;++i)
		a[i].val=a[i].flag?n:1;
	reg int temp=(Max-n)/(n-1),t2=(Max-n)%(n-1);
	//彻底更改 temp 个，小幅度修改第 temp+1 的值
	for(reg int i=1;i<=temp;++i)
		if(a[i].val==n)
			a[i].val=1;
		else
			a[i].val=n;
	if(a[temp+1].val==n)
		a[temp+1].val-=t2;
	if(a[temp+1].val==1)
		a[temp+1].val+=t2;
	//输出
	puts("Possible");
	for(reg int i=1;i<=cnt;++i)
		if(i==1)
			printf("%d",a[i].val);
		else
			printf(" %c %d",a[i].flag?'+':'-',a[i].val);
	printf(" = %d\n",n);
	return;
}
