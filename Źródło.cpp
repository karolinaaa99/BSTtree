#include <iostream>

using namespace std;

class Node 
{
private:
	int v; //key, data, dana przechowywana w wezle
	Node* left_node; //wskaznik na lewego syna
	Node* right_node; //wskaznik na prawego syna
	Node* parent_node; //wskaznik na ojca
public:
	Node(int v, Node* l, Node* r) { this->v = v; left_node = l; right_node = r; parent_node = NULL; } //konstruktor, tworzy wezel bez rodzica, czyli korzen
	Node(int v, Node* l, Node* r, Node* p) { this->v = v; left_node = l; right_node = r; parent_node = p; } //konstruktor, tworzy wezel z rodzicem, czyli nie-korzen
	int value(); //zwraca v
	Node* left(); //zwraca left_node
	Node* right(); //zwraca right_node
	Node* parent(); //zwraca parent_node
	void setValue(int v); //ustawia v
	void setLeft(Node* l); //ustawia left_node
	void setRight(Node* r); //ustawia right_node
	void setParent(Node* p); //ustawia parent_node
};

int Node::value() 
{
	return v;
}

Node* Node::left() 
{
	return left_node;
}

Node* Node::right() 
{
	return right_node;
}

Node* Node::parent() 
{
	return parent_node;
}

void Node::setValue(int v) 
{
	this->v = v;
}

void Node::setLeft(Node* l) 
{
	left_node = l;
}

void Node::setRight(Node* r) 
{
	right_node = r;
}

void Node::setParent(Node* p) 
{
	parent_node = p;
}

class Tree 
{
protected: //daje protected zamiast private tak, aby w klasie pochodnej te zmienne i metody byly widoczne
	Node* root; //wskazuje na korzen drzewa
	bool empty(Node* n);	//zwraca true, jesli wezel nie istnieje, false w przeciwnym razie
	void preorder(Node* n); //przejscie preorder
	void inorder(Node* n); //przejscie inorder
	void postorder(Node* n); //przejscie postorder
	int size(Node* n); //oblicza i zwraca liczbe wezlow w drzewie
	int height(Node* n); //oblicza i zwraca wysokosc drzewa, dlugosc najdluzszej sciezki w drzewie
	void clear(Node* n); //usuwa drzewo
public:
	Tree();			//tworzy puste drzewo
	Tree(Node* r);  //tworzy nowe drzewo
	bool empty();		//zwraca true, jesli drzewo jest puste, false w przeciwnym razie
	void preorder(); //wywolujemy protected preorder
	void inorder(); //wywolujemy protected inorder
	void postorder(); //wywolujemy protected postorder
	int size(); //wywolujemy protected size
	int height(); //wywolujemy protected height
	void clear(); //wywolujemy protected clear
};

