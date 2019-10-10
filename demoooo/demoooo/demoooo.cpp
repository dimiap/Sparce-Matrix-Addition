#include <iostream>;
#include<iomanip>;
#include <string>;

using namespace std;


class NodeType { //to create an object of the node in the linked list
public:
	int info; //store the value of the node
	int column; //store the index of the column of the node
	NodeType *next; //pointer that shows the next node and creates a linked list 
public: //initialize the previous values
	NodeType() {
		info = 0;
		column = 0;
		next = NULL;
	}
};


class LinkedList { //creating the linked list of nodes
public:
	NodeType * head; //stores the location of the first node of the linked list
	NodeType * tail; //stores the location of the last node of the linked list

public:
	LinkedList();  //calling the contructor of the linked list
	~LinkedList(); //calling the destructor of the linked list
	void insertAtBeginning(int column, int value);
	void insertAtEnd(int column, int value);
	void insertItemAt(int column, int value);
	void insertRow(NodeType *other);
};


LinkedList::LinkedList() {  //contructor of the linked list, we initialize the values of the beggining and ending of the nodes
	head = NULL;
	tail = NULL;
}
//destructor of the linked list, to clean the objects of the nodes of the linked list from the heap memory
LinkedList::~LinkedList() { 
	NodeType * current = head; //the location of the current node is equal to the head node
	while (current != NULL) {  //while the current node isnt null
		current = current->next; //the current node is the next node
		delete head;//we delete the head node
		head = current; //the head node now is the current node 
		//this is run up until the current node is null so that all the nodes are deleted 
	}
	head = NULL; //initialize the head and tail nodes
	tail = NULL;
}
//function to create a new node and to store its column and value at the beginning of the linked list
void LinkedList::insertAtBeginning(int column, int value) {
	NodeType * newNode = new NodeType;
	newNode->info = value;
	newNode->column = column;

	//checking if the linked list is empty, if it is the head node is equal to the tail node so they are equal to the new node that we created
	if (head == NULL) {
		head = tail = newNode;
	}
	//if the linked list isnt empty the new node is the head node
	else {
		newNode->next = head;
		head = newNode;
	}
}
//function to create a new node and to store its column and value at the end of the linked list
void LinkedList::insertAtEnd(int column, int value) {
	NodeType * newNode = new NodeType;
	newNode->column = column;
	newNode->info = value;
	//checking if the linked list is empty, if it is the head node is equal to the tail node so they are equal to the new node that we created
	if (head == NULL)
		head = tail = newNode;
	//if the linked list isnt empty the new node is the tail node
	else {
		tail->next = newNode;
		tail = newNode;
	}
}
//function to create a new node and to store its column and value in the linked list (not at the beginning or at the end)
void LinkedList::insertItemAt(int column, int value) {
	//checking if the linked list is empty and if the column of the first node is bigger than the column of the new node
	//if its true then we call the function insertAtBeginning to store the new node as the head node of the linked list
	if (head == NULL || head->column > column) {
		insertAtBeginning(column, value);
	}
	//checking if the column of the new node is bigger than the column of the tail node
	//if its true then we call the function insertAtEnd to store the new node as the tail node of the linked list
	else if (tail->column < column) {
		insertAtEnd(column, value);

	}
	//if the column of the new node is at the middle of the linked list (middle= not at the head nor at the tail) we will check the location of the pointer of the new node
	else {
		//prevNode to store the head node
		NodeType * prevNode = head;
		//iteration until the value of the current column is smaller than the value of the current column of the node added by the user
		while (prevNode->column < column && prevNode != NULL) {
			//checking if the value of the column of the next node is bigger than the value of the column of the node added by the user
			//if its true then the iteration is complete 
			if (prevNode->next->column > column)
				break;
			prevNode = prevNode->next;
		}
		//if the value of the column of the node is equal to the value of the column of the node that was added by the user then we change the value of the info variable
		if (prevNode->column == column) {
			prevNode->info = value;
		}
		//else the value of the column of the node that was added by the user is after the value of the node
		else {
			NodeType * newNode = new NodeType;
			newNode->info = value;
			newNode->column = column;
			newNode->next = prevNode->next;
			prevNode->next = newNode;
		}

	}
}
//to insert the value of the row of the table to the value of the row of the other table
void LinkedList::insertRow(NodeType *other) {
	//iteration of the nodes in another linked list creating a copy of the other nodes
	while (other != NULL) {
		insertAtEnd(other->column, other->info);
		other = other->next;
	}
}

class SM {
public:
	LinkedList *linkedList;
	int n, m;

public:
	SM(int rows, int columns);
	~SM();
	void readElements();
	void printMatrix();
	void addSM(SM &other);
};

SM::SM(int rows, int columns) {
	n = rows;
	m = columns;
	linkedList = new LinkedList[n];
}

SM::~SM() {
	delete[] linkedList;
}

