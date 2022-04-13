#include <iostream>
#include <vector>
#include <string>
using namespace std;
bool is_interleaving(string root1, string root2, string final_string) {
	bool c = false;
	if (final_string.size() == root1.size() && root1.size() == root2.size() && root2.size() == 0) return true;
	else if (final_string.size() == 0) return false;
	if (root1.size() > 0 && final_string[0] == root1[0]) {
		char firsst_element_tmp = root1[0];
		root1.erase(root1.begin());
		final_string.erase(final_string.begin());
		c = is_interleaving(root1, root2, final_string);
		root1.insert(root1.begin(), firsst_element_tmp);
		final_string.insert(final_string.begin(), firsst_element_tmp);
	}
	if (root2.size()>0 && final_string[0] == root2[0]) {
		root2.erase(root2.begin());
		final_string.erase(final_string.begin());
		if(c==false) c = is_interleaving(root1, root2, final_string);
	}
	return c;
}
int main() {
	string root1, root2, final_string;
	cin >> root1 >> root2 >> final_string;
	if (is_interleaving(root1, root2, final_string)) cout << "interleaving";
	else cout << "Not interleaving";

}