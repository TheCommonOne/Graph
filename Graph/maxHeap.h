#include<iostream>

using namespace  std;

template<class dataType>
class maxHeap {
public:
	dataType * heap_array;
	int current_size;
	int max_size;
	maxHeap(const int mx_sz);
	~maxHeap();
	void initiate();
	void buildHeap();

	bool isEmpty();
	bool isLeaf(int pos);

	int getLeft(int pos) const;	   		// ��������λ��
	int getRight(int pos) const;		// �����Һ���λ��
	int getParent(int pos) const;			// ���ظ����λ��
	bool Insert(const dataType& newNode);		// ����в�����Ԫ��newNode

	dataType& removeMax();			// �ӶѶ�ɾ����Сֵ
	bool remove(int pos, dataType& node); 		// ɾ�������±��Ԫ��

	void swap(int post_x, int post_y);
	void siftUp(int position);		 // ��position���Ͽ�ʼ������ʹ���г�Ϊ��
	void siftDown(int left);         	// ����ɸѡ������left��ʾ��ʼ����������±�

	template<dataType>
	friend ostream& operator <<(ostream& out, maxHeap<dataType>& mh);
};

template<class dataType>
maxHeap<dataType>::maxHeap(const int mx_sz) {
	if (mx_sz <= 0)
	{
		heap_array = NULL; current_size = max_size = 0;
		return;
	}
	current_size = 0;
	max_size = mx_sz;
	heap_array = new dataType[mx_sz];
	buildHeap();
}
template<class dataType>
maxHeap<dataType>::~maxHeap() {
	if (heap_array != NULL)
	{
		delete[] heap_array;
	}
}
template<class dataType>
void maxHeap<dataType>::initiate() {
	int pos = getParent(current_size - 1);
	while (pos >= 0)
	{
		siftDown(pos);
		pos--;
	}
}
template<class dataType>
void maxHeap<dataType>::buildHeap() {
	dataType temp;
	for (int i = 0; i < max_size; i++)
	{
		cout << "Input " << max_size << " Value" << endl;
		//cin >> temp;
		heap_array[i] = i;
		this->current_size++;
	}
	initiate();
}

template<class dataType>
bool maxHeap<dataType>::isEmpty() {
	return current_size == 0;
}
template<class dataType>
bool maxHeap<dataType>::isLeaf(int pos) {
	return (pos < current_size) && (pos >= current_size / 2);
}
template<class dataType>
int maxHeap<dataType>::getLeft(int pos) const {
	return 2 * pos + 1;
}

template<class dataType>// ��������λ��
int maxHeap<dataType>::getRight(int pos) const {
	return 2 * pos + 2;
}
template<class dataType>// �����Һ���λ��
int maxHeap<dataType>::getParent(int pos) const {
	return (pos - 1) / 2;
}
template<class dataType>// ���ظ����λ��
bool maxHeap<dataType>::Insert(const dataType& newNode) {
	if (current_size == max_size)
	{
		cout << "Max Heap Full" << endl;
		return false;
	}
	if (pos>current_size || pos<0)
		return false;
	heap_array[current_size] = newNode;
	current_size++;
	siftUp(current_size - 1);
	return true;
}
// ����в�����Ԫ��newNode
template<class dataType>
dataType& maxHeap<dataType>::removeMax() {
	if (this->isEmpty())
	{
		cout << "Empty Max Heap" << endl;
		return heap_array[0];
	}
	dataType temp = heap_array[0];
	if (current_size == 0) {
		cout << "Can't Delete";		// ����RemoveMin֮ǰ����Ҫ�ж϶ѷǿ�
		exit(1);
	}
	else {
		swap(0, --current_size);	                 // �����Ѷ������һ��Ԫ��
		if (current_size>1)        siftDown(0);          // �ӶѶ���ʼɸѡ
		return temp;
	}

}			// �ӶѶ�ɾ�����ֵ
template<class dataType>
bool maxHeap<dataType>::remove(int pos, dataType& node) {
	if (this->isEmpty())
	{
		cout << "Empty Max Heap" << endl;
		return flase;
	}
	if (pos>current_size || pos<0)
		return false;
	node = heap_array[pos];
	heap_array[pos] = heap_array[--current_size];	// ������Ԫ��ֵ���ɾ��λ�õ�Ԫ��
	if (heap_array[getParent(pos)] < heap_array[pos])
		siftUp(pos);			// ��ǰԪ��С�ڸ���㣬��Ҫ��������
	else siftDown(pos);			// ��ǰԪ�ش��ڸ���㣬����ɸ
	return true;
} 		// ɾ�������±��Ԫ��
template<class dataType>
void maxHeap<dataType>::swap(int post_x, int post_y) {
	dataType temp = this->heap_array[post_x];
	this->heap_array[post_x] = this->heap_array[post_y];
	this->heap_array[post_y] = temp;
}

template<class dataType>
void maxHeap<dataType>::siftUp(int position) {
	dataType temp = heap_array[position];
	while ((position > 0) && (temp > heap_array[getParent(position)]))
	{
		heap_array[position] = heap_array[getParent(position)];
		position = getParent(position);
	}
	heap_array[position] = temp;
}
// ��position���Ͽ�ʼ������ʹ���г�Ϊ��
template<class dataType>
void maxHeap<dataType>::siftDown(int pos) {
	int up = pos;
	int below = getLeft(pos);
	dataType temp = heap_array[pos];
	while (below < current_size)
	{
		if ((below < current_size - 1) && heap_array[below] < heap_array[below + 1])
		{
			below++;
		}
		if ((temp < heap_array[below]))
		{
			heap_array[up] = heap_array[below];
			up = below;
			below = getLeft(up);
		}
		else break;
	}
	heap_array[up] = temp;
}
// ����ɸѡ������left��ʾ��ʼ����������±�

template<class dataType>
ostream & operator << (ostream & out, maxHeap<dataType>& mh) {
	for (int i = 0; i < mh.current_size; i++)
	{
		cout << mh.heap_array[i] << ' ';
	}
	return out;
}
#pragma once
