#include <jsoncast.hpp>

template <typename T>
void to_json(json& j, const T& obj)
{
    j = meta::serialize(obj);
}

template <typename T>
void from_json(const json& j, T& obj)
{
    meta::deserialize(obj, j);
}

#include <iostream>

namespace meta
{
/////////////////// SERIALIZATION
    template <typename Class,
            typename>
    json serialize(const Class& obj)
    {
        QJsonObject value;
        meta::doForAllMembers<Class>(
                [&obj, &value](auto& member)
                {
                    value.insert(member.getName(), QJsonValue(serialize_basic(member.getCopy(obj))));
                }
        );
        return json(value);
    }
    
    template <typename Class,
            typename, typename>
    json serialize(const Class& obj)
    {
        return serialize_basic(obj);
    }
    
    template <typename Class>
    json serialize_basic(const Class& obj)
    {
        return json(obj);
    }
    
    template <>
    json serialize_basic(const QString& obj)
    {
        return json(obj);
    }

    // specialization for QVector
    template <typename T>
    json serialize_basic(const QVector<T>& obj)
    {
        QJsonObject value;
        int i = 0;
        for (auto& elem : obj) {
            json jelement;
            to_json(jelement, elem);
            value[QString::number(i)] = jelement;
            ++i;
        }
        return value;
    }
    
    template <>
    json serialize_basic(const QRect& obj)
    {
        QJsonObject value;
        value["x"] = obj.x();
        value["y"] = obj.y();
        value["width"] = obj.width();
        value["height"] = obj.height();
        return value;
    }

/////////////////// DESERIALIZATION
    
    template <typename Class>
    Class deserialize(const json& obj)
    {
        Class c;
        deserialize(c, obj);
        return c;
    }
    
    template <typename T>
    struct val{};
    
    template <typename T>
    T create(const QJsonValue&, val<T>)
    {
        return T();
    }
    
    template<>
    auto create(const QJsonValue& value, val<int>) -> int
    {
        return value.toInt();
    }
    
    template<>
    auto create(const QJsonValue& value, val<QString>) -> QString
    {
        return value.toString();
    }
    
    template<>
    auto create(const QJsonValue& value, val<bool>) -> bool
    {
        return value.toBool();
    }
    
    template<typename T>
    auto create(const QJsonValue& value, val<QVector<T>>)
    {
        QVector<T> vec;
        vec.reserve(value.toObject().size());
        for (const auto& elem : value.toObject()) {
            T element;
            from_json(elem, element);
            vec.push_back(element);
        }
        return vec;
    }
    
    template <typename T>
    T create(const QJsonValue& value)
    {
        return create(value, val<T>{});
    }
    
    template <typename Class,
                typename>
    void deserialize(Class& obj, const json& object)
    {
        meta::doForAllMembers<Class>(
                [&obj, &object](auto& member)
                {
                    QJsonValue && objName = object.toObject()[member.getName()];
                    if(!objName.isNull())
                    {
                        using MemberT = meta::get_member_type<decltype(member)>;
                        if(member.hasSetter())
                        {
                            member.set(obj, create<MemberT>(objName));
                        }
                        else if(member.canGetRef())
                        {
                            member.getRef(obj) = create<MemberT>(objName);
                        }
                        else
                        {
                            throw std::runtime_error("Error: can't deserialize member because it's read only");
                        }
                    }
                }
        );
    }
    
    template <typename Class,
            typename, typename>
    void deserialize(Class& obj, const json& object)
    {
        obj = create<Class>(object);
    }
}