#ifndef ENUM_TO_STRING_H
#define ENUM_TO_STRING_H

#include <map>
#include <string>
#include <iostream>
#include <algorithm>

template<typename E>
class EnumToString {
public:
    static std::string toString(const E& enum_value) { try { return map_.at(enum_value); } catch(const std::out_of_range&) { return std::string("EnumToString::toString(): Unknown value"); } }
    static E fromString(const std::string& str_value) { auto it = std::find_if(map_.begin(), map_.end(), [&str_value](std::pair<E, std::string> p)->bool {return p.second == str_value;});
                                                        if(it == map_.end()) return E::UNDEFINED;
                                                        return (*it).first; }
private:
    static const std::map<E, std::string> map_;
};

#endif
