///==============================================================
///	Cross::Module
/// Created on: Oct 3, 2013
///
/// \brief A base class for modules that allows allocations to
///			always draw from services.
///==============================================================

#ifndef FLOW_MODULE_H_
#define FLOW_MODULE_H_

namespace Cross
{

class Serial;
class Continuer;
class Context;

// encapsulates modular flow logic
class Module
{
public:
    Module(Context* cxt, Continuer* cnt=NULL, Serial* s=NULL) {}

    virtual ~Module() {}

    void* operator new (size_t size, Context& ctx);

	void operator delete (void* module);

	void operator delete (void* module, Context& ctx);
};

}

#endif /* FLOW_MODULE_H_ */



