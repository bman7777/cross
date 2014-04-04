/****************************************************************/
/// \class Cross::Service
/// \ingroup Service
/// \date Oct 4, 2013
/// \brief A base class for services that provides support for
///         service keys that index into contexts.
/****************************************************************/

#ifndef SERVICE_H_
#define SERVICE_H_

namespace Cross
{

class Context;

class Service
{
public:
    typedef int Key;

    static Service* Get(Key k, Context* ctx);
};

}

#endif /* SERVICE_H_ */
