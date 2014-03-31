/*
 * Service.h
 *
 *  Created on: Oct 4, 2013
 *      Author: bmanson
 */

#ifndef SERVICE_H_
#define SERVICE_H_

namespace Cross
{

class Context;

class Service
{
public:
	typedef int Key;

	static Service* Get(Key k, Context* ctx);
};

}

#endif /* SERVICE_H_ */



