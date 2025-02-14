#pragma once

#include "Macros.h"

template<typename T>
class LinkedList;

template<typename T>
struct LINK_ITEM
{
	LINK_ITEM();	
	~LINK_ITEM();

	LINK_ITEM<T>* next_;
	LINK_ITEM<T>* prev_;
	T* item_;

	LinkedList<T>* ownerLinkedList_;
};

template<typename T>
inline LINK_ITEM<T>::LINK_ITEM()
	: next_(nullptr),
	prev_(nullptr),
	item_(nullptr),
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

	bool PopItem(LINK_ITEM<T>* popTarget);

	bool DeleteItem(LINK_ITEM<T>* deleteTarget);

	void PopAll();

	void DeleteAll();

	//void PrintAll() const;
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
	DeleteAll();
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
		LINK_ITEM<T>* linkItem = head_;
		linkItem->ownerLinkedList_ = nullptr;

		head_ = nullptr;
		tail_ = nullptr;
		return linkItem;
	}
	else
	{
		LINK_ITEM<T>* linkItem = head_;
		linkItem->ownerLinkedList_ = nullptr;

		head_ = head_->next_;
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
		LINK_ITEM<T>* linkItem = tail_;
		linkItem->ownerLinkedList_ = nullptr;

		head_ = nullptr;
		tail_ = nullptr;

		return linkItem;
	}
	else
	{
		LINK_ITEM<T>* linkItem = tail_;
		linkItem->ownerLinkedList_ = nullptr;

		tail_ = tail_->prev_;
		tail_->next_ = nullptr;

		linkItem->prev_ = nullptr;
		return linkItem;
	}
}

template<typename T>
inline bool LinkedList<T>::PopItem(LINK_ITEM<T>* popTarget)
{
	if (nullptr == popTarget)
	{
		DEBUG_BREAK();
		return false;
	}

	if (this == popTarget->ownerLinkedList_)
	{

		if (nullptr == popTarget->prev_ && nullptr == popTarget->next_)
		{
			head_ = nullptr;
			tail_ = nullptr;

			popTarget->ownerLinkedList_ = nullptr;
			return true;
		}
		else if (nullptr == popTarget->prev_)
		{
			head_ = &*popTarget->next_;
			head_->prev_ = nullptr;

			popTarget->next_ = nullptr;
			popTarget->ownerLinkedList_ = nullptr;
			return true;
		}
		else if (nullptr == popTarget->next_)
		{
			tail_ = &*popTarget->prev_;
			tail_->next_ = nullptr;

			popTarget->prev_ = nullptr;
			popTarget->ownerLinkedList_ = nullptr;
			return true;
		}
		else
		{
			popTarget->prev_->next_ = popTarget->next_;
			popTarget->next_->prev_ = popTarget->prev_;

			popTarget->prev_ = nullptr;
			popTarget->next_ = nullptr;

			popTarget->ownerLinkedList_ = nullptr;
			return true;
		}
	}
	else
	{
		return false;
	}
}

template<typename T>
inline bool LinkedList<T>::DeleteItem(LINK_ITEM<T>* deleteTarget)
{
	if (false == PopItem(deleteTarget))
	{
		DEBUG_BREAK();
		return false;
	}

	delete deleteTarget;
	deleteTarget = nullptr;

	return true;
}

template<typename T>
void LinkedList<T>::PopAll()
{
	//LINK_ITEM<T>* pCur = head_;
	while (head_)
	{
		PopFront();
	}
}

template<typename T>
inline void LinkedList<T>::DeleteAll()
{
	while (head_)
	{
		LINK_ITEM<T>* deleteTarget = PopFront();
		delete deleteTarget;
		deleteTarget = nullptr;
	}
}

//template<typename T>
//inline void LinkedList<T>::PrintAll() const
//{
//	LINK_ITEM<T>* pCur = head_;
//	while (pCur)
//	{
//		printf("%d\n", *pCur->item_);
//		pCur = pCur->next_;
//	}
//}

