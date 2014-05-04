/****************************************************************/
/// \class Cross::DataContext
/// \ingroup Context
/// \date Apr 16, 2014
/// \brief container for data key that can be used to identify
///         a contextual object.
/****************************************************************/

#include <boost/uuid/uuid_generators.hpp>
#include "cross/Context/DataContext.h"

namespace Cross
{

/// \brief create a new key using a UUID to identify the object
///         uniquely.  This can be used to hash.
/// \return UUID that identifies the service
const DataContext::Key DataContext::MakeKey()
{
    boost::mt19937 ran;
    ran.seed(time(NULL)); // one should likely seed in a better way
    boost::uuids::basic_random_generator<boost::mt19937> gen(&ran);
    return gen();
}

}

