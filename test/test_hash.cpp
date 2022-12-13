#include "cryptopp/cryptlib.h"
#include "cryptopp/sha.h"
#include "cryptopp/blake2.h"
#include "cryptopp/keccak.h"
#include "common/utils.h"
#include "common/myhash.h"
#include <iostream>
#include <string>

int main(){ 
    CryptoPP::Keccak_256 hash;
    std::string msg = "Yoda saidconiqwoncioas ciosaioasnciosancc oancsianiwqoancoioda said, Do or do not. There is not trsdasdascjnaisncin cijanasnciasncoinwoicnqiwncio cxa csao cwoi qc sancasonciosancias concisoandioasndoisancxsai xkciasncisancoasc as ckxakc sacnjsancoisaniocnwion9wniasoniocnasoinciosancisaoncoisancoiasnoidniqwoncioas ciosaj cjas cosajcaso cwoqcnosan cioasncoiasncioasnciosancc oancsianiw";
    std::string digest;

    perf::CpuTimer<perf::ns> timer;
    timer.start();
    hash.Update((const CryptoPP::byte*)msg.c_str(), msg.size());
    digest.resize(hash.DigestSize());
    hash.Final((CryptoPP::byte*)&digest[0]);
    timer.stop();
    uint8_t ydigest[32];
    perf::CpuTimer<perf::ns> mytimer; 
    mytimer.start();
    CPUHash::calculate_hash((const uint8_t*)msg.c_str(), msg.size(), ydigest);
    mytimer.stop();
    std::cout << "Message: " << msg << std::endl;
    std::cout << "Cryptopp:"<< timer.get() << std::endl;
    std::cout << "our:" << mytimer.get() << std::endl;
    return 0;
}