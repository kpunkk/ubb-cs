#pragma once
#include "SortedMultiMap.h"

class Heap;

class SMMIterator{
	friend class SortedMultiMap;
	friend class Heap;
public:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);
	Heap* heap = nullptr;

	void first();
	void next() const;
	bool valid() const;
   	TElem getCurrent() const;
};

class Heap {
public:
	int capacity;
	int length;
	int* valueIndices;
	Node** currentNodes;
	TElem* elements;
	Relation relation;

	Heap(Relation relation, int capacity): relation(relation), length(0), capacity(capacity) {
		elements = new TElem[this->capacity + 1];
		valueIndices = new int[this->capacity + 1];
		currentNodes = new Node*[this->capacity + 1];
	}

	~Heap() {
		delete[] elements;
	}

	void add(TElem e) {
		if(this->length == this->capacity - 1)
			this->resize();

		this->elements[++this->length] = e;
		this->bubbleUp(this->length);
	}

	TElem getMinAndRemove() {
		TElem deletedTElem = this->elements[1];
		this->elements[1] = this->elements[this->length--];
		this->bubbleDown(1);

		return deletedTElem;
	}

	void bubbleUp(int position) const {
		TElem newTElem = this->elements[position];
		int parent = position / 2;
		while(position > 1 && relation(newTElem.first, this->elements[parent].first)) {
			this->elements[position] = this->elements[parent];
			position = parent;
			parent = position / 2;
		}

		this->elements[position] = newTElem;
	}

	void bubbleDown(int position) const {
		TElem elem = this->elements[position];
		while(position < this->length) {
			int maxChild = -1;
			if(position * 2 <= this->length)
				maxChild = position * 2;

			if(position * 2 + 1 <= this->length && relation(this->elements[2 * position + 1].first, this->elements[2 * position].first))
				maxChild = position * 2 + 1;

			if(maxChild != -1 && relation(this->elements[maxChild].first, elem.first)) {
				TElem temp = this->elements[position];
				this->elements[position] = this->elements[maxChild];
				this->elements[maxChild] = temp;
				position = maxChild;
			} else {
				position = this->length + 1;
			}
		}
	}

	void resize() {
		auto* newElements = new TElem[this->capacity * 2];
		for(int i = 0; i < this->capacity; i++)
			newElements[i] = this->elements[i];

		delete[] this->elements;
		this->elements = newElements;
		this->capacity = this->capacity * 2;
	}
};
