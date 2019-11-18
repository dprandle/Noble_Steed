#include <noble_steed/core/system.h>
#include <noble_steed/dbg.h>
#include <rttr/registration>

namespace noble_steed
{
System::System()
{}

System::~System()
{}

const String & System::get_internal()
{
    return internal_;
}

void System::log_internal()
{
    dbg(internal_);
}

void System::set_internal(const String & to_set)
{
    internal_ = to_set;
}

RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<System>("System")
        .constructor<>()
        .method("log_internal", &System::log_internal, registration::public_access)
        .property("internal", &System::get_internal, &System::set_internal);
}

} // namespace noble_steed