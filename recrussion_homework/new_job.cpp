#include <iostream>
#include<vector>
#include<string>
using namespace std;
int abs(int n){
	if(n<0) return -n;
	else return n;
}
bool can_calculate(vector <int> stones, int mass) {
	if (stones.size() == 0) return 0;
	if (stones[0] == mass) return 1;
	int sum = 0;
	for (int i = 0; i < stones.size(); i++) {
		sum += stones[i];
	}
	if (sum < mass) return 0;
	vector <int> stones_without_first_element = stones;
	stones_without_first_element.erase(stones_without_first_element.begin());
	if (can_calculate(stones_without_first_element, abs(mass + stones[0]))) return 1;
	if (can_calculate(stones_without_first_element, abs(mass - stones[0]))) return 1;
	if (can_calculate(stones_without_first_element, mass));
}
int main() {
	int number, mass;
	cin >> number >> mass;
	vector <int> stones;
	for (int i = 0; i < number; i++) {
		int stone_tmp;
		cin >> stone_tmp;
		stones.push_back(stone_tmp);
	}
	if (can_calculate(stones, mass)) cout << "True";
	else cout << "False";
}
