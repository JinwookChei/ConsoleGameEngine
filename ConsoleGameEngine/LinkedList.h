#pragma once

#include "Macros.h"

//template<typename T>
//struct LINK_ITEM
//{
//	LINK_ITEM(T* item);
//
//	LINK_ITEM<T>* next_;
//	LINK_ITEM<T>* prev_;
//	T* item_;
//};
//
//template<typename T>
//LINK_ITEM<T>::LINK_ITEM(T* item)
//	: next_(nullptr),
//	prev_(nullptr),
//	item_(item)
//{
//}
//
//
//template<typename T>
//class LinkedList
//{
//public:
//	LinkedList();
//	virtual ~LinkedList();
//
//	LINK_ITEM<T>* head_;
//	LINK_ITEM<T>* tail_;
//
//	void PushFront(T* item);
//	void PushBack(T* item);
//
//	void PopFront();
//	void PopBack();
//
//	void Erase();
//};
//
//
//template<typename T>
//LinkedList<T>::LinkedList()
//	: head_(nullptr),
//	tail_(nullptr)
//{
//}
//
//template<typename T>
//LinkedList<T>::~LinkedList()
//{
//	Erase();
//}
//
//template<typename T>
//void LinkedList<T>::PushFront(T* item)
//{
//	if (nullptr == item)
//	{
//		DEBUG_BREAK();
//		return;
//	}
//
//	LINK_ITEM<T>* linkItem = new LINK_ITEM<T>(item);
//
//
//	if (nullptr == head_)
//	{
//		linkItem->next_ = nullptr;
//		linkItem->prev_ = nullptr;
//		head_ = linkItem;
//		tail_ = linkItem;
//	}
//	else
//	{
//		linkItem->prev_ = nullptr;
//		linkItem->next_ = head_;
//		head_->prev_ = linkItem;
//		head_ = linkItem;
//	}
//}
//
//template<typename T>
//void LinkedList<T>::PushBack(T* item)
//{
//	if (nullptr == item)
//	{
//		DEBUG_BREAK();
//		return;
//	}
//
//	LINK_ITEM<T>* linkItem = new LINK_ITEM<T>(item);
//
//	if (nullptr == tail_)
//	{
//		linkItem->prev_ = nullptr;
//		linkItem->next_ = nullptr;
//
//		head_ = linkItem;
//		tail_ = linkItem;
//	}
//	else
//	{
//		linkItem->prev_ = tail_;
//		linkItem->next_ = nullptr;
//		tail_->next_ = linkItem;
//		tail_ = linkItem;
//	}
//}
//
//template<typename T>
//void LinkedList<T>::PopFront()
//{
//	if (nullptr == head_)
//	{
//		DEBUG_BREAK();
//		return;
//	}
//
//	if (head_ == tail_)
//	{
//		delete head_;
//		head_ = nullptr;
//		tail_ = nullptr;
//	}
//	else
//	{
//		head_ = head_->next_;
//		delete head_->prev_;
//		head_->prev_ = nullptr;
//	}
//
//}
//
//template<typename T>
//void LinkedList<T>::PopBack()
//{
//	if (nullptr == tail_)
//	{
//		DEBUG_BREAK();
//		return;
//	}
//
//	if (head_ == tail_)
//	{
//		delete tail_;
//		head_ = nullptr;
//		tail_ = nullptr;
//	}
//	else
//	{
//		tail_ = tail_->prev_;
//		delete tail_->next_;
//		tail_->next_ = nullptr;
//	}
//}
//
//template<typename T>
//void LinkedList<T>::Erase()
//{
//	while (head_)
//	{
//		PopFront();
//	}
//}


template<typename T>
class LinkedList;

template<typename T>
struct LINK_ITEM
{
	LINK_ITEM(T item);
	~LINK_ITEM();

	LINK_ITEM<T>* next_;
	LINK_ITEM<T>* prev_;
	T* item_;

	LinkedList<T>* ownerLinkedList_;
};

template<typename T>
LINK_ITEM<T>::LINK_ITEM(T item)
	: next_(nullptr),
	prev_(nullptr),
	item_(new T(item)),
	ownerLinkedList_(nullptr)
{
}

template<typename T>
inline LINK_ITEM<T>::~LINK_ITEM()
{
	if (nullptr != ownerLinkedList_)
	{
		ownerLinkedList_->PopItem(this);
	}

	delete item_;
	item_ = nullptr;
}


template<typename T>
class LinkedList
{
	friend struct LINK_ITEM<T>;
public:

	LinkedList();
	virtual ~LinkedList();

	LINK_ITEM<T>* head_;
	LINK_ITEM<T>* tail_;

	bool PushFront(LINK_ITEM<T>* linkItem);
	bool PushBack(LINK_ITEM<T>* linkItem);

