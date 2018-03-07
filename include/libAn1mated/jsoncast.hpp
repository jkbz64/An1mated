#ifndef AN1MATED_JSONCAST_HPP
#define AN1MATED_JSONCAST_HPP

#include <Meta.h>
#include <QJsonObject>

using json = QJsonValue;

template <typename T>
void to_json(json& j, const T& obj);

template <typename T>
void from_json(const json& j, T& obj);

namespace meta
{
    // Serialization
    template <typename Class,
            typename = std::enable_if_t <meta::isRegistered<Class>()>>
    json serialize(const Class& obj);
    
    template <typename Class,
            typename = std::enable_if_t <!meta::isRegistered<Class>()>,
            typename = void>
    json serialize(const Class& obj);
    
    template <typename Class>
    json serialize_basic(const Class& obj);

    // specialization for QVector
    template <typename T>
    json serialize_basic(const QVector<T>& obj);
    
    // Deserialization
    
    template <typename Class,
            typename = std::enable_if_t<meta::isRegistered<Class>()>>
    void deserialize(Class& obj, const json& object);
    
    template <typename Class,
            typename = std::enable_if_t<!meta::isRegistered<Class>()>,
            typename = void>
    void deserialize(Class& obj, const json& object);

    // specialization for std::vector
    template <typename T>
    void deserialize_basic(QVector<T>& obj, const json& object);
    
}

#include <jsoncast.inl>

#endif //AN1MATED_JSON_HPP
