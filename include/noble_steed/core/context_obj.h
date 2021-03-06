#pragma once

#include <rttr/type>
#include <rttr/registration_friend>
#include <noble_steed/io/json_archive.h>
#include <noble_steed/core/signal.h>
#include <noble_steed/container/array.h>
#include <mutex>

#include "variant.h"

namespace noble_steed
{

struct Event
{
    Event();
    Event(const String & name, const Variant_Hash & data_=Variant_Hash());
    Event(u32 id_, const Variant_Hash & data_=Variant_Hash());
    u32 id;
    std::chrono::nanoseconds timestamp;
    Variant_Hash data;
};

struct Event_Buffer
{
    Event_Buffer();
    void push(const Event & event);
    Event & process();
    bool available();

    Array<Event,20> frame_events;
    size_t cur_ind;
    size_t processed_ind;
};


/// Subscribe a handler functioin - params are event_id, 
#define subscribe_event_handler(event_id, ...) ns_ctxt.subscribe_to_event(this,event_id); \
    sig_connect(process_event_map[event_id], __VA_ARGS__);

#define unsubscribe_event_handler(event_id, ...) ns_ctxt.unsubscribe_to_event(this,event_id); \
    sig_disconnect(process_event_map[event_id], __VA_ARGS__); \
    process_event_map.erase(event_id);

class Context_Obj
{    
    template<class T> friend class Pool_Factory;
    template<class T> friend class Free_List_Factory;

  public:
    Context_Obj();

    Context_Obj(const Context_Obj & copy);

    virtual ~Context_Obj();

    virtual void pack_unpack(JSON_Archive & ar);

    String to_json();

    void from_json(const String & json_str);

    bool is_owned_by_context();

    Context_Obj & operator=(Context_Obj rhs);

    void push_event(const Event & event);

    void process_events();

    Hash_Map<u32, Signal<Event&>> process_event_map;
    Signal<Context_Obj*> destroyed;
    
  protected:
    void swap(Context_Obj & rhs);

    virtual void pack_begin(JSON_Archive::Direction io_dir);

    virtual void pack_end(JSON_Archive::Direction io_dir);

    Event_Buffer events_;
    std::mutex event_mutex_;

    bool owned;

    SLOT_OBJECT
    RTTR_ENABLE()
    RTTR_REGISTRATION_FRIEND
};
} // namespace noble_steed