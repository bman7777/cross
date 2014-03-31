/*
 * Continuer.h
 *
 *  Created on: Oct 4, 2013
 *      Author: bmanson
 */

#ifndef CONTINUER_H_
#define CONTINUER_H_

#include "cross/Context/FlowDefine.h"

namespace Cross
{

class Context;

// causes a transition
class Continuer
{
public:

	virtual ~Continuer() {}
	virtual void Continue(Context* ctx, ErrorCode e = ERR_NONE) {}
};

class CallbackContinuer : public Continuer
{
public:
	typedef void (*CallbackType)(ErrorCode e);

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



