#include<bits/stdc++.h>
using namespace std;

#define MAX_LENGTH 20005
struct BigNumber{
	int len,s[MAX_LENGTH];
	bool sign;
	
	BigNumber(void);
	BigNumber(const char*);
	BigNumber(int);
	~BigNumber(void);
	void clean(void);
	string toStr(void)const;
	friend istream& operator>>(istream&,BigNumber&);
	friend ostream& operator<<(ostream&,BigNumber&);
	BigNumber operator=(const char*);
	BigNumber operator=(int);
	BigNumber operator=(const string);
	bool operator>(const BigNumber&)const;
	bool operator>=(const BigNumber&)const;
	bool operator<(const BigNumber&)const;
	bool operator<=(const BigNumber&)const;
	bool operator==(const BigNumber&)const;
	bool operator!=(const BigNumber&)const;
	BigNumber operator+(const BigNumber&)const;
	BigNumber operator++(void);
	BigNumber operator++(int);
	BigNumber operator+=(const BigNumber&);
	BigNumber operator-(const BigNumber &) const;
	BigNumber operator--(void);
	BigNumber operator--(int);
	BigNumber operator-=(const BigNumber&);
	BigNumber operator*(const BigNumber &)const;
	BigNumber operator*(const int num)const;
	BigNumber operator*=(const BigNumber&);
	BigNumber operator/(const BigNumber&)const;
	BigNumber operator/=(const BigNumber&);
	BigNumber operator%(const BigNumber&)const;
	BigNumber factorial(void)const;
	BigNumber sqrt(void)const;
	BigNumber pow(const BigNumber&)const;
};
BigNumber::BigNumber(void){
	memset(s, 0, sizeof(s));
	len = 1;
	sign = 1;
}
BigNumber::BigNumber(const char*num){
	*this = num;
}
BigNumber::BigNumber(int num){
	*this = num;
}
string BigNumber::toStr(void)const{
	string res;
	res = "";
	for (int i = 0; i < len; i++)
		res = (char)(s[i] + '0') + res;
	if (res == "")
		res = "0";
	if (!sign&&res != "0")
		res = "-" + res;
	return res;
}
istream &operator>>(istream &in,BigNumber&num){
	string str;
	in>>str;
	num=str;
	return in;
}
ostream &operator<<(ostream &out,BigNumber&num){
	out<<num.toStr();
	return out;
}
BigNumber BigNumber::operator=(const char*num){
	memset(s, 0, sizeof(s));
	char a[MAX_LENGTH] = "";
	if (num[0] != '-')
		strcpy(a, num);
	else
		for (int i = 1,len=strlen(num); i < len; i++)
			a[i - 1] = num[i];
	sign = !(num[0] == '-');
	len = strlen(a);
	for (int i = 0; i <len; i++)
		s[i] = a[len - i - 1] - 48;
	return *this;
}
BigNumber BigNumber::operator=(int num){
	char temp[MAX_LENGTH];
	sprintf(temp, "%d", num);
	*this = temp;
	return *this;
}
BigNumber BigNumber::operator=(const string num){
	const char *tmp;
	tmp = num.c_str();
	*this = tmp;
	return *this;
}
bool BigNumber::operator<(const BigNumber&num)const{
	if (sign^num.sign)
		return num.sign;
	if (len != num.len)
		return len < num.len;
	for (int i = len - 1; i >= 0; i--)
		if (s[i] != num.s[i])
			return sign ? (s[i] < num.s[i]) : (!(s[i] < num.s[i]));
	return !sign;
}
bool BigNumber::operator>(const BigNumber&num)const{
	return num < *this;
}
bool BigNumber::operator<=(const BigNumber&num)const{
	return !(*this>num);
}
bool BigNumber::operator>=(const BigNumber&num)const{
	return !(*this<num);
}
bool BigNumber::operator!=(const BigNumber&num)const{
	return *this > num || *this < num;
}
bool BigNumber::operator==(const BigNumber&num)const{
	return !(num != *this);
}
BigNumber BigNumber::operator+(const BigNumber &num)const{
	if (sign^num.sign) {
		BigNumber tmp = sign ? num : *this;
		tmp.sign = 1;
		return sign ? *this - tmp : num - tmp;
	}
	BigNumber result;
	result.len = 0;
	int temp = 0;
	for (int i = 0; temp || i < (max(len, num.len)); i++) {
		int t = s[i] + num.s[i] + temp;
		result.s[result.len++] = t % 10;
		temp = t / 10;
	}
	result.sign = sign;
	return result;
}
BigNumber BigNumber::operator++(void){
	*this = *this + 1;
	return *this;
}
BigNumber BigNumber::operator++(int){
	BigNumber old = *this;
	++(*this);
	return old;
}
BigNumber BigNumber::operator+=(const BigNumber &num){
	*this = *this + num;
	return *this;
}
BigNumber BigNumber::operator-(const BigNumber &num) const{
	BigNumber b=num,a=*this;
	if (!num.sign && !sign) {
		b.sign=1;
		a.sign=1;
		return b-a;
	}
	if (!b.sign) {
		b.sign=1;
		return a+b;
	}
	if (!a.sign) {
		a.sign=1;
		b=BigNumber(0)-(a+b);
		return b;
	}
	if (a<b) {
		BigNumber c=(b-a);
		c.sign=false;
		return c;
	}
	BigNumber result;
	result.len = 0;
	for (int i = 0, g = 0; i < a.len; i++) {
		int x = a.s[i] - g;
		if (i < b.len) x -= b.s[i];
		if (x >= 0) g = 0;
		else {
			g = 1;
			x += 10;
		}
		result.s[result.len++] = x;
	}
	result.clean();
	return result;
}
BigNumber BigNumber::operator*(const BigNumber &num)const{
	BigNumber result;
	result.len = len + num.len;
 
	for (int i = 0; i < len; i++)
		for (int j = 0; j < num.len; j++)
			result.s[i + j] += s[i] * num.s[j];
 
	for (int i = 0; i < result.len; i++) {
		result.s[i + 1] += result.s[i] / 10;
		result.s[i] %= 10;
	}
	result.clean();
	result.sign = !(sign^num.sign);
	return result;
}
BigNumber BigNumber::operator*(const int num)const{
	BigNumber x = num;
	BigNumber z = *this;
	return x*z;
}
BigNumber BigNumber::operator/(const BigNumber&num)const{
	BigNumber ans;
	ans.len = len - num.len + 1;
	if (ans.len < 0) {
		ans.len = 1;
		return ans;
	}
 
	BigNumber divisor = *this, divid = num;
	divisor.sign = divid.sign = 1;
	int k = ans.len - 1;
	int j = len - 1;
	while (k >= 0) {
		while (divisor.s[j] == 0) j--;
		if (k > j) k = j;
		char z[MAX_LENGTH];
		memset(z, 0, sizeof(z));
		for (int i = j; i >= k; i--)
			z[j - i] = divisor.s[i] + '0';
		BigNumber dividend = z;
		if (dividend < divid) {
			k--;
			continue;
		}
		int key = 0;
		while (divid*key <= dividend) key++;
		key--;
		ans.s[k] = key;
		BigNumber temp = divid*key;
		for (int i = 0; i < k; i++)
			temp = temp * 10;
		divisor = divisor - temp;
		k--;
	}
	ans.clean();
	ans.sign = !(sign^num.sign);
	return ans;
}
BigNumber BigNumber::operator/=(const BigNumber&num){
	*this = *this / num;
	return *this;
}
void BigNumber::clean(void){
	if (len == 0) len++;
	while (len > 1 && s[len - 1] == '\0')
		len--;
}
BigNumber::~BigNumber(void){
}

#define reg register
typedef long long ll;
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

inline BigNumber fac(reg ll x){
	BigNumber res=1;
	for(reg int i=2;i<=x;++i)
		res=res*i;
	return res;
}

inline BigNumber C(reg ll n,reg ll m){
	return fac(n)/(fac(m)*fac(n-m));
}

int n;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read();
	return;
}

inline void Work(void){
	BigNumber ans=C(2*n,n)/(n+1);
	cout<<ans<<endl;
	return;
}
