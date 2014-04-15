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

class Context;

class AllocationContext
{
public:
    AllocationContext(Context* ctx) : mAllocator(ctx) {}

    virtual ~AllocationContext() {}

    void* operator new (size_t size, Context* ctx);

    void operator delete (void* module);

    void operator delete (void* module, Context* ctx);

protected:
    Context* GetAllocContext() { return mAllocator; }

private:
    Context* mAllocator;
};

}


#endif /* ALLOCATIONCONTEXT_H_ */
