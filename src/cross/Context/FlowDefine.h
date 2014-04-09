/****************************************************************/
/// \class Cross::FlowDefine
/// \ingroup Context
/// \date Oct 4, 2013
/// \brief FlowDefine is a container for all definitions that
///         do not have a home and are global to the system.
/****************************************************************/

#ifndef FLOWDEFINE_H_
#define FLOWDEFINE_H_

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
}

#endif /* FLOWDEFINE_H_ */



