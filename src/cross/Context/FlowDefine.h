///==============================================================
///	Cross::FlowDefine
/// Created on: Oct 4, 2013
///
/// \brief FlowDefine is a container for all definitions that
///			do not have a home and are global to the system.
///==============================================================

#ifndef FLOWDEFINE_H_
#define FLOWDEFINE_H_

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace Cross
{
    typedef int ErrorCode;
    const int ERR_NONE = 0x00000000;
    const int ERR_ENDOFDATA = 0x00001000;
    const int ERR_UNKNOWN = 0xffffffff;

    typedef int Direction;
    static const Direction DIR_NONE 	= 0x00;
    static const Direction DIR_FORWARD 	= 0x01;
    static const Direction DIR_BACKWARD	= 0x02;
    static const Direction DIR_JUMP 	= 0x03;
    static const Direction DIR_UNKNOWN 	= 0xff;

    typedef boost::uuids::uuid ModuleKey;
    static ModuleKey MakeFlowKey()
    {
        return boost::uuids::random_generator()();
    }
    static const ModuleKey INVALID_MODULE_KEY = MakeFlowKey();
}

#endif /* FLOWDEFINE_H_ */



