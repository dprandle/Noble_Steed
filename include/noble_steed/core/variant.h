#pragma once

#include <variant>
#include <typeinfo>
#include <any>

#include "common.h"

namespace noble_steed
{
class Variant;
struct Log_Level_Info;

using Variant_Hash = Hash_Map<String, Variant>;
using Variant_Map = Map<String, Variant>;
using Variant_List = List<Variant>;
using Variant_Vec = Vector<Variant>;
using Custom_Value = std::any;

using Variant_Type = std::variant<double,
                                  bool,
                                  i8,
                                  i8_Vector,
                                  u8,
                                  u8_Vector,
                                  i16,
                                  i16_Vector,
                                  u16,
                                  u16_Vector,
                                  i32,
                                  i32_Vector,
                                  u32,
                                  u32_Vector,
                                  i64,
                                  i64_Vector,
                                  u64,
                                  u64_Vector,
                                  char,
                                  char*,
                                  const char *,
                                  uchar,
                                  dtup2,
                                  ftup2,
                                  i8tup2,
                                  i16tup2,
                                  itup2,
                                  i64tup2,
                                  u8tup2,
                                  u16tup2,
                                  utup2,
                                  u64tup2,
                                  dtup3,
                                  ftup3,
                                  i8tup3,
                                  i16tup3,
                                  itup3,
                                  i64tup3,
                                  u8tup3,
                                  u16tup3,
                                  utup3,
                                  u64tup3,
                                  dtup4,
                                  ftup4,
                                  i8tup4,
                                  i16tup4,
                                  itup4,
                                  i64tup4,
                                  u8tup4,
                                  u16tup4,
                                  utup4,
                                  u64tup4,
                                  String,
                                  String_Vector,
                                  String_List,
                                  Variant_Hash,
                                  Variant_Map,
                                  Variant_List,
                                  Variant_Vec,
                                  void *,
                                  Custom_Value>;

class Variant
{
  public:
    Variant();

    Variant(const Variant & rhs);

    template<class T>
    Variant(const T & val) : data_(val)
    {}

    ~Variant();

    template<class T>
    T & get_value()
    {
        return std::get<T>(data_);
    }

    template<class T>
    const T & get_value() const
    {
        return std::get<T>(data_);
    }

    template<class T>
    T to_value() const
    {
        T ret;
        const T * pt = get_value_ptr<T>();
        if (pt)
            ret = *pt;
        return ret;
    }

    template<class T>
    T to_custom_value() const
    {
        T * cvp = get_custom_value_ptr<T>();
        if (cvp)
            return *cvp;
    }

    template<class T>
    const T * get_value_ptr() const
    {
        return std::get_if<T>(data_);
    }

    template<class T>
    T * get_value_ptr()
    {
        return std::get_if<T>(data_);
    }

    template<class T>
    const T * get_void_ptr_cast() const
    {
        void * ptr = get_value<void *>();
        return static_cast<const T *>(ptr);
    }

    template<class T>
    const T & get_custom_value() const
    {
        const Custom_Value & v = get_value<Custom_Value>();
        return *std::any_cast<T>(&v);
    }

    template<class T>
    const T * get_custom_value_ptr() const
    {
        const Custom_Value * v = get_value_ptr<Custom_Value>();
        if (v)
            return std::any_cast<T>(&v);
        return nullptr;
    }

    template<class T>
    bool is_type() const
    {
        return std::holds_alternative<T>(data_);
    }

    template<class T>
    bool is_custom_type() const
    {
        const Custom_Value * val = get_value_ptr<Custom_Value>();
        if (val && val->type() == typeid(T))    
            return true;
        return false;
    }

    template<class T>
    void set_value(const T & from)
    {
        data_.emplace(from);
    }

    Variant & operator=(Variant rhs_cpy);

    template<class T>
    Variant & operator=(const T & rhs)
    {
        Variant cpy(rhs);
        swap(cpy);
        return *this;
    }

    void swap(Variant & rhs);

  private:
    Variant_Type data_;
};

template<class T>
bool grab_param(const Variant_Hash & items, const String & name, T & to_fill)
{
    auto fiter = items.find(name);
    if (fiter != items.end() && fiter->second.is_type<T>())
    {
        to_fill = fiter->second.get_value<T>();
        return true;
    }
    return false;
}

using xtup2 = Tuple2<Variant>;
using xtup3 = Tuple3<Variant>;
using xtup4 = Tuple4<Variant>;

} // namespace noble_steed