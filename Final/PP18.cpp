#include <iostream>
using namespace std;
// A node for storing the non-zero element in the sparse vector
struct nonZeroElement
{
	int index;						// The position index of the sparse vector element
	int value;						// The value of the sparse vector element
	nonZeroElement *next; // The link to the next node
	nonZeroElement *prev; // The link to the previous node
};
// Sparse vector with a linked list of non-zero elements
struct svector
{
	int size;
	// The number of elements (including the zeros) of a sparse vector,
	// not the number of non-zero elements
	nonZeroElement *head;
	// The head of the linked list with non-zero elements
};
// Insert a non-zero element into the sparse vector's linked list
void insertSparseVectorElement(svector &v, int index, int value)
{
	// // TO DO: ADD YOUR CODE HERE
	// // Create a new node
	// // 2 points in total: 0.5 each of the following 4 statements
	// nonZeroElement *newElement = new nonZeroElement;
	// newElement->index = index;
	// newElement->value = value;
	// newElement->next = newElement->prev = NULL;
	// // CASE 1: Empty list or insert in the begining of the list
	// // 2 points in total
	// if ((v.head == NULL) || (v.head->index > index)) // 0.5 points
	// {
	// 	newElement->next = v.head; // 0.5 points
	// 	if (v.head != NULL)				 // 0.5 points including the condition checking
	// 		v.head->prev = newElement;
	// 	v.head = newElement; // 0.5 points
	// }
	// else // CASE 2: Insert in the middle or the end of the list
	// {		 // ( 5 points in total )
	// 	// 2 points for finding the position
	// 	nonZeroElement *temp = v.head;
	// 	while ((temp->next != NULL) && (temp->index < index))
	// 		temp = temp->next;
	// 	// 3 points for updating the points correctly
	// 	if (temp->index < index) // Insert at the end
	// 	{
	// 		temp->next = newElement;
	// 		newElement->prev = temp;
	// 	}
	// 	else if (temp->index > index) // Insert between two nodes
	// 	{
	// 		newElement->next = temp;
	// 		newElement->prev = temp->prev;
	// 		temp->prev->next = newElement;
	// 		temp->prev = newElement;
	// 	}
	// }
	nonZeroElement *head = v.head;
	nonZeroElement *prev = nullptr;
	nonZeroElement *p = head;
	if (head == nullptr)
	{
		v.head = new nonZeroElement{index, value, nullptr, nullptr};
		return;
	}
	while (p != nullptr && p->index < index)
	{
		prev = p;
		p = p->next;
	}
	nonZeroElement *newElement = new nonZeroElement{index, value, p, prev};
	if (p != nullptr)
	{
		p->prev = newElement;
	}

	if (prev == nullptr)
	{
		v.head = newElement;
	}
	else
	{
		prev->next = newElement;
	}
}
// Print the sparse vector by printing the non-zero elements
// in the linked list and the omitted zero elements
void printSparseVector(const svector &v)
{
	// // TO DO: ADD YOUR CODE HERE
	// // 0.5 points for the "["
	// cout << "[";
	// // 4 points in total for printing the leading zeros, in-between zeros and
	// // the non-zero elements
	// nonZeroElement *temp = v.head;
	// int start = 0;
	// for (; temp != NULL; temp = temp->next) // 1 point
	// {
	// 	// Print the omitted zero elements: 1.5 points
	// 	int end = temp->index;
	// 	for (; start < end; start++)
	// 		cout << "0, ";
	// 	// Print the non-zero element
	// 	cout << temp->value;						// 1 point
	// 	if (temp->index < (v.size - 1)) // 0.5 points
	// 		cout << ", ";
	// 	start = end + 1;
	// }
	// // Print the omitted zero elements
	// // 2 points for the trailing zeros
	// int end = v.size;
	// for (; start < end; start++)
	// {
	// 	cout << "0";
	// 	if (start < (end - 1))
	// 		cout << ", ";
	// }
	// // 0.5 points for the following
	// cout << "]" << endl;
	cout << "[";
	for (int i = 0; i < v.size; i++)
	{
		nonZeroElement *p = v.head;
		if (p == nullptr)
		{
			if (i < v.size - 1)
			{
				cout << "0, ";
			}
			else
			{
				cout << "0";
			}
		}
		else
		{
			bool inList = false;
			while (p != nullptr)
			{
				if (p->index == i)
				{
					if (i < v.size - 1)
					{
						cout << p->value << ", ";
					}
					else
					{
						cout << p->value;
					}
					inList = true;
					p = p->next;
					break;
				}
				else
				{
					p = p->next;
				}
			}
			if (!inList)
			{
				if (i < v.size - 1)
				{
					cout << "0, ";
				}
				else
				{
					cout << "0";
				}
			}
		}
	}
	cout << "]" << endl;
}
int main()
{
	// Information of the non-zero elements
	int e[][2] = {{5, 10}, {4, 20}, {0, 15}, {9, 5}, {15, 110}};
	// Create and initialize a svector object
	svector sparseVector;
	sparseVector.size = 20;
	sparseVector.head = NULL;
	cout << "Zero Vector: " << endl;
	printSparseVector(sparseVector);
	// Insert the non-zero elements to the svector object
	for (int i = 0; i < (sizeof(e) / sizeof(e[0])); i++)
		insertSparseVectorElement(sparseVector, e[i][0], e[i][1]);
	// Print the svector object
	cout << "Vector: " << endl;
	printSparseVector(sparseVector);
	return 0;
}
