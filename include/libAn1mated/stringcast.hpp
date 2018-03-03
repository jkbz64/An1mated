#ifndef AN1MATED_STRINGCAST_HPP
#define AN1MATED_STRINGCAST_HPP
#include <string>
#include <QString>

std::string castToString(const bool& value)
{
    return value ? "true" : "false";
}

std::string castToString(const int& value)
{
    return std::to_string(value);
}

std::string castToString(const float& value)
{
    return std::to_string(value);
}

std::string castToString(const std::string& value)
{
    return value;
}

std::string castToString(const QString& value)
{
    return value.toStdString();
}

// from string

// return empty string if no conversion possible
template <typename T>
std::string castToString(const T& /* value */)
{
    return std::string();
}

template <typename T>
T fromString(const std::string& /* value */)
{
    return T();
}

template <>
bool fromString(const std::string& valueStr)
{
    if (valueStr == "true") {
        return true;
    } else if (valueStr == "false") {
        return false;
    }
    throw std::runtime_error("Bool value is neither true nor false");
}

template <>
int fromString(const std::string& valueStr)
{
    return std::stoi(valueStr);
}

template <>
float fromString(const std::string& valueStr)
{
    return std::stof(valueStr);
}

template <>
std::string fromString(const std::string& valueStr)
{
    return valueStr;
}

template <>
QString fromString(const std::string& valueStr)
{
    return QString::fromStdString(valueStr);
}

#endif //AN1MATED_STRINGCAST_HPP
