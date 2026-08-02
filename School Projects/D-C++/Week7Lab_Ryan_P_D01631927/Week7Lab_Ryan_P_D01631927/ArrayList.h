#pragma once

template <class T>
class ArrayList
{
private:
	const static int DEFAULT_SIZE = 5;
	T* list;
	int count;
	int capacity;

public:
	ArrayList(void)
	{
		this->list = new T[DEFAULT_SIZE];
		this->capacity = DEFAULT_SIZE;
		this->count = 0;
	}
	ArrayList(int initialCapacity)
	{
		this->list = new T[initialCapacity];
		this->capacity = initialCapacity;
		this->count = 0;
	}

	~ArrayList(void)
	{
		if (this->list != nullptr)
		{
			delete[] this->list;
			this->list = nullptr;
		}
	}

	bool isEmpty(void)
	{
		return count == 0;
	}
	
	T get(int position)
	{
		if (position < count)
			return list[position];
		else
			return NULL;
	}

	void add(T data)//add items to the ArrayList
	{
		if (count == capacity)
		{//creates bigger array
			capacity = 2 * capacity;
			T* temp = new T[capacity];

			for (int i = 0; i < count; i++)//copies items from current array to bigger array
			{
				temp[i] = list[i];
			}
			//then need to delet the current array
			delete[] list;
			//rename the bigger array
			list = temp;
		}
		list[count] = data;
		count++;
	}

	//remove item and shift list
	void removeAt(int position)
	{
		for (int i = position; i < count - 1; i++)
		{
			list[i] = list[i + 1];
		}
		count--;// decrease count to keep track
	}
	int getCount(void)
	{
		return count;
	}

	int getCapacity(void)
	{
		return capacity;
	}

};