void SM::readElements() {
	//initialize of the linked list
	//we create the locations of the values that arent 0
	//we insert those locations using the format: row,column,value
	//to end the insertion we put 0 0 0.
	cout << "Please follow the sequence of element when enter the data for the matrix. " << endl;
	cout << "The sequence is as follow : \nrow >> column >> value " << endl;
	cout << "*Using a space or enter to separate the elements." << endl;
	cout << "*Enter 0 0 0 to finish.\n" << endl;

	int row = 1, column = 1, value = 1;
	int count = 1;
	do {
		cout << "Data (" << count << ") >> ";
		cin >> row;
		cin >> column;
		cin >> value;
		//if the user inserts 0 0 0 that is to end the insertion, we end the iteration
		if (row == 0 && column == 0 && value == 0)
			break;
		//if the value that was added by the user for the row of the table is bigger than the value of the row then we will get an error message 
		if (row >= n) {
			cout << "\nInvalid data found!\nThe maximum number of row is " << n << "! Please enter a valid number of row!\n" << endl;
		}
		//if the value that was added by the user for the column of the table is bigger than the value of the column then we will get an error message 
		else if (column >= m) {
			cout << "\nInvalid data found!\nThe maximum number of column is " << m << "! Please enter a valid number of column!\n" << endl;
		}
		//else put the values at the linked list
		else {
			count++;
			linkedList[row].insertItemAt(column, value);
		}

	} while ((row != 0 || column != 0 || value != 0));

	cout << endl;
}

void SM::printMatrix() {
	//iteration for the rows of the table
	for (int i = 0; i < n; i++) {
		cout << setw(7);
		NodeType *current = linkedList[i].head;
		//iteration for the columns of the table
		for (int j = 0; j < m; j++) {
			//checks if the linked list is empty, if it isnt empty then checks the nodes
			if (current != NULL) {
				//checks if the value of column of the node is equal to the value of  the column of the current node, if it is then we will get the info of the node in the table
				if (current->column == j) {
					cout << current->info << setw(7);
					current = current->next;
				}
				//otherwise we will get 0 
				else
					cout << "0" << setw(7);
			}
			//if the linked list is empty, it will print 0
			else {
				cout << "0" << setw(7);
			}
		}
		cout << endl;
	}
}

void SM::addSM(SM &matrixB) {
	//iteration for the rows of the table
	for (int i = 0; i < n; i++) {
		NodeType *ACurrent = NULL;
		//ACurrent pointer used for browsing at the linked list of the table A
		//if the row of the second table is empty then go to the next row
		if (matrixB.linkedList[i].head != NULL) {
			//initialize of BCurrent to point at the first node of the row of the linked list of table B 
			NodeType *BCurrent = matrixB.linkedList[i].head;
			//BCurrent pointer used for browsing at the linked list of the table B
			//iteration to all the nodes of table B for the row 
			while (BCurrent != NULL) {
				//if the first row of the first table is not empty we add the rows of the two tables together
				if (linkedList[i].head != NULL) {
					//if ACurrent isnt pointing anywhere then point to the head of the row of table A
					if (ACurrent == NULL) {
						ACurrent = linkedList[i].head;
					}
					//if the value of the column of the head node of table A is bigger than the value of the column that is pointed by the BCurrent
					//then we add the node of BCurrent to the beginning of the linked list of table A
					if (linkedList[i].head->column > BCurrent->column)
						linkedList[i].insertAtBeginning(BCurrent->column, BCurrent->info);
					//if the value of the tail node of the column of table of table A is smaller than the value of the column that is poinred by BCurrent
					//insert the node that BCurrent at the tail of the linked list of table A
					else if (linkedList[i].tail->column < BCurrent->column)
						linkedList[i].insertAtEnd(BCurrent->column, BCurrent->info);

					else {
						//iteration until the value of the column that ACurrent is pointing at is smaller than the value of the column that is pointed by BCurrent
						//and until ACurrent isnt equal to null so that there are nodes at the linked list
						while (ACurrent->column < BCurrent->column && ACurrent != NULL) {
							//checks if the pointer of the next node of the column of table A is bigger than the pointer of the column of table B
							if (ACurrent->next->column > BCurrent->column)
								break;
							ACurrent = ACurrent->next;
						}
						//if the column that ACurrent is pointing at is equal to to column that BCurrent is pointing at then we add the values 
						if (ACurrent->column == BCurrent->column) {
							ACurrent->info = BCurrent->info + ACurrent->info;
						}
						//otherwise we have addition of the new nodes after ACurrent
						else {
							NodeType * newNode = new NodeType;
							newNode->column = BCurrent->column;
							newNode->info = BCurrent->info;
							newNode->next = ACurrent->next;
							ACurrent->next = newNode;
						}
					}
				}
				//insert the whole row that BCurrent points at inside the row of table A
				//we stop the iteration and move to the next row
				else {
					linkedList[i].insertRow(BCurrent);
					break;
				}
				//if BCurrent has next node then move to the next node
				if (BCurrent->next != NULL)
					BCurrent = BCurrent->next;
				//else stop the iteration and move to the next row
				else
					break;
			}
		}
	}
}


int main() {
	int n, m;

	do {
		//user inserts the dimensions of the table
		cout << "Please enter the number of row(s) and column(s) for the matrix " << endl;
		cout << "Row(s) >> ";
		cin >> n;
		cout << "Column(s) >> ";
		cin >> m;
		cout << "\n" << endl;
		//checking if the dimensions are false
		if (n <= 0 || m <= 0)
			cout << "The number of row and column must be more than zero!\n" << endl;;
	} while (n <= 0 || m <= 0);
	//call the function SM for the both table
	SM sm = SM(n, m);
	SM sm2 = SM(n, m);
	//print the first and the second tables
	cout << "First Matrix:" << endl;
	sm.readElements();

	cout << "Second Matrix:" << endl;
	sm2.readElements();
	//print the tables with 0 
	cout << "First Matrix:" << endl;
	sm.printMatrix();
	cout << endl;
	cout << "Second Matrix:" << endl;
	sm2.printMatrix();
	cout << endl;
	//print the sum of the tables as a table not as a list
	sm.addSM(sm2);
	cout << "After Sum:" << endl;
	sm.printMatrix();
	cout << endl;
	system("PAUSE");
	return 0;
}