	LINK_ITEM<T>* PopFront();
	LINK_ITEM<T>* PopBack();

	bool PopItem(LINK_ITEM<T>* linkItem);

	void PopAll();

	//void PrintAll();
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
	PopAll();
}

template<typename T>
bool LinkedList<T>::PushFront(LINK_ITEM<T>* linkItem)
{
	if (nullptr == linkItem)
	{
		DEBUG_BREAK();
		return false;
	}

	if (this == linkItem->ownerLinkedList_)
	{
		return false;
	}



	if (nullptr == head_)
	{
		linkItem->next_ = nullptr;
		linkItem->prev_ = nullptr;
		head_ = linkItem;
		tail_ = linkItem;

		linkItem->ownerLinkedList_ = this;
	}
	else
	{
		linkItem->prev_ = nullptr;
		linkItem->next_ = &*head_;
		head_->prev_ = linkItem;
		head_ = linkItem;

		linkItem->ownerLinkedList_ = this;
	}
	return true;
}

template<typename T>
bool LinkedList<T>::PushBack(LINK_ITEM<T>* linkItem)
{
	if (nullptr == linkItem)
	{
		DEBUG_BREAK();
		return false;
	}

	if (this == linkItem->ownerLinkedList_)
	{
		return false;
	}

	if (nullptr == tail_)
	{
		linkItem->prev_ = nullptr;
		linkItem->next_ = nullptr;

		head_ = linkItem;
		tail_ = linkItem;

		linkItem->ownerLinkedList_ = this;
	}
	else
	{

		linkItem->prev_ = &*tail_;
		linkItem->next_ = nullptr;
		tail_->next_ = linkItem;
		tail_ = linkItem;

		linkItem->ownerLinkedList_ = this;
	}

	return true;
}

template<typename T>
LINK_ITEM<T>* LinkedList<T>::PopFront()
{
	if (nullptr == head_)
	{
		DEBUG_BREAK();
		return nullptr;
	}

	if (head_ == tail_)
	{
		LINK_ITEM<T>* linkItem = &*head_;
		linkItem->ownerLinkedList_ = nullptr;

		head_ = nullptr;
		tail_ = nullptr;
		return linkItem;
	}
	else
	{
		LINK_ITEM<T>* linkItem = &*head_;
		linkItem->ownerLinkedList_ = nullptr;

		head_ = &*head_->next_;
		head_->prev_ = nullptr;

		linkItem->next_ = nullptr;
		linkItem->prev_ = nullptr;
		return linkItem;
	}

}

template<typename T>
LINK_ITEM<T>* LinkedList<T>::PopBack()
{
	if (nullptr == tail_)
	{
		DEBUG_BREAK();
		return nullptr;
	}

	if (head_ == tail_)
	{
		LINK_ITEM<T>* linkItem = &*tail_;
		linkItem->ownerLinkedList_ = nullptr;

		head_ = nullptr;
		tail_ = nullptr;

		return linkItem;
	}
	else
	{
		LINK_ITEM<T>* linkItem = &*tail_;
		linkItem->ownerLinkedList_ = nullptr;

		tail_ = &*tail_->prev_;
		tail_->next_ = nullptr;

		linkItem->prev_ = nullptr;
		return linkItem;
	}
}

template<typename T>
inline bool LinkedList<T>::PopItem(LINK_ITEM<T>* linkItem)
{
	if (nullptr == linkItem)
	{
		DEBUG_BREAK();
		return false;
	}

	if (this == linkItem->ownerLinkedList_)
	{

		if (nullptr == linkItem->prev_ && nullptr == linkItem->next_)
		{
			head_ = nullptr;
			tail_ = nullptr;

			linkItem->ownerLinkedList_ = nullptr;
			return true;
		}
		else if (nullptr == linkItem->prev_)
		{
			head_ = &*linkItem->next_;
			head_->prev_ = nullptr;

			linkItem->next_ = nullptr;
			linkItem->ownerLinkedList_ = nullptr;
			return true;
		}
		else if (nullptr == linkItem->next_)
		{
			tail_ = &*linkItem->prev_;
			tail_->next_ = nullptr;

			linkItem->prev_ = nullptr;
			linkItem->ownerLinkedList_ = nullptr;
			return true;
		}
		else
		{
			linkItem->prev_->next_ = linkItem->next_;
			linkItem->next_->prev_ = linkItem->prev_;

			linkItem->prev_ = nullptr;
			linkItem->next_ = nullptr;

			linkItem->ownerLinkedList_ = nullptr;
			return true;
		}
	}
	else
	{
		return false;
	}
}

template<typename T>
void LinkedList<T>::PopAll()
{
	LINK_ITEM<T>* pCur = head_;
	while (pCur)
	{
		PopFront();
		pCur = head_;
	}
}
