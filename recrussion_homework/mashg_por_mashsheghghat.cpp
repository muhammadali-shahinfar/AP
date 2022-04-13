#include <iostream>
#include <vector>
#include <string>
using namespace std;
long long pow(int base,int power){
	long long pow_tmp = 1;
	for(int i=0;i<power;i++){
		pow_tmp *=base;
	}
	return pow_tmp;
}
string mashgh_masheghghat(string s, int n) {
	vector <string> v;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '0') v.push_back("01");
		else v.push_back("10");
	}
	s = v[0];
	for (int i = 1; i < v.size(); i++) s += v[i];
	if (s.length() == pow(2, n)) {
		return s;
	}
	else {
		s = mashgh_masheghghat(s, n);
		return s;
	}
}
int main() {
	int n,k;
	string s = "0";
	cin >> n >> k;
	s = mashgh_masheghghat(s, n);
	cout << s[k-1];

}
