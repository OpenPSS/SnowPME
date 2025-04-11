#ifndef LIB_PSS_MD5_H 
#define LIB_PSS_MD5_H
#include <vector>
#include <Sce/Pss/Core/Crypto/Algorithms/Algorithms.hpp>

namespace Sce::Pss::Core::Crypto {
	class Md5Hash {
	private:
		MD5Context* context;
	public:
		Md5Hash();
		~Md5Hash();
		void Update(uint8_t* data, size_t datasize);
		void Update(std::vector<uint8_t> data);
		uint8_t* Final();
	};
}

#endif