bool Tree::empty(Node* n) 
{
	if (n == NULL) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void Tree::preorder(Node* n) //rekurencja
{
	if (!empty(n))
	{
		cout << n->value() << " "; //odwiedzamy wezel
		preorder(n->left()); //przechodzimy lewe poddrzewo
		preorder(n->right()); //przechodzimy prawe poddrzewo
	}
	else
	{
		return;
	}
}

void Tree::inorder(Node* n) //rekurencja
{
	if (!empty(n))
	{
		inorder(n->left()); //przechodzimy lewe poddrzewo
		cout << n->value() << " "; //odwiedzamy wezel
		inorder(n->right()); //przechodzimy prawe poddrzewo
	}
	else
	{
		return;
	}
}

void Tree::postorder(Node* n) //rekurencja
{
	if (!empty(n))
	{
		postorder(n->left()); //przechodzimy lewe poddrzewo
		postorder(n->right()); //przechodzimy prawe poddrzewo
		cout << n->value() << " "; //odwiedzamy wezel
	}
	else
	{
		return;
	}
}

int Tree::size(Node* n) //rekurencja
{
	
	/**sprawdzasz lewe poddrzewo, prawe poddrzewo, sumujesz i masz ilość węzłów u dzieci, następnie dodajesz obecny węzeł i masz ilość węzłów poddrzewa i tak od liści do korzenia**/
	int s = 0;
	if (n != NULL) 
	{
		s += size(n->left());
		s += size(n->right());
		return ++s;
	}
	else
		return 0;
}

int Tree::height(Node* n) //rekurencja
{
	/**Podobnie jest dla wysokości drzewa, tylko tutaj robisz dla każdego węzła jakby dwie możliwości, tj albo idziesz do lewego dziecka, albo do prawego
	   Tworzą się wtedy takie pojedyncze drogi od korzenia do liści**/
	int left = 0;
	int right = 0;
	if (!empty(n)) {
		left += height(n->left());
		right += height(n->right());

		left++;
		right++;
		if (left > right)
			return left;
		else
			return right;
	}
	else
		return 0;
}

void Tree::clear(Node* n) //rekurencja
{
	if (!empty(n->left()))
		clear(n->left());
	if (!empty(n->right()))
		clear(n->right());

	delete n;
}

Tree::Tree() 
{
	root = NULL;
}

Tree::Tree(Node* r) 
{
	root = r;
}

bool Tree::empty() 
{
	if (empty(root))
		return true;
	else
		return false;
}

void Tree::preorder() 
{
	preorder(root);
}

void Tree::inorder() 
{
	inorder(root);
}

void Tree::postorder() 
{
	postorder(root);
}

int Tree::size() 
{
	return size(root);
}

int Tree::height() 
{
	return height(root);
}

void Tree::clear() 
{
	clear(root);
	root = NULL;
}

class TreeBST :public Tree 
{
private:
	Node* minimum(Node* p); //wyznacza wezel o najmniejszej wartosci klucza
	Node* maximum(Node* p); //wyznacza wezel o najwiekszej wartosci klucza
public:
	TreeBST(); //konstruktor, tworzy puste drzewo bst
	TreeBST(Node* r); //konstruktor, tworzy drzewo bst
	void insert(int x); //dodaje wezel do drzewa bst z zachowaniem wlasnosci drzewa bst, dodajemy nowy wezel zawsze jako lisc
	Node* search(int x); //znajduje wezel o kluczy x
	Node* minimum(); //wywolujemy private minimum
	Node* maximum(); //wywolujemy private maximum
	Node* prec(Node* p); //predecessor - poprzednik, znajduje poprzednika wezla p
	Node* succ(Node* p); //successor - nastepnik, znajduje nastepnika wezla p
	void del(Node* p); //usuwa wezel p
};

Node* TreeBST::minimum(Node* p) 
{
	if (empty(p))
		return NULL;
	Node* currentNode = p;
	while (currentNode->left() != NULL) //wezel o najmniejszym kluczu to ostatni lewy syn
	{
		currentNode = currentNode->left();
	}
	return currentNode;
}

Node* TreeBST::maximum(Node* p) 
{
	if (empty(p))
		return NULL;
	Node* currentNode = p;
	while (currentNode->right() != NULL) //wezel o najwiekszym kluczu to ostatni prawy syn
	{
		currentNode = currentNode->right();
	}

	return currentNode;
}

TreeBST::TreeBST() 
{
	root = NULL;
}

TreeBST::TreeBST(Node* r) 
{
	root = r;
}

void TreeBST::insert(int x) 
{
	if (empty()) 
	{
		root = new Node(x, NULL, NULL, NULL);
		return;
	}
	bool left = true;
	Node* currentNode = root;
	Node* previousNode = NULL;
	while (currentNode != NULL) //przemieszczamy sie po drzewie do miejsca, w ktorym bedziemy mogli wstawic nowy wezel jako lisc
	{
		if (currentNode->value() >= x) 
		{
			previousNode = currentNode;
			currentNode = currentNode->left();
			left = true;
		}
		else 
		{
			previousNode = currentNode;
			currentNode = currentNode->right();
			left = false;
		}
	}

	currentNode = new Node(x, NULL, NULL, previousNode);
	if (left)
		previousNode->setLeft(currentNode);
	else
		previousNode->setRight(currentNode);
}

Node* TreeBST::search(int x) 
{
	Node* currentNode = root;

	while (currentNode->value() != x) 
	{
		if (currentNode->value() >= x)
			currentNode = currentNode->left();
		else
			currentNode = currentNode->right();

		if (empty(currentNode))
			return NULL;
	}
	return currentNode;
}

Node* TreeBST::minimum() 
{
	return minimum(root);
}

Node* TreeBST::maximum() 
{
	return maximum(root);
}

Node* TreeBST::prec(Node* p) //poprzednik wezla p to wezel najwiekszy, ale mniejszy od wezla p
{
	if (empty()) //jesli drzewo jest puste
		return NULL;

	if (minimum() == p) //jesli p jest minimum, to nie ma wezla o wartosci mniejszej od p
		return NULL;

	if (!empty(p->left())) //jesli wezel p posiada lewego syna, to jego poprzednikiem jest maksimum z jego lewego poddrzewa
		return maximum(p->left());
	else //jesli wezel p nie posiada lewego syna, to jego poprzednikim jest pierwszy rodzic, dla ktorego jest on w prawym poddrzewie
	{
		Node* precNode = p;
		while (precNode->parent()->right() != precNode) 
		{
			precNode = precNode->parent();
		}
		return precNode->parent();
	}
}

Node* TreeBST::succ(Node* p) //nastepnik wezla p to wezel najmniejszy, ale wiekszy od wezla p
{
	if (empty()) //jesli drzewo jest puste
		return NULL;

	if (maximum() == p) //jesli p jest maksimum, to nie ma wezla o wartosci wiekszej od p
		return NULL;

	if (!empty(p->right())) //jesli wezel p posiada prawego syna, to jego nastepnikiem jest minimum z jego prawego poddrzewa
		return minimum(p->right());
	else //jesli wezel p nie ma prawego syna, to jego nastepnikiem jest pierwszy rodzic, dla ktorego wezel p jest w lewym podrzewie
	{
		Node* succNode = p;
		while (succNode->parent()->left() != succNode) 
		{
			succNode = succNode->parent();
		}
		return succNode->parent();
	}
}

void TreeBST::del(Node* p) //usuwa wezel p
{
	if (empty()) //jesli drzewo jest puste
		return;
	if (empty(p)) //jesli wezel p jest pusty
		return;
	if ((empty(p->left())) && (empty(p->right()))) //jesli p jest lisciem, to poprostu usuwam go ze struktury drzewa
	{
		if (p == root)
		{
			root = NULL;
			return;
		}

		if (p->parent()->left() == p)
		{
			p->parent()->setLeft(NULL);
		}
		else // lub else if (p->parent()->right() == p)
		{
			p->parent()->setRight(NULL);
		}
		
		delete p;
		return;
	}
	//jesli p ma jednego syna: lewego lub prawego, to zastepujemy go tym synem, odpowiednio lewym lub prawym
	if ((!empty(p->left()))&&(empty(p->right()))) //jesli wezel p ma lewego syna
	{
		if (p == root)
		{
			root = p->left();
			return;
		}

		if (p->parent()->left() == p)
		{
			p->parent()->setLeft(p->left());
		}
		else 
		{
			p->parent()->setRight(p->left());
		}

		p->left()->setParent(p->parent());
		delete p;
		return;
	}
	if ((empty(p->left())) && (!empty(p->right()))) //jesli wezel p ma prawego syna
	{
		if (p == root)
		{
			root = p->right();
			return;
		}

		if (p->parent()->left() == p)
		{
			p->parent()->setLeft(p->right());
		}
		else
		{
			p->parent()->setRight(p->right());
		}
		p->right()->setParent(p->parent());
		delete p;
		return;
	}
	if (!empty(p->left()) && !empty(p->right())) //jesli wezel p ma obydwu synow to zastepuje go losowo jego poprzednikiem lub nastepnikiem
	{
		//Node* node1 = prec(p); //wystarczy, ze jedno znajde
		Node* succNode = succ(p); 
//		if (p == root)
//		{
			Node* succNodeLeft = succNode->left();
			Node* succNodeRight = succNode->right();
			if (!empty(succNodeLeft))
			{
				succNodeLeft->setParent(succNode->parent());
				if (succNode->parent()->left() == succNode)
				{
					succNode->parent()->setLeft(succNodeLeft);
				}
				else
				{
					succNode->parent()->setRight(succNodeLeft);
				}
			}
			else if(!empty(succNodeRight))
			{
				succNodeRight->setParent(succNode->parent());
				if (succNode->parent()->left() == succNode)
				{
					succNode->parent()->setLeft(succNodeRight);
				}
				else
				{
					succNode->parent()->setRight(succNodeRight);
				}
			}

			if (succNode->parent() != p)
			{
				succNode->setRight(p->right());
			}
			if (p == root) 
			{
				succNode->setParent(NULL);
				root = succNode;
			}
			else
			{
				succNode->setParent(p->parent());
				if (p->parent()->left() == p) {
					p->parent()->setLeft(succNode);
				}
				else {
					p->parent()->setRight(succNode);
				}
			}
			succNode->setLeft(p->left());
			
			delete p;

//		}
		
	}
}

int main() 
{

	/*
	Tree* t = new Tree(new Node(9, new Node(5, new Node(2, new Node(3, NULL, NULL), new Node(3, NULL, NULL)),
		new Node(7, NULL, new Node(8, NULL, NULL))), new Node(12, new Node(10, NULL, new Node(11, NULL, NULL)), NULL)));

	t->preorder();
	cout << endl;
	t->inorder();
	cout << endl;
	t->postorder();
	cout << endl;

	t->clear();
	t->preorder();
	cout << endl;
	*/

	/*
	TreeBST tBST;
	tBST.insert(4);
	tBST.insert(1);
	tBST.insert(5);
	tBST.insert(3);
	tBST.insert(2);
	tBST.preorder();
	*/
	TreeBST b;
	b.insert(4);
	b.insert(8);
	b.insert(2);
	b.insert(3);
	b.insert(5);
	b.insert(6);
	b.insert(1);
	b.insert(9);
	b.insert(7);
	b.insert(1);
	b.preorder();
	cout << endl;
	b.del(b.search(2));
	b.preorder();
	cout << endl;
	b.del(b.search(4));
	b.preorder();
	cout << endl;
	b.del(b.search(5));
	b.preorder();
	cout << endl;
//	cout << "Inorder: ";
//	tBST.inorder();
//	cout << endl;
//	Node* node = tBST.search(4);
//	tBST.del(node);
//	tBST.preorder();
//	cout << endl;
	/*
	cout << "Czy znaleziono wezel o kluczu 3: ";
	Node* node;
	node = tBST.search(3); 
	if (node != NULL) 
	{
		//cout << node->value() << endl;
		cout << "TAK";
	}
	else 
	{
		//cout << "Brak wezla" << endl;
		cout << "NIE";
	}
	cout << endl;

	cout << "Minimum: ";
	Node* node2;
	node2 = tBST.minimum();
	if(node2 != NULL)
	{
		cout << node2->value() << endl;
	}
	else 
	{
		 cout << "Brak minimum!" << endl;
	}
	cout << endl;

	cout << "Maksimum: ";
	Node* node3;
	node3 = tBST.maximum();
	if(node3 != NULL)
	{
		cout << node3->value() << endl;
	}
	else 
	{
		 cout << "Brak maksimum!" << endl;
	}
	cout << endl;
	
	cout << "Poprzednik 3: ";
	Node* node4;
	node4 = tBST.prec(node);
	if (node4 != NULL) 
	{
		cout << node4->value() << endl;
	}
	else 
	{
		cout << "Brak poprzednika!" << endl;
	}
	cout << endl;

	cout << "Nastepnik 3: ";
	Node* node5;
	node5 = tBST.succ(node);
	if (node5 != NULL) 
	{
		cout << node5->value() << endl;
	}
	else 
	{
		cout << "Brak nastepnika!" << endl;
	}
	cout << endl;

	cout << "Usuwam wezel o kluczu 2." << endl;
	Node* node6;
	node6 = tBST.search(2);
	tBST.del(node6);
	cout << "Inorder: ";
	tBST.inorder();
	cout << endl;
	*/

	/**cout << "Usuwam wezel o kluczu 1." << endl;
	Node* node7;
	node7 = tBST.search(1);
	tBST.del(node7);
	cout << "Inorder: ";
	tBST.inorder();
	cout << endl;

	cout << "Usuwam wezel o kluczu 5." << endl;
	Node* node8;
	node8 = tBST.search(5);
	tBST.del(node8);
	cout << "Inorder: ";
	tBST.inorder();
	cout << endl;**/

	return 0;
}