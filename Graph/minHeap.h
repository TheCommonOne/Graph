#include<iostream>

using namespace  std;

template<class dataType>
class minHeap {
public:
	dataType * heap_array;
	int current_size;
	int max_size;

	minHeap(const int mx_sz);
	~minHeap();
	void initiate();
	void buildHeap();

	bool isEmpty();
	bool isLeaf(int pos);

	int getLeft(int pos) const;	   		// ��������λ��
	int getRight(int pos) const;		// �����Һ���λ��
	int getParent(int pos) const;			// ���ظ����λ��
	bool Insert(const dataType& newNode);		// ����в�����Ԫ��newNode

	dataType& removeMin();			// �ӶѶ�ɾ����Сֵ
	bool remove(int pos, dataType& node); 		// ɾ�������±��Ԫ��

	void swap(int post_x, int post_y);
	void siftUp(int position);		 // ��position���Ͽ�ʼ������ʹ���г�Ϊ��
	void siftDown(int left);         	// ����ɸѡ������left��ʾ��ʼ����������±�

	//template<dataType>
	//friend ostream & operator << (ostream & out, minHeap<dataType>& mh);
};

template<class dataType>
minHeap<dataType>::minHeap(const int mx_sz) {
	if (mx_sz <= 0)return;
	current_size = 0;
	max_size = mx_sz;
	heap_array = new dataType[max_size];
}
template<class dataType>
minHeap<dataType>::~minHeap() {
	if (heap_array != NULL)
		delete[] heap_array;
}
template<class dataType>
void minHeap<dataType>::initiate() {
	int pos = getParent(current_size - 1);
	while (pos >= 0)
	{
		siftDown(pos);
		pos--;
	}
}
template<class dataType>
void minHeap<dataType>::buildHeap() {
	dataType temp;
	for (int i = 0; i < max_size; i++)
	{
		cout << "Input " << max_size << " Value" << endl;
		//cin >> temp;
		heap_array[i] = max_size - i - 1;
		this->current_size++;
	}
	initiate();
	cout << *this;
}

template<class dataType>
bool minHeap<dataType>::isEmpty() {
	return current_size == 0;
}
template<class dataType>
bool minHeap<dataType>::isLeaf(int pos) {
	return (pos < current_size) && (pos >= current_size / 2);
}
template<class dataType>
int minHeap<dataType>::getLeft(int pos) const {
	return 2 * pos + 1;
}

// ����в�����Ԫ��newNode
template<class dataType>// ��������λ��
int minHeap<dataType>::getRight(int pos) const {
	return 2 * pos + 2;
}
template<class dataType>// �����Һ���λ��
int minHeap<dataType>::getParent(int pos) const {
	return (pos - 1) / 2;
}
template<class dataType>// ���ظ����λ��
bool minHeap<dataType>::Insert(const dataType& newNode) {
	if (current_size == max_size)
	{
		cout << "MinHeap Full" << endl;
		return false;
	}
	heap_array[current_size] = newNode;
	current_size++;
	siftUp(current_size - 1);
	return true;
}

template<class dataType>
dataType& minHeap<dataType>::removeMin() {
	if (this->isEmpty())
	{
		cout << "Empty Min Heap" << endl;
		return heap_array[0];
	}
	dataType temp = heap_array[0];
	heap_array[0] = heap_array[current_size - 1];
	current_size--;
	siftDown(0);
	return temp;
}			// �ӶѶ�ɾ����Сֵ
template<class dataType>
bool minHeap<dataType>::remove(int pos, dataType& node) {
	if (this->isEmpty())
	{
		cout << "Empty Min Heap" << endl;
		return false;
	}
	if (pos>current_size || pos<0)
		return false;
	node = heap_array[pos];
	heap_array[pos] = heap_array[current_size - 1];
	if (heap_array[getParent(pos)] > heap_array[pos])
		siftUp(pos);
	else siftDown(pos);
	current_size--;
	return true;
} 		// ɾ�������±��Ԫ��
template<class dataType>
void minHeap<dataType>::swap(int post_x, int post_y) {
	dataType temp = heap_array[post_x];
	heap_array[post_x] = heap_array[post_y];
	heap_array[post_y] = temp;
}

template<class dataType>
void minHeap<dataType>::siftUp(int position) {
	dataType temp = heap_array[position];
	while ((position > 0) && (temp < heap_array[getParent(position)]))
	{
		heap_array[position] = heap_array[getParent(position)];
		position = getParent(position);
	}
	heap_array[position] = temp;
}
// ��position���Ͽ�ʼ������ʹ���г�Ϊ��
template<class dataType>
void minHeap<dataType>::siftDown(int left) {
	int up = left, below = getLeft(left);
	dataType temp = heap_array[left];
	while (below < current_size)
	{
		if ((below < current_size - 1) && (heap_array[below] > heap_array[below + 1]))
		{
			below++;
		}
		if (temp > heap_array[below])
		{
			heap_array[up] = heap_array[below];
			up = below;
			below = getLeft(up);
		}
		else  break;
	}
	heap_array[up] = temp;
}
// ����ɸѡ������left��ʾ��ʼ����������±�

template<class dataType>
ostream & operator << (ostream & out, minHeap<dataType>& mh) {
	for (int i = 0; i < mh.current_size; i++)
	{
		cout << mh.heap_array[i] << ' ';
	}
	return out;
}
#pragma once
