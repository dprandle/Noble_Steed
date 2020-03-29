#include <noble_steed/core/context_obj.h>
#include <noble_steed/core/logger.h>

namespace noble_steed
{
Context_Obj::Context_Obj()
{}

Context_Obj::~Context_Obj()
{}

void Context_Obj::pack_unpack(JSON_Archive & ar)
{
    noble_steed::pack_unpack(ar, *this);
}
String Context_Obj::to_json()
{
    JSON_Archive ar;
    ar.io_dir = Archive::DIR_OUT;
    pack_unpack(ar);
    return ar.json_str;
}
void Context_Obj::from_json(const String & json_str)
{
    JSON_Archive ar;
    ar.json_str = json_str;
    ar.io_dir = Archive::DIR_IN;
    pack_unpack(ar);
}

void Context_Obj::pack_begin(JSON_Archive::Direction io_dir)
{
    ilog("Starting to pack in direction {} object type {}!",io_dir, get_derived_info().m_type.get_name().to_string());
}

void Context_Obj::pack_end(JSON_Archive::Direction io_dir)
{
    ilog("Finished packing in direction {} object type {}!",io_dir, get_derived_info().m_type.get_name().to_string());
}

} // namespace noble_steed

#include <rttr/registration>

RTTR_REGISTRATION
{
    using namespace rttr;
    using namespace noble_steed;

    registration::class_<Context_Obj>("noble_steed::Context_Obj")
        .constructor<>()
        .method("pack_unpack", &Context_Obj::pack_unpack, registration::public_access)
        .method("to_json", &Context_Obj::to_json, registration::public_access)
        .method("from_json", &Context_Obj::from_json, registration::public_access)
        .method("pack_begin", &Context_Obj::pack_begin, registration::protected_access)
        .method("pack_end", &Context_Obj::pack_end, registration::protected_access);
}