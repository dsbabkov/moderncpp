#include "IpAddress.h"
#include "Split.h"
#include <charconv>

IpAddress::IpAddress(const std::string &str) {
    unsigned offset = 32;
    for (const auto &octStr: split(str, '.')) {
        offset -= 8;
        ip_ |= octetStrToInt(octStr) << offset;
    }
}

bool IpAddress::operator<(const IpAddress &o) const {
    return ip_ < o.ip_;
}

std::string IpAddress::toString() const {
    return std::to_string((ip_ >> 24) & 0xFF) + '.' +
           std::to_string((ip_ >> 16) & 0xFF) + '.' +
           std::to_string((ip_ >> 8) & 0xFF) + '.' +
           std::to_string(ip_ & 0xFF);
}

uint32_t IpAddress::octetStrToInt(std::string_view str) {
    uint32_t result;
    std::from_chars(str.data(), str.data() + str.size(), result);
    return result;
}

std::ostream &operator<<(std::ostream &os, const IpAddress &ip) {
    return os << ip.toString();
}
