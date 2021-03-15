#include <fstream>
using namespace std;

struct Node {
	int K;
	int L;
	int R;
};

int height(Node *bin_tree, int H) {
	if (H == -1) {
		return 0;
	}
	else {
		return max(height(bin_tree, bin_tree[H].L), height(bin_tree, bin_tree[H].R)) + 1;
	}
}

int main() {
	ifstream fin("height.in");
	ofstream fout("height.out");
	int N;
	fin >> N;
	if (N == 0) {
		fout << 0;
	}
	Node *bin_tree = new Node[N];
	for (int i = 0; i < N; i++) {
		fin >> bin_tree[i].K >> bin_tree[i].L >> bin_tree[i].R;
		bin_tree[i].R--;
		bin_tree[i].L--;
	}
	if (N != 0) {
		fout << height(bin_tree, 0) << endl;
	}
	fin.close();
	fout.close();
	return 0;
}