/****************************************************************/
/// \class Cross::Allocation
/// \ingroup Service
/// \date Oct 4, 2013
/// \brief A service that provides allocation support for
///         flow-based entities.  This can create/destroy objects
///         from similar heaps or pools of memory across feature
///         lines.
/****************************************************************/

#ifndef ALLOCATION_H_
#define ALLOCATION_H_

#include "cross/Service/Service.h"

namespace Cross
{

class Context;

class Allocation : public Service
{
public:
    static const DataContext::Key KEY;

    Allocation(Context* ctx) : mContext(ctx) {}
    virtual ~Allocation() {}

    virtual void* Allocate(size_t size);
    virtual void DeAllocate(void* ptr);

    static Allocation* Get(Context* ctx);

private:
    Context* mContext;
};

} //end namespace


#endif /* ALLOCATION_H_ */


