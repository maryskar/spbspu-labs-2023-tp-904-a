#ifndef STREAMSGUARD_H
#define STREAMSGUARD_H

#include <ios>

namespace dmitriev
{
	class StreamGuard
	{
	public:
		explicit StreamGuard(std::basic_ios< char >& stream);
		~StreamGuard();

	private:
		std::basic_ios< char >& m_stream;
		char m_fill;
		std::streamsize m_precision;
		std::basic_ios< char >::fmtflags m_flag;
	};
}

#endif
