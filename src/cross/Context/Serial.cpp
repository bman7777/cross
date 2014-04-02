///==============================================================
///	Cross::Serial
/// Created on: Dec 19, 2013
///
/// \brief A series of values can be packed into this object and
///			pulled from when a module is actually run.  This
///			decouples params from their place in the flow.
///==============================================================

#include <utility>
#include "cross/Context/Serial.h"

namespace Cross
{


void Serial::AddData(Serial::Key k, char c)
{
	std::pair<NodeCollection::iterator, bool> pair = mCollection.emplace(k, k);
	if(pair.second)
	{
		pair.first->second.Type = CHAR_TYPE;
		pair.first->second.Data.CharData = c;
	}
}

void Serial::AddData(Serial::Key k, float f)
{
	//mCollection.emplace(k, k, FLOAT_TYPE, f);
}

void Serial::AddData(Serial::Key k, int i)
{
	//mCollection.emplace(k, k, INT_TYPE, i);
}

void Serial::AddData(Serial::Key k, bool b)
{
	//mCollection.emplace(k, k, BOOL_TYPE, b);
}

}
