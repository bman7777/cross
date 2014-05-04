/****************************************************************/
/// \class Cross::AllocationContext
/// \ingroup Context
/// \date Apr 11, 2014
/// \brief all classes that require use of allocation context
///         should derive from this base class
/****************************************************************/

#ifndef ALLOCATIONCONTEXT_H_
#define ALLOCATIONCONTEXT_H_

#include <stddef.h>

namespace Cross
{

class Allocation;
class Context;

class AllocationContext
{
public:
    AllocationContext(Context* ctx);

    virtual ~AllocationContext() {}

    void* operator new (size_t size, Context* ctx);

    void operator delete (void* module);

    void operator delete (void* module, Context* ctx);

protected:
    Allocation* GetAllocContext() { return mAllocator; }

private:
    Allocation* mAllocator;
};

}

#endif /* ALLOCATIONCONTEXT_H_ */
