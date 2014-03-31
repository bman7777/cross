/*
 * Serial.h
 *
 *  Created on: Dec 17, 2013
 *      Author: brian
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include <utility>
#include <boost/unordered_map.hpp>

namespace Cross
{

class Serial
{
public:
	typedef int Key;

	void AddData(Key k, char c);

	void AddData(Key k, float f);

	void AddData(Key k, int i);

	void AddData(Key k, bool b);

	template<typename T>
	void AddData(Key k, T* ptr);

	template<typename T>
	bool GetData(Key k, T*& ptr);

	template<typename T>
	bool GetData(Key k, T& data);
private:

	static const int INT_TYPE 	= 0;
	static const int FLOAT_TYPE = 1;
	static const int CHAR_TYPE 	= 2;
	static const int BOOL_TYPE 	= 3;
	static const int PTR_TYPE 	= 4;
	static const int INVALID_TYPE 	= 0xffffffff;
	struct Node
	{
		int Type;
		Key ValKey;

		union data
		{
			int IntData;
			float FloatData;
			char CharData;
			bool BoolData;
			void* PtrData;
		} Data;

		Node(Key k) : ValKey(k), Type(INVALID_TYPE), Data({0}) {}
	};

	typedef boost::unordered_map<Key, Node> NodeCollection;
	NodeCollection mCollection;
};

template <typename T>
bool Serial::GetData(Serial::Key k, T& data)
{
	NodeCollection::iterator iter = mCollection.find(k);
	if(iter != mCollection.end())
	{
		data = static_cast<T>(iter->second.Data.IntData);
		return true;
	}

	return false;
}

template<typename T>
bool Serial::GetData(Serial::Key k, T*& ptr)
{
	NodeCollection::iterator iter = mCollection.find(k);
	if(iter != mCollection.end())
	{
		ptr = static_cast<T*>(iter->second.Data.PtrData);
		return true;
	}

	return false;
}

template<typename T>
void Serial::AddData(Serial::Key k, T* ptr)
{
	std::pair<NodeCollection::iterator, bool> pair = mCollection.emplace(k, k);
	if(pair.second)
	{
		pair.first->second.Type = PTR_TYPE;
		pair.first->second.Data.PtrData = ptr;
	}
}

}

#endif /* SERIAL_H_ */
