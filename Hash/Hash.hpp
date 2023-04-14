#ifndef HASH_HPP
#define HASH_HPP
#include <boost/crc.hpp>

template <class HashType>
std::size_t hashBlock( const std::vector<char>& data)
{
    HashType result;
    result.process_bytes(data.data(), data.size());
    auto test=result.checksum();
    return test;
}

#endif // HASH_HPP
