/****************************************************************/
/// \class Cross::DataContext
/// \ingroup Context
/// \date Apr 16, 2014
/// \brief container for data key that can be used to identify
///         a contextual object.
/****************************************************************/

#ifndef DATACONTEXT_H_
#define DATACONTEXT_H_

#include <boost/uuid/uuid.hpp>

namespace Cross
{

class DataContext
{
public:
    typedef boost::uuids::uuid Key;

    DataContext() : mKey(MakeKey()) {}

    const Key& GetKey() const { return mKey; }

protected:
    static Key MakeKey();

private:
    const Key mKey;
};
}


#endif /* DATACONTEXT_H_ */
