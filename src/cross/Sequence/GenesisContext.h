/****************************************************************/
/// \class Cross::GenesisContext
/// \ingroup Sequence
/// \date Mar 28, 2014
/// \brief The context used for generating the construction of
///         sequences.  This is then forked and split as
///         sequences are run throughout an iterator.
/****************************************************************/

#ifndef GENESISCONTEXT_H_
#define GENESISCONTEXT_H_

namespace Cross
{

class Context;

class GenesisContext
{
public:
    static Context* Get();
};
}

#endif /* GENESISCONTEXT_H_ */
