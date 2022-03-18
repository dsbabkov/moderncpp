#pragma once

#include <string>

class IpAddress {
public:
    explicit IpAddress(const std::string &str);

    bool operator<(const IpAddress &o) const;

    std::string toString() const;

private:
    static uint32_t octetStrToInt(std::string_view str);

private:
    uint32_t ip_ = 0;
};

std::ostream &operator<<(std::ostream &os, const IpAddress &ip);

