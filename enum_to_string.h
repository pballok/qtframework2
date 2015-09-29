#ifndef ENUM_TO_STRING_H
#define ENUM_TO_STRING_H

#include <map>
#include <string>
#include <algorithm>

template<typename E>
class EnumToString {
public:
    static std::string toString(const E& enum_value) { return map_.at(enum_value); }

    static E fromString(const std::string& str_value) {
        auto it = std::find_if(map_.begin(), map_.end(), [&str_value](auto p)->bool {return p.second == str_value;});
        if(it == map_.end()) throw std::runtime_error("Invalid enum string");
        return (*it).first;
    }

    static E fromString(const std::string& str_value, E default_value) noexcept {
        try {
            return fromString(str_value);
        } catch(const std::runtime_error&) {
            return default_value;
        }
    }

private:
    static const std::map<E, std::string> map_;
};

#endif
