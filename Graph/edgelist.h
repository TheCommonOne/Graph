#include<iostream>

using namespace std;

template<class t>
class listData {
public:
	int vertex;
	t weight;
};

template<class dataType>
class ListNode {
public:
	dataType element;
	ListNode<dataType> *next;
	ListNode(const dataType& elemval, ListNode<dataType> *nextval = NULL) {
		element = elemval; next = nextval;
	}
	ListNode(ListNode<dataType> *nextval = NULL) {
		next = nextval;
	}
};

template<class dataType>
class EdgeList {
public:
	ListNode<dataType> *head;
	EdgeList() {
		head = new ListNode<dataType>();
	}
	void removeall() {
		ListNode<dataType> *tmp;
		while (head != NULL)
		{
			tmp = head;
			head = head->next;
			delete tmp;
		}
	}
	~EdgeList() {
		removeall();
	};
};
#pragma once
