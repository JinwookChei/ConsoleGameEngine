#pragma once



template<typename Key, typename Value>
struct BUCKET_ITEM
{
	Key* key_;

	Value* value_;

	LINK_ITEM<BUCKET_ITEM<Key, Value>>* ownerLinkItem;
};

//Hash Table
template<typename Key, typename Value>
struct HASH_TABLE
{
	LinkedList<BUCKET_ITEM<Key, Value>> bucketList_;

};


template<typename Key, typename Value>
struct HashMap
{

	HashMap();

	HashMap(unsigned int numberOfKey);

	~HashMap();

	bool Initialize();


	HASH_TABLE<Key, Value>* hashTable_;

	unsigned int numberOfKey_;

	void Insert(Key* key, Value* value) const;

	bool Delete(Key* key);

	bool Select(const Key* inSearchKey, Value** outResultValue) const;

private:
	// TODO : Hash ¼öÁ¤.
	const unsigned int CreateHash(const Key* key) const;
};

template<typename Key, typename Value>
inline HashMap<Key, Value>::HashMap()
	: numberOfKey_(8),
	hashTable_(nullptr)
{
}

template<typename Key, typename Value>
inline HashMap<Key, Value>::HashMap(unsigned int numberOfKey)
	: numberOfKey_(numberOfKey),
	hashTable_(nullptr)
{
}

template<typename Key, typename Value>
inline HashMap<Key, Value>::~HashMap()
{
	if (nullptr != hashTable_) {
		free(hashTable_);
		hashTable_ = nullptr;
	}
}

template<typename Key, typename Value>
inline bool HashMap<Key, Value>::Initialize()
{
	hashTable_ = (HASH_TABLE<Key, Value>*)malloc(sizeof(HASH_TABLE<Key, Value>) * numberOfKey_);
	if (nullptr == hashTable_) {
		return false;
	}

	memset(hashTable_, 0, sizeof(HASH_TABLE<Key, Value>) * numberOfKey_);
	return true;
}

template<typename Key, typename Value>
inline void HashMap<Key, Value>::Insert(Key* key, Value* value) const
{
	const unsigned int hash = CreateHash(key);

	HASH_TABLE<Key, Value>* hashTable = &hashTable_[hash];

	BUCKET_ITEM<Key, Value>* bucketItem = new BUCKET_ITEM<Key, Value>();

	bucketItem->key_ = key;
	bucketItem->value_ = value;

	LINK_ITEM<BUCKET_ITEM<Key, Value>>* bucketLinkItem = new LINK_ITEM<BUCKET_ITEM<Key, Value>>();

	bucketLinkItem->next_ = nullptr;
	bucketLinkItem->prev_ = nullptr;
	bucketLinkItem->ownerLinkedList_ = nullptr;
	bucketLinkItem->item_ = bucketItem;

	bucketItem->ownerLinkItem = bucketLinkItem;

	hashTable->bucketList_.PushBack(bucketLinkItem);
}

template<typename Key, typename Value>
inline bool HashMap<Key, Value>::Delete(Key* key)
{
	const unsigned int hash = CreateHash(key);

	HASH_TABLE<Key, Value>* hashTable = &hashTable_[hash];

	LINK_ITEM<BUCKET_ITEM<Key, Value>>* pCur = (LINK_ITEM<BUCKET_ITEM<Key, Value>>*)hashTable->bucketList_.head_;

	while (pCur)
	{
		if (pCur->item_->key_ == key)
		{
			if (false == pCur->ownerLinkedList_->DeleteItem(pCur))
			{
				DEBUG_BREAK();
				return false;
			}

			return true;
		}

		pCur = pCur->next_;
	}

	return false;
}

template<typename Key, typename Value>
inline bool HashMap<Key, Value>::Select(const Key* inSearchKey, Value** outResultValue) const
{
	const unsigned int hash = CreateHash(inSearchKey);

	HASH_TABLE<Key, Value>* hashTable = &hashTable_[hash];

	LINK_ITEM<BUCKET_ITEM<Key, Value>>* pCur = (LINK_ITEM<BUCKET_ITEM<Key, Value>>*)hashTable->bucketList_.head_;

	while (pCur)
	{
		if (pCur->item_->key_ == inSearchKey)
		{
			*outResultValue = pCur->item_->value_;
			return true;
		}
	}

	return false;
}

template<typename Key, typename Value>
inline const unsigned int HashMap<Key, Value>::CreateHash(const Key* key) const
{
	return *key % numberOfKey_;
}
