#pragma once

struct bNode
{
	bNode* Next;
	bNode* Prev;

	bNode* GetNext()
	{
		return Next;
	}

	bNode* GetPrev()
	{
		return Prev;
	}

	void Remove()
	{
		Prev->Next = Next;
		Next->Prev = Prev;
	}

	void AddAfter(bNode *insert_point)
	{
		if (!insert_point) return;

		insert_point->Prev = this;
		insert_point->Next = Next;
		
		Next->Prev = insert_point;
		Next = insert_point;
	}

	void AddBefore(bNode *insert_point)
	{
		if (!insert_point) return;

		insert_point->Next = this;
		insert_point->Prev = Prev;

		Prev->Next = insert_point;
		Prev = insert_point;
	}
};

template <typename T>
struct bTNode : bNode
{
	T* GetNext()
	{
		return (T*)bNode::GetNext();
	}

	T* GetPrev()
	{
		return (T*)bNode::GetPrev();
	}
	/*
	void Remove()
	{
		bNode::Remove();
	}

	void AddAfter(T *insert_point)
	{
		bNode::AddAfter(insert_point);
	}

	void AddBefore(T *insert_point)
	{
		bNode::AddBefore(insert_point);
	}*/
};

struct bList
{
	bNode HeadNode;

	void InitList()
	{
		HeadNode.Next = &HeadNode;
		HeadNode.Prev = &HeadNode;
	}

	bool IsEmpty()
	{
		return HeadNode.Next == &HeadNode;
	}

	bNode *GetHead()
	{
		return HeadNode.Next;
	}

	bNode *GetTail()
	{
		return HeadNode.Prev;
	}

	void AddBefore(bNode *insert_point, bNode *node)
	{
		node->AddBefore(insert_point);
	}

	void AddAfter(bNode* insert_point, bNode* node)
	{
		node->AddAfter(insert_point);
	}

	void AddHead(bNode* node)
	{
		node->AddAfter(&HeadNode);
	}

	void AddTail(bNode* node)
	{
		node->AddBefore(&HeadNode);
	}

	void Remove(bNode* node)
	{
		node->Remove();
	}

	void RemoveHead()
	{
		if (!IsEmpty())
			Remove(GetHead());
	}

	void RemoveTail()
	{
		if (!IsEmpty())
			Remove(GetTail());
	}

	int TraversebList(bNode* match_node)
	{
		bNode* next = HeadNode.Next;
		int result = 0;

		while (next != &HeadNode)
		{
			if (next == match_node)
				return ++result;
			++result;
			next = next->Next;
		}

		if (match_node) return 0;
		return result;
	}

	int IsInList(bNode *node)
	{
		return TraversebList(node);
	}

	int CountElements()
	{
		return TraversebList(nullptr);
	}
};

template <typename T>
struct bTList : bList
{
	T* GetHead()
	{
		return (T*)bList::GetHead();
	}

	T* GetTail()
	{
		return (T*)bList::GetTail();
	}
};