#pragma once

//class for indidivual Entry in Map
template<typename K, typename V>
class Entry
{
private:
	K key;
	V value;
public:
	Entry(K k, V v)
		: key{ k }, value{ v } {}
	K getKey()
	{
		return key;
	}
	V getValue()
	{
		return value;
	}
	void setValue(V v)
	{
		value = v;
	}
};

// Map Class
template<typename K, typename V>
class Map
{
private:
	int size;
	int capacity = 100;
	Entry<K, V> map = new Entry[capacity];
public:

	V get(K key)
	{
		for (int i = 0; i < size; i++)
		{
			if (map[i] != nullptr)
			{
				if (map[i].getKey() == key)
				{
					return map[i].getValue();
				}
			}
		}
		return nullptr;
	}
	void put(K k, V val)
	{
		for (int i = 0; i < size; i++)
		{
			if (map[i].getKey() == k)
			{
				map[i].setValue(val);
			}
		}
	}
	int getSize()
	{
		return size;
	}
	void remove(K key)
	{
		for (int i = 0; i < size; i++)
		{
			if (map[i].getKey() == key)
			{
				map[i] = nullptr;
				size--;
				contract(i);
			}
		}
	}
	void contract(int start)
	{
		for (int i = start; i < size; i++)
		{
			map[i] = map[i + 1];
		}
	}


};