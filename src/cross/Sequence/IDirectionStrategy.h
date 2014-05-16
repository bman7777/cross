/****************************************************************/
/// \class Cross::IDirectionStrategy
/// \ingroup Sequence
/// \date Feb 1, 2014
/// \brief An abstract interface that describes classes who can
///         decide the next direction in a flow.  This may take
///         into account errors or availability based on the
///         nature of the strategy.
/****************************************************************/

#ifndef IDIRECTIONSTRATEGY_H_
#define IDIRECTIONSTRATEGY_H_

namespace Cross
{

class SeqConnect;
class SeqNode;

class IDirectionStrategy
{
public:
    virtual ~IDirectionStrategy() {}

    virtual SeqNode* GetNextNode(SeqConnect* current, ErrorCode e) = 0;
};

}


#endif /* IDIRECTIONSTRATEGY_H_ */
