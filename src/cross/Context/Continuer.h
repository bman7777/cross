
#ifndef CONTINUER_H_
#define CONTINUER_H_

#include <boost/function.hpp>
#include "cross/Context/FlowDefine.h"

namespace Cross
{

class Context;

/****************************************************************/
/// \class Cross::Continuer
/// \ingroup Context
/// \date Oct 4, 2013
/// \brief Continuer triggers the next part of a flow with an
///         error, if applicable.  Various classes can implement
///         this api to be themselves a continuer.
/****************************************************************/
// causes a transition
class Continuer
{
public:

    virtual ~Continuer() {}
    virtual void Continue(Context* ctx, ErrorCode e = ERR_NONE) {}
};

/****************************************************************/
/// \class Cross::CallbackContinuer
/// \ingroup Context
/// \date Oct 4, 2013
/// \brief Since commonly continuers are just pass-through
///         callbacks- this serves as a helper utility for
///         simple continuers.
/****************************************************************/
class CallbackContinuer : public Continuer
{
public:
    typedef boost::function<void (ErrorCode e)> CallbackType;

    CallbackContinuer(CallbackType callback) : mCallback(callback) {}
    virtual void Continue(Context* ctx, ErrorCode e = ERR_NONE)
    {
        mCallback(e);
    }

private:
    const CallbackType mCallback;
};

}

#endif /* CONTINUER_H_ */

