#pragma once

#include "Macros.h"

template<typename T>
struct LINK_ITEM
{
	LINK_ITEM(T* item);

	LINK_ITEM<T>* next_;
	LINK_ITEM<T>* prev_;
	T* item_;
};

template<typename T>
LINK_ITEM<T>::LINK_ITEM(T* item)
	: next_(nullptr),
	prev_(nullptr),
	item_(item)
{
}


template<typename T>
class LinkedList
{
public:
	LinkedList();
	virtual ~LinkedList();

	LINK_ITEM<T>* head_;
	LINK_ITEM<T>* tail_;

	void PushFront(T* item);
	void PushBack(T* item);

	void PopFront();
	void PopBack();

	void Erase();
};


template<typename T>
LinkedList<T>::LinkedList()
	: head_(nullptr),
	tail_(nullptr)
{
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	Erase();
}

template<typename T>
void LinkedList<T>::PushFront(T* item)
{
	if (nullptr == item)
	{
		DEBUG_BREAK();
		return;
	}

	LINK_ITEM<T>* linkItem = new LINK_ITEM<T>(item);


	if (nullptr == head_)
	{
		linkItem->next_ = nullptr;
		linkItem->prev_ = nullptr;
		head_ = linkItem;
		tail_ = linkItem;
	}
	else
	{
		linkItem->prev_ = nullptr;
		linkItem->next_ = head_;
		head_->prev_ = linkItem;
		head_ = linkItem;
	}
}

template<typename T>
void LinkedList<T>::PushBack(T* item)
{
	if (nullptr == item)
	{
		DEBUG_BREAK();
		return;
	}

	LINK_ITEM<T>* linkItem = new LINK_ITEM<T>(item);

	if (nullptr == tail_)
	{
		linkItem->prev_ = nullptr;
		linkItem->next_ = nullptr;

		head_ = linkItem;
		tail_ = linkItem;
	}
	else
	{
		linkItem->prev_ = tail_;
		linkItem->next_ = nullptr;
		tail_->next_ = linkItem;
		tail_ = linkItem;
	}
}

template<typename T>
void LinkedList<T>::PopFront()
{
	if (nullptr == head_)
	{
		DEBUG_BREAK();
		return;
	}

	if (head_ == tail_)
	{
		delete head_;
		head_ = nullptr;
		tail_ = nullptr;
	}
	else
	{
		head_ = head_->next_;
		delete head_->prev_;
		head_->prev_ = nullptr;
	}

}

template<typename T>
void LinkedList<T>::PopBack()
{
	if (nullptr == tail_)
	{
		DEBUG_BREAK();
		return;
	}

	if (head_ == tail_)
	{
		delete tail_;
		head_ = nullptr;
		tail_ = nullptr;
	}
	else
	{
		tail_ = tail_->prev_;
		delete tail_->next_;
		tail_->next_ = nullptr;
	}
}

template<typename T>
void LinkedList<T>::Erase()
{
	while (head_)
	{
		PopFront();
	}
}

