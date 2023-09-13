#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>

namespace dmitriev
{

	struct DataStruct
	{
		double key1;
		long long key2;

		std::string key3;
	};

	bool compareDataStruct(const DataStruct& lhs, const DataStruct& rhs);
	std::istream& operator>>(std::istream& inp, DataStruct& data);
	std::ostream& operator<<(std::ostream& inp, const DataStruct& data);

}

#endif
