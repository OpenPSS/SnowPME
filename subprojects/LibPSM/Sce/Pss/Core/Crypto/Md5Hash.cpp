#include <Sce/Pss/Core/Crypto/Md5Hash.hpp>
#include <LibShared.hpp>

namespace Sce::Pss::Core::Crypto {
	Md5Hash::Md5Hash() {
		this->context = new MD5Context();
		md5Init(context);
	}

	Md5Hash::~Md5Hash() {
		delete this->context;
	}

	void Md5Hash::Update(uint8_t* data, size_t datasize) {
		md5Update(this->context, data, datasize);
	}
	void Md5Hash::Update(std::vector<uint8_t> data) {
		md5Update(this->context, data.data(), data.size());
	}
	uint8_t* Md5Hash::Final() {
		md5Finalize(this->context);

		return this->context->digest;
	}

}