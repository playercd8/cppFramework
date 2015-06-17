/*
 * IComparable.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#ifndef ICOMPARABLE_H_
#define ICOMPARABLE_H_

namespace System {

template <typename T>
class IComparable {
public:
	//IComparable() {}
	virtual ~IComparable() {}

	virtual int CompareTo(T& other) const;
};

} /* namespace System */

#endif /* ICOMPARABLE_H_ */
