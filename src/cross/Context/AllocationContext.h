/****************************************************************/
/// \class Cross::AllocationContext
/// \ingroup Context
/// \date Apr 11, 2014
/// \brief all classes that require use of allocation context
///         should derive from this base class
/****************************************************************/

#ifndef ALLOCATIONCONTEXT_H_
#define ALLOCATIONCONTEXT_H_

#include <memory>
#include <stddef.h>
#include "cross/Service/Allocation.h"

namespace Cross
{

class AllocationContext
{
public:
    AllocationContext() {}
    virtual ~AllocationContext() {}

private:
    Allocation::AllocInfo* GetAllocInfo() { return &mAllocInfo; }

    Allocation::AllocInfo mAllocInfo;

    friend Allocation;
};

}

#endif /* ALLOCATIONCONTEXT_H_ */
