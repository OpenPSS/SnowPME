#include <benchmark/benchmark.h>
#include <vector>
#include <cstring>

#include <Sce/Pss/Core/Crypto/CryptoLibrary.hpp>
#include <Sce/Pss/Core/Crypto/AesCbc.hpp>
#include <Sce/Pss/Core/Crypto/AesEcb.hpp>
#include <Sce/Pss/Core/Crypto/Md5Hash.hpp>

using namespace Sce::Pss::Core::Crypto;

static std::vector<uint8_t> randomData(size_t size) {
    std::vector<uint8_t> data(size);
    for (size_t i = 0; i < size; ++i) {
        data[i] = static_cast<uint8_t>(i & 0xFF);
    }
    return data;
}

static void BM_HmacSha256(benchmark::State& state) {
    uint8_t key[0x20] = {};
    uint8_t out[0x20];
    auto data = randomData(state.range(0));

    for (auto _ : state) {
        CryptoLibrary::HmacSha256(key, out, data.data(), data.size());
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(data.size()));
}
BENCHMARK(BM_HmacSha256)->Range(64, 4096);

static void BM_Md5Sum(benchmark::State& state) {
    auto data = randomData(state.range(0));
    uint8_t out[CryptoLibrary::Md5HashSize];

    for (auto _ : state) {
        CryptoLibrary::Md5Sum(data.data(), data.size(), out);
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(data.size()));
}
BENCHMARK(BM_Md5Sum)->Range(64, 4096);

static void BM_Sha1Sum(benchmark::State& state) {
    auto data = randomData(state.range(0));
    uint8_t out[0x14];

    for (auto _ : state) {
        CryptoLibrary::Sha1Sum(data.data(), data.size(), out);
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(data.size()));
}
BENCHMARK(BM_Sha1Sum)->Range(64, 4096);

static void BM_Sha256Sum(benchmark::State& state) {
    auto data = randomData(state.range(0));
    uint8_t out[0x20];

    for (auto _ : state) {
        CryptoLibrary::Sha256Sum(data.data(), data.size(), out);
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(data.size()));
}
BENCHMARK(BM_Sha256Sum)->Range(64, 4096);

static void BM_Aes128CbcEncrypt(benchmark::State& state) {
    uint8_t key[0x10] = {};
    uint8_t iv[0x10] = {};
    auto data = randomData(state.range(0));
    std::vector<uint8_t> out;

    for (auto _ : state) {
        CryptoLibrary::Aes128CbcEncrypt(key, iv, data, out);
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(data.size()));
}
BENCHMARK(BM_Aes128CbcEncrypt)->Range(16, 4096);

static void BM_Aes128CbcDecrypt(benchmark::State& state) {
    uint8_t key[0x10] = {};
    uint8_t iv[0x10] = {};
    auto data = randomData(state.range(0));
    CryptoLibrary::Aes128CbcEncrypt(key, iv, data.data(), data.size());

    for (auto _ : state) {
        CryptoLibrary::Aes128CbcDecrypt(key, iv, data.data(), data.size());
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(data.size()));
}
BENCHMARK(BM_Aes128CbcDecrypt)->Range(16, 4096);


static void BM_AesCbc_Decrypt(benchmark::State& state) {
    uint8_t key[0x10] = {};
    uint8_t iv[0x10] = {};
    auto input = randomData(state.range(0));
    AesCbc aes(key, iv);

    for (auto _ : state) {
        aes.SetIv(iv);
        aes.Decrypt(input);
        benchmark::DoNotOptimize(input);
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(input.size()));
}
BENCHMARK(BM_AesCbc_Decrypt)->RangeMultiplier(2)->Range(16, 4096*4);

static void BM_AesEcb_Decrypt(benchmark::State& state) {
    uint8_t key[0x10] = {};
    auto input = randomData(state.range(0));
    AesEcb aes(key);

    for (auto _ : state) {
        aes.Decrypt(input);
        benchmark::DoNotOptimize(input);
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(input.size()));
}
BENCHMARK(BM_AesEcb_Decrypt)->RangeMultiplier(2)->Range(16, 4096);

static void BM_Md5Hash_UpdateFinal(benchmark::State& state) {
    auto input = randomData(state.range(0));
    Md5Hash md5;

    for (auto _ : state) {
        md5.Update(input);
    }
    uint8_t* result = md5.Final();
    state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(input.size()));
}
BENCHMARK(BM_Md5Hash_UpdateFinal)->RangeMultiplier(2)->Range(64, 4096);


BENCHMARK_MAIN();
