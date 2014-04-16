/****************************************************************/
/// \class Cross::Service
/// \ingroup Service
/// \date Oct 4, 2013
/// \brief A base class for services that provides support for
///         service keys that index into contexts.
/****************************************************************/

#ifndef SERVICE_H_
#define SERVICE_H_

#include <boost/uuid/uuid.hpp>
#include "cross/Context/DataContext.h"

namespace Cross
{

class Context;

class Service : public DataContext
{
public:
    static Service* Get(const DataContext::Key& k, Context* ctx);
};

}

#endif /* SERVICE_H_ */
