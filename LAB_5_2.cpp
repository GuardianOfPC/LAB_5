#include <fstream>
using namespace std;

struct Node {
	int K;   // Key
	Node* P; // Parent
	Node* L; // Left
	Node* R; // Right
};

class BinTreeSearch {
private:
	Node* root = NULL;
public:
	void insert(int value) {
		if (check_value(value))
			return;
		Node* new_el = new Node;
		new_el->K = value;
		new_el->P = NULL;
		new_el->L = NULL;
		new_el->R = Null;
		Node* current = root;
		while (current != NULL) {
			new_el->parent = current;
			if (new_el->K < current->K) {
				current = current->L;
			}
			else {
				current = current->R;
			}
		}
		if (new_el->parent == NULL) {
			root = new_el;
		}
		else {
			if (new_el->K < new_el->P->K) {
				new_el->P->L = new_el;
			}
			else {
				new_el->P->R = new_el;
			}
		}
	}

	void Delete(int value) {
		Node* del = search(value); // del -удаляемый элемент
		if (del == NULL) {
			return;
		}
		Node* prev; // предыдущий элемент
		Node* utility; // вспомогательный элемент
		if ((del->L == NULL) || (del->R == NULL)) {
			prev = del;
		}
		else {
			prev = next(value);
		}
		if (prev->L != NULL) {
			utility = prev->L;
		}
		else {
			utility = prev->R;
		}
		if (utility != NULL) {
			utility->P = prev->P;
		}
		if (prev->P == NULL) {
			root = utility;
		}
		else {
			if (prev = prev->P->L) {
				prev->P->L = utility;
			}
			else {
				prev->P->R = utility;
			}
		}
		if (prev != del) {
			del->K = prev->K;
		}
		delete prev;
	}

	Node* search(int value) {
			Node* current = root; // current - текущий элемент
			while (current != NULL && != current->K) {
				if (value < current->K) {
					current = current->L;
				}
				else {
					current = current->R;
				}
			}
			return current;
		}

	Node* next(int value) {
		Node* current = root;
		Node* successor = NULL;
		while (current != NULL) {
			if (current->K > value) {
				successor = current;
				current = current->L;
			}
			else {
				current = current->R;
			}
			return successor;
		}
	}
	
	Node* prev(int value) {
		Node* current = root;
		Node* prev = NULL;
		while (current != NULL) {
			if (current->K != NULL) {
				prev = current;
				current = current->R;
			}
			else {
				current = current->L;
			}
		}
		return prev;
	}

	bool check_value(int value) {
		return search(value) != NULL;
	}			
}

int main() {
	ifstream fin("bstsimple.in");
	ofstream fout("bstsimple.out");
	BinTreeSearch bin_tree;
	int V; // Value
	string cmd;
	while (fin >> cmd >> V) {
		if (cmd == "insert") {
			bin_tree.insert(V);
		}
		if (cmd == "delete") {
			bin_tree.Delete(V);
		}
		if (cmd == "exists") {
			if (bin_tree.exists(V)){
				fout << "true\n";
			}
			else {
				fout << "false"\n;
			}
		}
		if (cmd == "next") {
			Node* result = bin_tree.next(V);
			if (result == NULL) {
				fout << "none\n";
			}
			else {
				fout << result->K << "\n";
			}
		}
		if (cmd == "prev") {
			Node* result = bin_tree.prev(V);
			if (result == NULL) {
				fout << "none\n";
			}
			else {
				fout << result->K << "\n";
			}
		}
	}
	fin.close();
	fout.close();

	return 0;
}