/*
 * EVA.h
 *
 *  Created on: Oct 11, 2016
 *      Author: elvis
 */

#ifndef EVA_H_
#define EVA_H_

class EVA
{
public:
	EVA();
	virtual ~EVA();
	EVA(EVA&& src) noexcept;
	EVA& operator=(EVA&& src) noexcept;
};

#endif /* EVA_H_ */
