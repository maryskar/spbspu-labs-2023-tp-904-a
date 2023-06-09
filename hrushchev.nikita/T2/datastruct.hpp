#include <string>
#include <complex>

namespace hrushchev
{
	struct DataStruct
	{
		unsigned long long key1;
		std::complex< double > key2;
		std::string key3;
	};

	std::ostream& operator<<(std::ostream& out, const DataStruct& data);
	std::istream& operator>>(std::istream& in, DataStruct& data);

}
