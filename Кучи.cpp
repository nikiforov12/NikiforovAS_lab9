
#include <iostream>
#include <list>
#include <string>
#include <conio.h>
using namespace std;

class Binomial_Heap {
	int data;
	int degree;
	Binomial_Heap *child;
	Binomial_Heap *sibling;
	Binomial_Heap *parent;
public:

	Binomial_Heap* creat(int key) {
		Binomial_Heap *temp = new Binomial_Heap;
		temp->data = key;
		temp->degree = NULL;
		temp->child = temp->parent = temp->sibling = NULL;
		return temp;
	}

	
	list<Binomial_Heap*> sort_degree(list<Binomial_Heap*> l1, list<Binomial_Heap*> l2) {
		list<Binomial_Heap*> _new;
		list<Binomial_Heap*>::iterator it = l1.begin();
		list<Binomial_Heap*>::iterator ot = l2.begin();
		while (it != l1.end() && ot != l2.end()) {
			if ((*it)->degree <= (*ot)->degree) {
				_new.push_back(*it);
				it++;
			}
			else {
				_new.push_back(*ot);
				ot++;
			}
		}
		while (it != l1.end()) {
			_new.push_back(*it);
			it++;
		}
		while (ot != l2.end()) {
			_new.push_back(*ot);
			ot++;
		}
		return _new;
	}

	Binomial_Heap* merge(Binomial_Heap *b1, Binomial_Heap *b2) {
		if (b1->data > b2->data) {
			Binomial_Heap *temp;
			temp = b1;
			b1 = b2;
			b2 = temp;
		}
		b2->parent = b1;
		b2->sibling = b1->child;
		b1->child = b2;
		b1->degree++;
		return b1;
	}

	list<Binomial_Heap*> invariant_2(list<Binomial_Heap*> heap) {
		if (heap.size() == 1) {
			return heap;
		}
		list<Binomial_Heap*> newheap;
		list<Binomial_Heap*>::iterator it1, it2, it3;
		it1 = it2 = it3 = heap.begin();
		if (heap.size() == 2) {
			//it2 = it1;
			it2++;
			it3 = heap.end();
		}
		else {
			it2++;
			it3 = it2;
			it3++;
		}
		while (it1 != heap.end()) {
			if (it2 == heap.end()) {
				it1++;
			}
			else if ((*it1)->degree < (*it2)->degree) {
				it1++;
				it2++;
				if (it3 != heap.end())
					it3++;
			}
			else if (it3 != heap.end() && (*it1)->degree == (*it2)->degree && (*it1)->degree == (*it3)->degree) {
				it1++;
				it2++;
				it3++;
			}
			else if ((*it1)->degree == (*it2)->degree) {
				*it1 = merge(*it1, *it2);
				it2 = heap.erase(it2);
				if (it3 != heap.end()) {
					it3++;
				}
			}
		}
		return heap;
	}

	list<Binomial_Heap*> insertInHeap(list<Binomial_Heap*> heap, Binomial_Heap *tree) {
		list<Binomial_Heap*> temp;
		temp.push_back(tree);
		temp = sort_degree(heap, temp);
		list<Binomial_Heap*> _temp = invariant_2(temp);
		return _temp;
	}

	list<Binomial_Heap*> insert(list<Binomial_Heap*> _head, int key) {
		Binomial_Heap *temp = creat(key);
		list<Binomial_Heap*> _temp = insertInHeap(_head, temp);
		return _temp;
	}

	list<Binomial_Heap*> removeMaxPriority(Binomial_Heap *tree) {
		list<Binomial_Heap*> heap;
		Binomial_Heap *temp = tree->child;
		Binomial_Heap *lo;
		while (temp) {
			lo = temp;
			temp = temp->sibling;
			lo->sibling = NULL;
			heap.push_front(lo);
		}
		return heap;
	}

	Binomial_Heap* getMaxPriority(list<Binomial_Heap*> heap) {
		list<Binomial_Heap*>::iterator it = heap.begin();
		Binomial_Heap *temp = *it;
		while (it != heap.end()) {
			if ((*it)->data < temp->data) {
				temp = *it;
			}
			it++;
		}
		return temp;
	}

	list<Binomial_Heap*> deleteMaxPriority(list<Binomial_Heap*> heap) {
		list<Binomial_Heap*> newheap, lo;
		Binomial_Heap *temp;
		temp = getMaxPriority(heap);
		list<Binomial_Heap*>::iterator it;
		it = heap.begin();
		while (it != heap.end()) {
			if (*it != temp) {
				newheap.push_back(*it);
			}
			it++;
		}
		lo = removeMaxPriority(temp);
		newheap = sort_degree(newheap, lo);
		list<Binomial_Heap*> _temp = invariant_2(newheap);
		return _temp;
	}

	void Print_Binomial_Heap(const string & probel, const Binomial_Heap* top, bool childs, bool viv, int l) {
		bool ghg = false;
		while (top != 0) {
			if (top != 0) {
				if (top->child != 0 || top->sibling != 0) {
					viv = true;
				}
				else {
					viv = false;
				}
				cout << probel;
				if (childs) {
					cout << "|----:" << top->data << endl;
				}
				else {
					if (l == 1) {
						cout << "------" << top->data << endl;
						l++;
						if (top->child == 0 && top->parent == 0) {
							ghg = true;
						}
					}
				}
				if (childs) {
					Print_Binomial_Heap(probel + "|     ", top->child, true, viv, l);
				}
				else {
					Print_Binomial_Heap(probel + "      ", top->child, true, viv, l);
				}
				top = top->sibling;
			}
		}
	}
};

int main() {
	setlocale(0, "");
	list<Binomial_Heap*> heap;
	Binomial_Heap tm;
	int num = 1;
	while (num != 0) {
		system("cls");
		cout << "Menu:\n1.Добавление в биномиальную кучу.\n2.Удаление минимального элемента.\n3.Вывод биномиального дерева.\n0-Выйти.\n";
		cin >> num;
		switch (num) {
		case 1:
			int val;
			char value[100];
			while (true) {
				system("cls");
				cout << "Введите значение (для выхода нажмите - (q)): ";
				cin >> value;
				if (strcmp(value, "q") == 0) {
					break;
				}
				val = atoi(value);
				heap = tm.insert(heap, val);
			}
			break;
		case 2:
			heap = tm.deleteMaxPriority(heap);
			break;
		case 3:
			system("cls");
			list<Binomial_Heap*>::iterator it;
			for (it = heap.begin(); it != heap.end(); it++) {
				tm.Print_Binomial_Heap("", *it, false, false, 1);
				cout << endl << endl << endl;
			}
			_getch();
			_getch();
			break;
		}

	}
	system("pause");
	return 0;
}