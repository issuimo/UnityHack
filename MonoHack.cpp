#include "MonoHack.h"

#include <format>
#include <fstream>
#include <iostream>
#include <sstream>

namespace Untiy3D {
    auto vecpush(void* ptr, std::vector<DWORD_PTR>& v) -> void { v.push_back((DWORD_PTR)ptr); }

    auto MonoCollector::SetModule(HMODULE Module) -> void {
        hModuleMono = Module;

        if (!hModuleMono)
            MessageBox(nullptr, L"Can not find Module", L"error", NULL);
        GetFunc();
    }

    auto MonoCollector::GetFunc() -> void {
#define DO_API(ret_type, name, args ) \
		name = reinterpret_cast<name##_t>(GetProcAddress(hModuleMono, #name));
        DO_API(int, il2cpp_init, (const char* domain_name));
        DO_API(int, il2cpp_init_utf16, (const Il2CppChar * domain_name));
        DO_API(void, il2cpp_shutdown, ());
        DO_API(void, il2cpp_set_config_dir, (const char* config_path));
        DO_API(void, il2cpp_set_data_dir, (const char* data_path));
        DO_API(void, il2cpp_set_temp_dir, (const char* temp_path));
        DO_API(void, il2cpp_set_commandline_arguments, (int argc, const char* const argv[], const char* basedir));
        DO_API(void,
               il2cpp_set_commandline_arguments_utf16,
               (int argc, const Il2CppChar* const argv[], const char* basedir));
        DO_API(void, il2cpp_set_config_utf16, (const Il2CppChar * executablePath));
        DO_API(void, il2cpp_set_config, (const char* executablePath));

        DO_API(void, il2cpp_set_memory_callbacks, (Il2CppMemoryCallbacks * callbacks));
        DO_API(const Il2CppImage*, il2cpp_get_corlib, ());
        DO_API(void, il2cpp_add_internal_call, (const char* name, Il2CppMethodPointer method));
        DO_API(Il2CppMethodPointer, il2cpp_resolve_icall, (const char* name));

        DO_API(void*, il2cpp_alloc, (size_t size));
        DO_API(void, il2cpp_free, (void* ptr));

        // array
        DO_API(Il2CppClass*, il2cpp_array_class_get, (Il2CppClass * element_class, uint32_t rank));
        DO_API(uint32_t, il2cpp_array_length, (Il2CppArray * array));
        DO_API(uint32_t, il2cpp_array_get_byte_length, (Il2CppArray * array));
        DO_API(Il2CppArray*, il2cpp_array_new, (Il2CppClass * elementTypeInfo, il2cpp_array_size_t length));
        DO_API(Il2CppArray*, il2cpp_array_new_specific, (Il2CppClass * arrayTypeInfo, il2cpp_array_size_t length));
        DO_API(Il2CppArray*,
               il2cpp_array_new_full,
               (Il2CppClass * array_class, il2cpp_array_size_t * lengths, il2cpp_array_size_t * lower_bounds));
        DO_API(Il2CppClass*,
               il2cpp_bounded_array_class_get,
               (Il2CppClass * element_class, uint32_t rank, bool bounded));
        DO_API(int, il2cpp_array_element_size, (const Il2CppClass * array_class));

        // assembly
        DO_API(const Il2CppImage*, il2cpp_assembly_get_image, (const Il2CppAssembly * assembly));

        // class
        DO_API(void,
               il2cpp_class_for_each,
               (void(*klassReportFunc)(Il2CppClass * klass, void* userData), void* userData));
        DO_API(const Il2CppType*, il2cpp_class_enum_basetype, (Il2CppClass * klass));
        DO_API(bool, il2cpp_class_is_generic, (const Il2CppClass * klass));
        DO_API(bool, il2cpp_class_is_inflated, (const Il2CppClass * klass));
        DO_API(bool, il2cpp_class_is_assignable_from, (Il2CppClass * klass, Il2CppClass * oklass));
        DO_API(bool, il2cpp_class_is_subclass_of, (Il2CppClass * klass, Il2CppClass * klassc, bool check_interfaces));
        DO_API(bool, il2cpp_class_has_parent, (Il2CppClass * klass, Il2CppClass * klassc));
        DO_API(Il2CppClass*, il2cpp_class_from_il2cpp_type, (const Il2CppType * type));
        DO_API(Il2CppClass*,
               il2cpp_class_from_name,
               (const Il2CppImage * image, const char* namespaze, const char* name));
        DO_API(Il2CppClass*, il2cpp_class_from_system_type, (Il2CppReflectionType * type));
        DO_API(Il2CppClass*, il2cpp_class_get_element_class, (Il2CppClass * klass));
        DO_API(const EventInfo*, il2cpp_class_get_events, (Il2CppClass * klass, void** iter));
        DO_API(FieldInfo*, il2cpp_class_get_fields, (Il2CppClass * klass, void** iter));
        DO_API(Il2CppClass*, il2cpp_class_get_nested_types, (Il2CppClass * klass, void** iter));
        DO_API(Il2CppClass*, il2cpp_class_get_interfaces, (Il2CppClass * klass, void** iter));
        DO_API(const PropertyInfo*, il2cpp_class_get_properties, (Il2CppClass * klass, void** iter));
        DO_API(const PropertyInfo*, il2cpp_class_get_property_from_name, (Il2CppClass * klass, const char* name));
        DO_API(FieldInfo*, il2cpp_class_get_field_from_name, (Il2CppClass * klass, const char* name));
        DO_API(const MethodInfo*, il2cpp_class_get_methods, (Il2CppClass * klass, void** iter));
        DO_API(const MethodInfo*,
               il2cpp_class_get_method_from_name,
               (Il2CppClass * klass, const char* name, int argsCount));
        DO_API(const char*, il2cpp_class_get_name, (Il2CppClass * klass));
        DO_API(const char*, il2cpp_class_get_namespace, (Il2CppClass * klass));
        DO_API(Il2CppClass*, il2cpp_class_get_parent, (Il2CppClass * klass));
        DO_API(Il2CppClass*, il2cpp_class_get_declaring_type, (Il2CppClass * klass));
        DO_API(int32_t, il2cpp_class_instance_size, (Il2CppClass * klass));
        DO_API(size_t, il2cpp_class_num_fields, (const Il2CppClass * enumKlass));
        DO_API(bool, il2cpp_class_is_valuetype, (const Il2CppClass * klass));
        DO_API(int32_t, il2cpp_class_value_size, (Il2CppClass * klass, uint32_t * align));
        DO_API(bool, il2cpp_class_is_blittable, (const Il2CppClass * klass));
        DO_API(int, il2cpp_class_get_flags, (const Il2CppClass * klass));
        DO_API(bool, il2cpp_class_is_abstract, (const Il2CppClass * klass));
        DO_API(bool, il2cpp_class_is_interface, (const Il2CppClass * klass));
        DO_API(int, il2cpp_class_array_element_size, (const Il2CppClass * klass));
        DO_API(Il2CppClass*, il2cpp_class_from_type, (const Il2CppType * type));
        DO_API(const Il2CppType*, il2cpp_class_get_type, (Il2CppClass * klass));
        DO_API(uint32_t, il2cpp_class_get_type_token, (Il2CppClass * klass));
        DO_API(bool, il2cpp_class_has_attribute, (Il2CppClass * klass, Il2CppClass * attr_class));
        DO_API(bool, il2cpp_class_has_references, (Il2CppClass * klass));
        DO_API(bool, il2cpp_class_is_enum, (const Il2CppClass * klass));
        DO_API(const Il2CppImage*, il2cpp_class_get_image, (Il2CppClass * klass));
        DO_API(const char*, il2cpp_class_get_assemblyname, (const Il2CppClass * klass));
        DO_API(int, il2cpp_class_get_rank, (const Il2CppClass * klass));
        DO_API(void,
               il2cpp_type_get_name_chunked,
               (const Il2CppType * type, void(*chunkReportFunc)(void* data, void* userData), void* userData));
        DO_API(uint32_t, il2cpp_class_get_data_size, (const Il2CppClass * klass));
        DO_API(void*, il2cpp_class_get_static_field_data, (const Il2CppClass * klass));

        // testing only
        DO_API(size_t, il2cpp_class_get_bitmap_size, (const Il2CppClass * klass));
        DO_API(void, il2cpp_class_get_bitmap, (Il2CppClass * klass, size_t * bitmap));

        // stats
        DO_API(bool, il2cpp_stats_dump_to_file, (const char* path));
        DO_API(uint64_t, il2cpp_stats_get_value, (Il2CppStat stat));

        // domain
        DO_API(Il2CppDomain*, il2cpp_domain_get, ());
        DO_API(const Il2CppAssembly*, il2cpp_domain_assembly_open, (Il2CppDomain * domain, const char* name));
        DO_API(const Il2CppAssembly**, il2cpp_domain_get_assemblies, (const Il2CppDomain * domain, size_t * size));

        // exception
        DO_API(void, il2cpp_raise_exception, (Il2CppException*));
        DO_API(Il2CppException*,
               il2cpp_exception_from_name_msg,
               (const Il2CppImage * image, const char* name_space, const char* name, const char* msg));
        DO_API(Il2CppException*, il2cpp_get_exception_argument_null, (const char* arg));
        DO_API(void, il2cpp_format_exception, (const Il2CppException * ex, char* message, int message_size));
        DO_API(void, il2cpp_format_stack_trace, (const Il2CppException * ex, char* output, int output_size));
        DO_API(void, il2cpp_unhandled_exception, (Il2CppException*));

        // field
        DO_API(int, il2cpp_field_get_flags, (FieldInfo * field));
        DO_API(const char*, il2cpp_field_get_name, (FieldInfo * field));
        DO_API(Il2CppClass*, il2cpp_field_get_parent, (FieldInfo * field));
        DO_API(size_t, il2cpp_field_get_offset, (FieldInfo * field));
        DO_API(const Il2CppType*, il2cpp_field_get_type, (FieldInfo * field));
        DO_API(void, il2cpp_field_get_value, (Il2CppObject * obj, FieldInfo * field, void* value));
        DO_API(Il2CppObject*, il2cpp_field_get_value_object, (FieldInfo * field, Il2CppObject * obj));
        DO_API(bool, il2cpp_field_has_attribute, (FieldInfo * field, Il2CppClass * attr_class));
        DO_API(void, il2cpp_field_set_value, (Il2CppObject * obj, FieldInfo * field, void* value));
        DO_API(void, il2cpp_field_static_get_value, (FieldInfo * field, void* value));
        DO_API(void, il2cpp_field_static_set_value, (FieldInfo * field, void* value));
        DO_API(void, il2cpp_field_set_value_object, (Il2CppObject * instance, FieldInfo * field, Il2CppObject * value));
        DO_API(bool, il2cpp_field_is_literal, (FieldInfo * field));

        // gc
        DO_API(void, il2cpp_gc_collect, (int maxGenerations));
        DO_API(int32_t, il2cpp_gc_collect_a_little, ());
        DO_API(void, il2cpp_gc_disable, ());
        DO_API(void, il2cpp_gc_enable, ());
        DO_API(bool, il2cpp_gc_is_disabled, ());
        DO_API(int64_t, il2cpp_gc_get_used_size, ());
        DO_API(int64_t, il2cpp_gc_get_heap_size, ());
        DO_API(void, il2cpp_gc_wbarrier_set_field, (Il2CppObject * obj, void** targetAddress, MonoObject * object));
        DO_API(bool, il2cpp_gc_has_strict_wbarriers, ());
        DO_API(void, il2cpp_gc_set_external_allocation_tracker, (void(*func)(void*, size_t, int)));
        DO_API(void, il2cpp_gc_set_external_wbarrier_tracker, (void(*func)(void**)));
        DO_API(void, il2cpp_gc_foreach_heap, (void(*func)(void* data, void* userData), void* userData));
        DO_API(void, il2cpp_stop_gc_world, ());
        DO_API(void, il2cpp_start_gc_world, ());

        // gchandle
        DO_API(uint32_t, il2cpp_gchandle_new, (Il2CppObject * obj, bool pinned));
        DO_API(uint32_t, il2cpp_gchandle_new_weakref, (Il2CppObject * obj, bool track_resurrection));
        DO_API(Il2CppObject*, il2cpp_gchandle_get_target, (uint32_t gchandle));
        DO_API(void, il2cpp_gchandle_free, (uint32_t gchandle));

        // liveness
        DO_API(void*,
               il2cpp_unity_liveness_calculation_begin,
               (Il2CppClass * filter, int max_object_count, il2cpp_register_object_callback callback, void* userdata,
                   il2cpp_WorldChangedCallback onWorldStarted, il2cpp_WorldChangedCallback onWorldStopped));
        DO_API(void, il2cpp_unity_liveness_calculation_end, (void* state));
        DO_API(void, il2cpp_unity_liveness_calculation_from_root, (Il2CppObject * root, void* state));
        DO_API(void, il2cpp_unity_liveness_calculation_from_statics, (void* state));

        // method
        DO_API(const Il2CppType*, il2cpp_method_get_return_type, (const MethodInfo * method));
        DO_API(Il2CppClass*, il2cpp_method_get_declaring_type, (const MethodInfo * method));
        DO_API(const char*, il2cpp_method_get_name, (const MethodInfo * method));
        DO_API(const MethodInfo*, il2cpp_method_get_from_reflection, (const Il2CppReflectionMethod * method));
        DO_API(Il2CppReflectionMethod*, il2cpp_method_get_object, (const MethodInfo * method, Il2CppClass * refclass));
        DO_API(bool, il2cpp_method_is_generic, (const MethodInfo * method));
        DO_API(bool, il2cpp_method_is_inflated, (const MethodInfo * method));
        DO_API(bool, il2cpp_method_is_instance, (const MethodInfo * method));
        DO_API(uint32_t, il2cpp_method_get_param_count, (const MethodInfo * method));
        DO_API(const Il2CppType*, il2cpp_method_get_param, (const MethodInfo * method, uint32_t index));
        DO_API(Il2CppClass*, il2cpp_method_get_class, (const MethodInfo * method));
        DO_API(bool, il2cpp_method_has_attribute, (const MethodInfo * method, Il2CppClass * attr_class));
        DO_API(uint32_t, il2cpp_method_get_flags, (const MethodInfo * method, uint32_t * iflags));
        DO_API(uint32_t, il2cpp_method_get_token, (const MethodInfo * method));
        DO_API(const char*, il2cpp_method_get_param_name, (const MethodInfo * method, uint32_t index));

        // profiler
        DO_API(void, il2cpp_profiler_install, (Il2CppProfiler * prof, Il2CppProfileFunc shutdown_callback));
        DO_API(void, il2cpp_profiler_set_events, (Il2CppProfileFlags events));
        DO_API(void,
               il2cpp_profiler_install_enter_leave,
               (Il2CppProfileMethodFunc enter, Il2CppProfileMethodFunc fleave));
        DO_API(void, il2cpp_profiler_install_allocation, (Il2CppProfileAllocFunc callback));
        DO_API(void,
               il2cpp_profiler_install_gc,
               (Il2CppProfileGCFunc callback, Il2CppProfileGCResizeFunc heap_resize_callback));
        DO_API(void, il2cpp_profiler_install_fileio, (Il2CppProfileFileIOFunc callback));
        DO_API(void, il2cpp_profiler_install_thread, (Il2CppProfileThreadFunc start, Il2CppProfileThreadFunc end));

        // property
        DO_API(uint32_t, il2cpp_property_get_flags, (PropertyInfo * prop));
        DO_API(const MethodInfo*, il2cpp_property_get_get_method, (PropertyInfo * prop));
        DO_API(const MethodInfo*, il2cpp_property_get_set_method, (PropertyInfo * prop));
        DO_API(const char*, il2cpp_property_get_name, (PropertyInfo * prop));
        DO_API(Il2CppClass*, il2cpp_property_get_parent, (PropertyInfo * prop));

        // object
        DO_API(Il2CppClass*, il2cpp_object_get_class, (Il2CppObject * obj));
        DO_API(uint32_t, il2cpp_object_get_size, (Il2CppObject * obj));
        DO_API(const MethodInfo*, il2cpp_object_get_virtual_method, (Il2CppObject * obj, const MethodInfo * method));
        DO_API(Il2CppObject*, il2cpp_object_new, (const Il2CppClass * klass));
        DO_API(void*, il2cpp_object_unbox, (Il2CppObject * obj));

        DO_API(Il2CppObject*, il2cpp_value_box, (Il2CppClass * klass, void* data));

        // monitor
        DO_API(void, il2cpp_monitor_enter, (Il2CppObject * obj));
        DO_API(bool, il2cpp_monitor_try_enter, (Il2CppObject * obj, uint32_t timeout));
        DO_API(void, il2cpp_monitor_exit, (Il2CppObject * obj));
        DO_API(void, il2cpp_monitor_pulse, (Il2CppObject * obj));
        DO_API(void, il2cpp_monitor_pulse_all, (Il2CppObject * obj));
        DO_API(void, il2cpp_monitor_wait, (Il2CppObject * obj));
        DO_API(bool, il2cpp_monitor_try_wait, (Il2CppObject * obj, uint32_t timeout));

        // runtime
        DO_API(Il2CppObject*,
               il2cpp_runtime_invoke,
               (const MethodInfo * method, MonoObject * obj, void** params, Il2CppException * *exc));
        DO_API(Il2CppObject*,
               il2cpp_runtime_invoke_convert_args,
               (const MethodInfo * method, MonoObject * obj, Il2CppObject * *params, int paramCount, Il2CppException * *
                   exc));
        DO_API(void, il2cpp_runtime_class_init, (Il2CppClass * klass));
        DO_API(void, il2cpp_runtime_object_init, (Il2CppObject * obj));

        DO_API(void, il2cpp_runtime_object_init_exception, (Il2CppObject * obj, Il2CppException * *exc));

        DO_API(void, il2cpp_runtime_unhandled_exception_policy_set, (Il2CppRuntimeUnhandledExceptionPolicy value));

        // string
        DO_API(int32_t, il2cpp_string_length, (Il2CppString * str));
        DO_API(Il2CppChar*, il2cpp_string_chars, (Il2CppString * str));
        DO_API(Il2CppString*, il2cpp_string_new, (const char* str));
        DO_API(Il2CppString*, il2cpp_string_new_len, (const char* str, uint32_t length));
        DO_API(Il2CppString*, il2cpp_string_new_utf16, (const Il2CppChar * text, int32_t len));
        DO_API(Il2CppString*, il2cpp_string_new_wrapper, (const char* str));
        DO_API(Il2CppString*, il2cpp_string_intern, (Il2CppString * str));
        DO_API(Il2CppString*, il2cpp_string_is_interned, (Il2CppString * str));

        // thread
        DO_API(Il2CppThread*, il2cpp_thread_current, ());
        DO_API(Il2CppThread*, il2cpp_thread_attach, (Il2CppDomain * domain));
        DO_API(void, il2cpp_thread_detach, (Il2CppThread * thread));

        DO_API(Il2CppThread**, il2cpp_thread_get_all_attached_threads, (size_t * size));
        DO_API(bool, il2cpp_is_vm_thread, (Il2CppThread * thread));

        // stacktrace
        DO_API(void, il2cpp_current_thread_walk_frame_stack, (Il2CppFrameWalkFunc func, void* user_data));
        DO_API(void,
               il2cpp_thread_walk_frame_stack,
               (Il2CppThread * thread, Il2CppFrameWalkFunc func, void* user_data));
        DO_API(bool, il2cpp_current_thread_get_top_frame, (Il2CppStackFrameInfo * frame));
        DO_API(bool, il2cpp_thread_get_top_frame, (Il2CppThread * thread, Il2CppStackFrameInfo * frame));
        DO_API(bool, il2cpp_current_thread_get_frame_at, (int32_t offset, Il2CppStackFrameInfo * frame));
        DO_API(bool, il2cpp_thread_get_frame_at, (Il2CppThread * thread, int32_t offset, Il2CppStackFrameInfo * frame));
        DO_API(int32_t, il2cpp_current_thread_get_stack_depth, ());
        DO_API(int32_t, il2cpp_thread_get_stack_depth, (Il2CppThread * thread));

        // type
        DO_API(Il2CppObject*, il2cpp_type_get_object, (const Il2CppType * type));
        DO_API(int, il2cpp_type_get_type, (const Il2CppType * type));
        DO_API(Il2CppClass*, il2cpp_type_get_class_or_element_class, (const Il2CppType * type));
        DO_API(char*, il2cpp_type_get_name, (const Il2CppType * type));
        DO_API(bool, il2cpp_type_is_byref, (const Il2CppType * type));
        DO_API(uint32_t, il2cpp_type_get_attrs, (const Il2CppType * type));
        DO_API(bool, il2cpp_type_equals, (const Il2CppType * type, const Il2CppType * otherType));
        DO_API(char*, il2cpp_type_get_assembly_qualified_name, (const Il2CppType * type));

        // image
        DO_API(const Il2CppAssembly*, il2cpp_image_get_assembly, (const Il2CppImage * image));
        DO_API(const char*, il2cpp_image_get_name, (const Il2CppImage * image));
        DO_API(const char*, il2cpp_image_get_filename, (const Il2CppImage * image));
        DO_API(const MethodInfo*, il2cpp_image_get_entry_point, (const Il2CppImage * image));

        DO_API(size_t, il2cpp_image_get_class_count, (const Il2CppImage * image));
        DO_API(const Il2CppClass*, il2cpp_image_get_class, (const Il2CppImage * image, size_t index));

        // Memory information
        DO_API(Il2CppManagedMemorySnapshot*, il2cpp_capture_memory_snapshot, ());
        DO_API(void, il2cpp_free_captured_memory_snapshot, (Il2CppManagedMemorySnapshot * snapshot));

        DO_API(void, il2cpp_set_find_plugin_callback, (Il2CppSetFindPlugInCallback method));

        // Logging
        DO_API(void, il2cpp_register_log_callback, (Il2CppLogCallback method));

        // Debugger
        DO_API(void, il2cpp_debugger_set_agent_options, (const char* options));
        DO_API(bool, il2cpp_is_debugger_attached, ());

        // TLS module
        DO_API(void, il2cpp_unity_install_unitytls_interface, (const void* unitytlsInterfaceStruct));

        // custom attributes
        DO_API(Il2CppCustomAttrInfo*, il2cpp_custom_attrs_from_class, (Il2CppClass * klass));
        DO_API(Il2CppCustomAttrInfo*, il2cpp_custom_attrs_from_method, (const MethodInfo * method));

        DO_API(Il2CppObject*, il2cpp_custom_attrs_get_attr, (Il2CppCustomAttrInfo * ainfo, Il2CppClass * attr_klass));
        DO_API(bool, il2cpp_custom_attrs_has_attr, (Il2CppCustomAttrInfo * ainfo, Il2CppClass * attr_klass));
        DO_API(Il2CppArray*, il2cpp_custom_attrs_construct, (Il2CppCustomAttrInfo * cinfo));

        DO_API(void, il2cpp_custom_attrs_free, (Il2CppCustomAttrInfo * ainfo));

        DO_API(MonoDomain*, mono_get_root_domain, (void));
        DO_API(void*, mono_thread_attach, (MonoDomain * domain));
        DO_API(void, mono_thread_detach, (MonoThread * monothread));
        DO_API(void, mono_thread_cleanup, (void));
        DO_API(void*, mono_object_get_class, (MonoObject * object));

        DO_API(void, mono_domain_foreach, (GFunc func, void* user_data));

        DO_API(int, mono_domain_set, (MonoDomain * domain, bool force));
        DO_API(void*, mono_domain_get, ());
        DO_API(int, mono_assembly_foreach, (GFunc func, void* user_data));
        DO_API(MonoImage*, mono_assembly_get_image, (MonoAssembly * assembly));
        DO_API(void*, mono_assembly_open, (void* fname, int* status));
        DO_API(void*, mono_image_get_assembly, (MonoImage * image));
        DO_API(char*, mono_image_get_name, (MonoImage * image));
        DO_API(void*, mono_image_open, (const char* fname, int* status));
        DO_API(char*, mono_image_get_filename, (MonoImage * image));

        DO_API(MonoTable*, mono_image_get_table_info, (MonoImage * image, int table_id));
        DO_API(int, mono_table_info_get_rows, (MonoTable * tableinfo));
        DO_API(int, mono_metadata_decode_row_col, (MonoTable * tableinfo, int idx, unsigned int col));
        DO_API(char*, mono_metadata_string_heap, (MonoImage * image, UINT32 index));

        DO_API(void*, mono_class_from_name_case, (MonoImage * image, const char* name_space, const char* name));
        DO_API(MonoClass*, mono_class_from_name, (MonoImage * image, const char* name_space, const char* name));
        DO_API(char*, mono_class_get_name, (MonoClass * klass));
        DO_API(char*, mono_class_get_namespace, (MonoClass * klass));
        DO_API(MonoClass*, mono_class_get, (MonoImage * image, UINT32 tokenindex));
        DO_API(MonoClass*, mono_class_from_typeref, (MonoImage * image, UINT32 type_token));
        DO_API(char*, mono_class_name_from_token, (MonoImage * image, UINT32 token));

        DO_API(void*, mono_class_get_methods, (MonoClass * klass, void* iter));
        DO_API(MethodInfo*,
               mono_class_get_method_from_name,
               (MonoClass * klass, const char* methodname, int paramcount));
        DO_API(FieldInfo*, mono_class_get_fields, (MonoClass * klass, void* iter));
        DO_API(MonoClass*, mono_class_get_parent, (MonoClass * klass));
        DO_API(void*, mono_class_get_image, (MonoClass * klass));
        DO_API(void*, mono_class_vtable, (MonoDomain * domain, MonoClass * klass));
        DO_API(int, mono_class_instance_size, (MonoClass * klass));
        DO_API(void*, mono_class_from_mono_type, (MonoType * type));
        DO_API(void*, mono_class_get_element_class, (MonoClass * klass));
        DO_API(int, mono_class_is_generic, (MonoClass * klass));

        DO_API(int, mono_class_num_fields, (MonoClass * klass));
        DO_API(int, mono_class_num_methods, (MonoClass * klass));

        DO_API(char*, mono_field_get_name, (FieldInfo * field));
        DO_API(MonoType*, mono_field_get_type, (FieldInfo * field));
        DO_API(void*, mono_field_get_parent, (FieldInfo * field));
        DO_API(int, mono_field_get_offset, (FieldInfo * field));

        DO_API(char*, mono_type_get_name, (MonoType * type));
        DO_API(int, mono_type_get_type, (MonoType * type));
        DO_API(char*, mono_type_get_name_full, (MonoType * type, int format));
        DO_API(int, mono_field_get_flags, (MonoType * type));

        DO_API(FieldInfo*, mono_class_get_field_from_name, (MonoClass * klass, const char* name));

        DO_API(char*, mono_method_get_name, (MethodInfo * method));
        DO_API(void*, mono_compile_method, (MethodInfo * method));
        DO_API(void, mono_free_method, (MethodInfo * method));

        DO_API(void*, mono_jit_info_table_find, (MonoDomain * domain, void* addr));

        DO_API(void*, mono_jit_info_get_method, (void* jitinfo));
        DO_API(void*, mono_jit_info_get_code_start, (void* jitinfo));
        DO_API(int, mono_jit_info_get_code_size, (void* jitinfo));

        DO_API(int, mono_jit_exec, (MonoDomain * domain, MonoAssembly * assembly, int argc, char* argv[]));

        DO_API(uint32_t, mono_method_get_flags, (MethodInfo * method, uint32_t * iflags));
        DO_API(void*, mono_method_get_header, (MethodInfo * method));
        DO_API(void*, mono_method_get_class, (MethodInfo * method));
        DO_API(void*, mono_method_signature, (MethodInfo * method));
        DO_API(void*, mono_method_get_param_names, (MethodInfo * method, const char** names));

        DO_API(void*, mono_method_header_get_code, (MethodInfo * methodheader, UINT32 * code_size, UINT32 * max_stack));
        DO_API(char*, mono_disasm_code, (void* dishelper, MethodInfo * method, void* ip, void* end));

        DO_API(char*, mono_signature_get_desc, (void* signature, int include_namespace));
        DO_API(MonoType*, mono_signature_get_params, (MonoMethodSignature * sig, void* iter));
        DO_API(int, mono_signature_get_param_count, (void* signature));
        DO_API(MonoType*, mono_signature_get_return_type, (void* signature));

        DO_API(void*, mono_image_rva_map, (MonoImage * image, UINT32 addr));
        DO_API(void*, mono_vtable_get_static_field_data, (void* vtable));

        DO_API(void*, mono_method_desc_new, (const char* name, int include_namespace));
        DO_API(void*, mono_method_desc_from_method, (MethodInfo * method));
        DO_API(void, mono_method_desc_free, (void* desc));

        DO_API(void*, mono_assembly_name_new, (const char* name));
        DO_API(void*, mono_assembly_loaded, (void* aname));
        DO_API(void*, mono_image_loaded, (void* aname));

        DO_API(void*, mono_string_new, (MonoDomain * domain, const char* text));
        DO_API(char*, mono_string_to_utf8, (void*));
        DO_API(void*, mono_array_new, (MonoDomain * domain, void* eclass, uintptr_t n));
        DO_API(void*, mono_object_to_string, (MonoObject * object, void** exc));
        DO_API(void*, mono_object_new, (MonoDomain * domain, MonoClass * klass));

        DO_API(void, mono_free, (void*));

        DO_API(void*, mono_method_desc_search_in_image, (void* desc, MonoImage * image));
        DO_API(void*, mono_runtime_invoke, (MethodInfo * method, MonoObject * obj, void** params, MonoObject * *exc));
        DO_API(void*, mono_runtime_invoke_array, (MethodInfo * method, MonoObject * obj, void* params, void** exc));
        DO_API(void*, mono_runtime_object_init, (MonoObject * object));

        DO_API(void*, mono_field_static_get_value, (void* vtable, FieldInfo * field, void* output));
        DO_API(void*, mono_field_static_set_value, (void* vtable, FieldInfo * field, void* input));

        DO_API(void*, mono_value_box, (MonoDomain * domain, MonoClass * klass, void* val));
        DO_API(void*, mono_object_unbox, (MonoObject * obj));
        DO_API(void*, mono_class_get_type, (MonoClass * klass));
        DO_API(void*, mono_class_get_nesting_type, (MonoClass * klass));

        DO_API(int, mono_runtime_is_shutting_down, (void));
#undef DO_API
        if (mono_thread_attach) {
            if (mono_get_root_domain) {
                auto domain = mono_get_root_domain();
                mono_thread_attach(domain);
            }
        }
        if (il2cpp_thread_attach)
            il2cpp_thread_attach(il2cpp_domain_get());
    }

    template<typename T>
    auto MonoCollector::il2cpp_GetStaticClass(Il2CppClass* klass) -> T* {
        return reinterpret_cast<T*>(il2cpp_class_get_static_field_data(klass));
    }

    auto MonoCollector::Mono_GetClassParent(MonoClass* klass) -> MonoClass* { return mono_class_get_parent(klass); }

    auto MonoCollector::il2cpp_GetClassParent(Il2CppClass* klass) -> Il2CppClass* {
        return il2cpp_class_get_parent(klass);
    }

    auto MonoCollector::Mono_GetMethodParam(MethodInfo* Method, size_t index) -> MonoType* {
        auto methodsignature = mono_method_signature(Method);

        auto i = 0;

        void*     iter = nullptr;
        MonoType* method;
        do {
            method = mono_signature_get_params(static_cast<MonoMethodSignature*>(methodsignature), &iter);
            if (i == index)
                return method;
            i++;
        }
        while (method);
        return nullptr;
    }

    auto MonoCollector::Mono_Dump2File(std::string file) -> void {
        std::ofstream io(file + "\\dump.cs");
        std::ofstream io2(file + "\\Mono.hpp");
        std::ofstream io3(file + "\\Mono-func.hpp");

        if (!io)
            return;
        std::stringstream str;
        std::stringstream str2;
        std::stringstream str3;

        std::vector<MonoAssembly*> Assemblys;
        for (size_t i = 0, max = Mono_EnummAssembly(Assemblys); i < max; i++) {
            auto image = Mono_GetImage(Assemblys[i]);
            str << std::format("// Image {}: {} - {}", i, Mono_GetImageName(image), Mono_GetClassCount(image)) <<
                std::endl;
        }
        str << std::endl << std::endl << std::endl;
        for (size_t i = 0, max = Assemblys.size(); i < max; i++) {
            auto                    image = Mono_GetImage(Assemblys[i]);
            std::vector<MonoClass*> classes;
            for (size_t i_c = 0, max_c = Mono_EnumClasses(image, classes); i_c < max_c; i_c++) {
                str << std::format("// Namespace: {}\npublic class {}\n",
                                   Mono_GetClassNamespace(classes[i_c]),
                                   Mono_GetClassName(classes[i_c])) << "{\n\t// Fields" << std::endl;
                str2 << std::format("struct {}\n", Mono_GetClassName(classes[i_c])) << "{" << std::endl;

                std::vector<FieldInfo*> Field;
                for (size_t i_f = 0, max_f = Mono_EnumFields(classes[i_c], Field); i_f < max_f; i_f++) {
                    auto           Typename          = Mono_GetTypeName(Mono_GetFieldType(Field[i_f]));
                    constexpr auto STATIC_FIELD_MASK = 0x00000002; // 第2位代表字段是否静态的掩码
                    auto           fieldFlags        = mono_field_get_flags((MonoType*)Field[i_f]);
                    str << std::format("\tpublic {} {} {}; // {:#X}",
                                       (fieldFlags & STATIC_FIELD_MASK) != 0 ? "static" : "",
                                       Typename,
                                       Mono_GetFieldName(Field[i_f]),
                                       Mono_GetFieldOffset(Field[i_f])) << std::endl;
                    str2 << std::format("\t{} {}; // {:#X}",
                                        Typename,
                                        Mono_GetFieldName(Field[i_f]),
                                        Mono_GetFieldOffset(Field[i_f])) << std::endl;
                }
                str << std::endl << std::endl << std::endl << "\t// Methods" << std::endl;
                str2 << "\n};" << std::endl;

                std::vector<MethodInfo*> Methods;
                for (size_t i_m = 0, max_m = Mono_EnumMethods(classes[i_c], Methods); i_m < max_m; i_m++) {
                    auto           retTypename        = Mono_GetTypeName(Mono_GetMethodRetType(Methods[i_m]));
                    constexpr auto STATIC_METHOD_MASK = 0x00000004; // 第3位代表方法是否静态的掩码
                    UINT32         flags{};
                    int            methodFlags = mono_method_get_flags(Methods[i_m], &flags);
                    str << std::format("\tpublic {} {} {}(",
                                       (methodFlags & STATIC_METHOD_MASK) != 0 ? "static" : "",
                                       retTypename,
                                       Mono_GetMethodName(Methods[i_m]));
                    str3 << std::format("DO_API({}, {}_{}, (",
                                        retTypename,
                                        Mono_GetClassName(classes[i_c]),
                                        Mono_GetMethodName(Methods[i_m]));

                    for (size_t i_p = 0, max_p = Mono_GetMethodParamCount(Methods[i_m]); i_p < max_p; i_p++) {
                        auto Typename = Mono_GetTypeName(Mono_GetMethodParam(Methods[i_m], i_p));

                        str << retTypename << " " << Mono_GetMethodParamName(Methods[i_m], i_p) << (
                            1 == (max_p - i_p) ? "" : ", ");
                        str3 << retTypename << " " << Mono_GetMethodParamName(Methods[i_m], i_p) << (
                            1 == (max_p - i_p) ? "" : ", ");
                    }
                    str << ");\n\n";
                    str3 << "));\n";
                }
                str << "}" << std::endl << std::endl << std::endl;
            }
        }
        io << str.str();
        io2 << str2.str();
        io3 << str3.str();
        io.close();
        io2.close();
        io3.close();
    }

    auto MonoCollector::Mono_GetMethodAddress(std::string klass,
                                              std::string Method,
                                              std::string Image,
                                              std::string namespaze) -> DWORD_PTR {
        std::vector<MonoAssembly*> Assemblys;
        Mono_EnummAssembly(Assemblys);
        for (size_t i = 0, max = Assemblys.size(); i < max; i++) {
            //判断是否在镜像内
            auto image = Mono_GetImage(Assemblys[i]);
            if (Image != "") {
                if (Mono_GetImageName(image) != Image)
                    continue;
            }

            //枚举类
            std::vector<MonoClass*> classes;
            Mono_EnumClasses(image, classes);
            for (size_t i_c = 0, max_c = classes.size(); i_c < max_c; i_c++) {
                //判断空间命名是否相等
                if (namespaze != "") {
                    if (Mono_GetClassNamespace(classes[i_c]) != namespaze)
                        continue;
                }

                //判断类名是否相等
                if (Mono_GetClassName(classes[i_c]) != klass)
                    continue;

                //枚举函数
                std::vector<MethodInfo*> Methods;
                Mono_EnumMethods(classes[i_c], Methods);
                for (size_t i_m = 0, max_m = Methods.size(); i_m < max_m; i_m++) {
                    if (Mono_GetMethodName(Methods[i_m]) != Method)
                        continue;
                    return Mono_GetMethodAddress(Methods[i_m]);
                }
            }
        }
        return 0;
    }

    auto MonoCollector::Mono_GetMethodAddress(MethodInfo* method) -> DWORD_PTR {
        if (!method)
            return 0;
        return reinterpret_cast<DWORD_PTR>(mono_method_get_header(method));
    }

    auto MonoCollector::Mono_GetMethodParamName(MethodInfo* Method, size_t index) -> std::string {
        auto methodsignature = mono_method_signature(Method);
        auto paramcount      = mono_signature_get_param_count(methodsignature);
        auto names           = static_cast<char**>(calloc(sizeof(char*), paramcount));
        mono_method_get_param_names(Method, (const char**)names);
        std::string name = names[index];
        free(names);
        return name;
    }

    auto MonoCollector::Mono_GetMethodParamCount(MethodInfo* Method) -> size_t {
        auto methodsignature = mono_method_signature(Method);
        return mono_signature_get_param_count(methodsignature);
    }

    auto MonoCollector::Mono_GetMethodRetType(MethodInfo* Method) -> MonoType* {
        auto methodsignature = mono_method_signature(Method);
        return mono_signature_get_return_type(methodsignature);
    }

    auto MonoCollector::Mono_GetMethodName(MethodInfo* Method) -> std::string { return mono_method_get_name(Method); }

    auto MonoCollector::Mono_GetMethodFromName(MonoClass* klass, std::string name, DWORD argscount) -> MethodInfo* {
        return mono_class_get_method_from_name(klass, name.c_str(), argscount);
    }

    auto MonoCollector::Mono_EnumMethods(MonoClass* klass, std::vector<MethodInfo*>& Methods) -> size_t {
        void*       iter = nullptr;
        MethodInfo* method;
        do {
            method = static_cast<MethodInfo*>(mono_class_get_methods(klass, &iter));
            if (!method)
                continue;
            Methods.push_back(method);
        }
        while (method);
        return Methods.size();
    }

    auto MonoCollector::Mono_GetFieldOffset(FieldInfo* field) -> size_t { return mono_field_get_offset(field); }

    auto MonoCollector::Mono_GetFieldType(FieldInfo* field) -> MonoType* { return mono_field_get_type(field); }

    auto MonoCollector::Mono_GetFieldName(FieldInfo* field) -> std::string { return mono_field_get_name(field); }

    auto MonoCollector::Mono_GetFieldStatic(FieldInfo* field, MonoClass* klass) -> DWORD_PTR {
        QWORD val = 0;
        mono_field_static_get_value(mono_class_vtable(mono_get_root_domain(), klass), field, &val);
        return val;
    }

    auto MonoCollector::Mono_GetFieldFromName(MonoClass* klass, std::string name) -> FieldInfo* {
        return mono_class_get_field_from_name(klass, name.c_str());
    }

    auto MonoCollector::Mono_EnumFields(MonoClass* klass, std::vector<FieldInfo*>& Fields) -> size_t {
        void*      iter = nullptr;
        FieldInfo* field;
        do {
            field = mono_class_get_fields(klass, &iter);
            if (!field)
                continue;
            Fields.push_back(field);
        }
        while (field);
        return Fields.size();
    }

    auto MonoCollector::Mono_GetClassNamespace(MonoClass* klass) -> std::string {
        return mono_class_get_namespace(klass);
    }

    auto MonoCollector::Mono_GetClassName(MonoClass* klass) -> std::string { return mono_class_get_name(klass); }

    auto MonoCollector::Mono_GetClassFromName(MonoImage* image, std::string name, std::string namespaze) -> MonoClass* {
        return mono_class_from_name(image, namespaze.c_str(), name.c_str());
    }

    auto MonoCollector::Mono_EnumClasses(MonoImage* Image, std::vector<MonoClass*>& classes) -> size_t {
        auto tdef = mono_image_get_table_info(Image, MONO_TABLE_TYPEDEF);
        if (!tdef)
            return 0;
        auto tdefcount = mono_table_info_get_rows(tdef);
        for (auto i = 0; i < tdefcount; i++) {
            auto c = mono_class_get(Image, MONO_TOKEN_TYPE_DEF | (i + 1));
            if (c == nullptr)
                continue;
            classes.push_back(c);
        }
        return classes.size();
    }

    auto MonoCollector::Mono_GetImage(MonoAssembly* Assembly) -> MonoImage* {
        return mono_assembly_get_image(Assembly);
    }

    auto MonoCollector::Mono_GetImageName(MonoImage* Image) -> std::string { return mono_image_get_name(Image); }

    auto MonoCollector::Mono_GetImageFile(MonoImage* Image) -> std::string { return mono_image_get_filename(Image); }

    auto MonoCollector::Mono_GetClassCount(MonoImage* Image) -> size_t {
        auto tdef = mono_image_get_table_info(Image, MONO_TABLE_TYPEDEF);
        return mono_table_info_get_rows(tdef);
    }

    auto MonoCollector::Mono_GetTypeName(MonoType* type) -> std::string { return mono_type_get_name(type); }

    auto MonoCollector::Mono_EnummAssembly(std::vector<MonoAssembly*>& Assemblys) -> size_t {
        mono_assembly_foreach((GFunc)vecpush, &Assemblys);
        return Assemblys.size();
    }

    auto MonoCollector::Mono_EnumDomains(std::vector<MonoDomain*>& Domains) -> size_t {
        mono_domain_foreach((GFunc)vecpush, &Domains);
        return Domains.size();
    }

    auto MonoCollector::il2cpp_Dump2File(std::string file) -> void {
        std::ofstream io(file + "\\dump.cs");
        std::ofstream io2(file + "\\il2cpp.hpp");
        std::ofstream io3(file + "\\il2cpp-func.hpp");

        if (!io)
            return;
        std::stringstream str;
        std::stringstream str2;
        std::stringstream str3;

        std::vector<Il2CppAssembly*> Assemblys;
        for (size_t i = 0, max = il2cpp_EnummAssembly(Assemblys); i < max; i++) {
            auto image = il2cpp_GetImage(Assemblys[i]);
            str << std::format("// Image {}: {} - {}", i, il2cpp_GetImageName(image), il2cpp_GetClassCount(image)) <<
                std::endl;
        }
        str << std::endl << std::endl << std::endl;
        for (size_t i = 0, max = Assemblys.size(); i < max; i++) {
            auto                      image = il2cpp_GetImage(Assemblys[i]);
            std::vector<Il2CppClass*> classes;
            for (size_t i_c = 0, max_c = il2cpp_EnumClasses(image, classes); i_c < max_c; i_c++) {
                str << std::format("// Namespace: {}\npublic class {}\n",
                                   il2cpp_GetClassNamespace(classes[i_c]),
                                   il2cpp_GetClassName(classes[i_c])) << "{\n\t// Fields" << std::endl;
                str2 << std::format("struct {}\n", il2cpp_GetClassName(classes[i_c])) << "{" << std::endl;

                std::vector<FieldInfo*> Field;
                for (size_t i_f = 0, max_f = il2cpp_EnumFields(classes[i_c], Field); i_f < max_f; i_f++) {
                    auto           Typename          = il2cpp_GetTypeName(il2cpp_GetFieldType(Field[i_f]));
                    constexpr auto STATIC_FIELD_MASK = 0x00000002; // 第2位代表字段是否静态的掩码
                    auto           fieldFlags        = il2cpp_field_get_flags(Field[i_f]);
                    str << std::format("\tpublic {} {} {}; // {:#X}",
                                       (fieldFlags & STATIC_FIELD_MASK) != 0 ? "static" : "",
                                       Typename,
                                       il2cpp_GetFieldName(Field[i_f]),
                                       il2cpp_GetFieldOffset(Field[i_f])) << std::endl;
                    str2 << std::format("\t{} {}; // {:#X}",
                                        Typename,
                                        il2cpp_GetFieldName(Field[i_f]),
                                        il2cpp_GetFieldOffset(Field[i_f])) << std::endl;
                }
                str << std::endl << std::endl << std::endl << "\t// Methods" << std::endl;
                str2 << "\n};" << std::endl;

                std::vector<MethodInfo*> Methods;
                for (size_t i_m = 0, max_m = il2cpp_EnumMethods(classes[i_c], Methods); i_m < max_m; i_m++) {
                    str << std::format("\t// RVA: {:#08X}",
                                       il2cpp_GetMethodAddress(Methods[i_m]) - (DWORD_PTR)hModuleMono) << std::endl;

                    auto           retTypename        = il2cpp_GetTypeName(il2cpp_GetMethodRetType(Methods[i_m]));
                    constexpr auto STATIC_METHOD_MASK = 0x00000004; // 第3位代表方法是否静态的掩码
                    UINT32         flags{};
                    int            methodFlags = il2cpp_method_get_flags(Methods[i_m], &flags);
                    str << std::format("\tpublic {} {} {}(",
                                       (methodFlags & STATIC_METHOD_MASK) != 0 ? "static" : "",
                                       retTypename,
                                       il2cpp_GetMethodName(Methods[i_m]));
                    str3 << std::format("DO_API({}, {}_{}, (",
                                        retTypename,
                                        il2cpp_GetClassName(classes[i_c]),
                                        il2cpp_GetMethodName(Methods[i_m]));

                    for (size_t i_p = 0, max_p = il2cpp_GetMethodParamCount(Methods[i_m]); i_p < max_p; i_p++) {
                        auto Typename = il2cpp_GetTypeName(il2cpp_GetMethodParam(Methods[i_m], i_p));
                        str << Typename << " " << il2cpp_GetMethodParamName(Methods[i_m], i_p) << (
                            1 == (max_p - i_p) ? "" : ", ");
                        str3 << Typename << " " << il2cpp_GetMethodParamName(Methods[i_m], i_p) << (
                            1 == (max_p - i_p) ? "" : ", ");
                    }
                    str << ");\n\n";
                    str3 << "));\n";
                }
                str << "}" << std::endl << std::endl << std::endl;
            }
        }
        io << str.str();
        io2 << str2.str();
        io3 << str3.str();
        io.close();
        io2.close();
        io3.close();
    }

    auto MonoCollector::il2cpp_GetFieldOffset(FieldInfo* field) -> size_t { return il2cpp_field_get_offset(field); }

    auto MonoCollector::il2cpp_GetMethodAddress(std::string klass,
                                                std::string Method,
                                                std::string Image,
                                                std::string namespaze) -> DWORD_PTR {
        std::vector<Il2CppAssembly*> Assemblys;
        il2cpp_EnummAssembly(Assemblys);
        for (size_t i = 0, max = Assemblys.size(); i < max; i++) {
            //判断是否在镜像内
            auto image = il2cpp_GetImage(Assemblys[i]);
            if (Image != "") {
                if (il2cpp_GetImageName(image) != Image)
                    continue;
            }

            //枚举类
            std::vector<Il2CppClass*> classes;
            il2cpp_EnumClasses(image, classes);
            for (size_t i_c = 0, max_c = classes.size(); i_c < max_c; i_c++) {
                //判断空间命名是否相等
                if (namespaze != "") {
                    if (il2cpp_GetClassNamespace(classes[i_c]) != namespaze)
                        continue;
                }

                //判断类名是否相等
                if (il2cpp_GetClassName(classes[i_c]) != klass)
                    continue;

                //枚举函数
                std::vector<MethodInfo*> Methods;
                il2cpp_EnumMethods(classes[i_c], Methods);
                for (size_t i_m = 0, max_m = Methods.size(); i_m < max_m; i_m++) {
                    if (il2cpp_GetMethodName(Methods[i_m]) != Method)
                        continue;
                    return il2cpp_GetMethodAddress(Methods[i_m]);
                }
            }
        }
        return 0;
    }

    auto MonoCollector::il2cpp_GetMethodAddress(MethodInfo* method) -> DWORD_PTR {
        if (!method)
            return 0;
        return *reinterpret_cast<DWORD_PTR*>(method);
    }

    auto MonoCollector::il2cpp_GetMethodInstance(MethodInfo* method) -> bool {
        return il2cpp_method_is_instance(method);
    }

    auto MonoCollector::il2cpp_GetMethodFromName(Il2CppClass* klass, std::string name, DWORD argscount) -> MethodInfo* {
        return const_cast<MethodInfo*>(il2cpp_class_get_method_from_name(klass, name.c_str(), argscount));
    }

    auto MonoCollector::il2cpp_GetMethodParam(MethodInfo* Method, size_t index) -> Il2CppType* {
        return const_cast<Il2CppType*>(il2cpp_method_get_param(Method, index));
    }

    auto MonoCollector::il2cpp_GetMethodParamName(MethodInfo* Method, size_t index) -> std::string {
        return il2cpp_method_get_param_name(Method, index);
    }

    auto MonoCollector::il2cpp_GetMethodParamCount(MethodInfo* Method) -> size_t {
        return il2cpp_method_get_param_count(Method);
    }

    auto MonoCollector::il2cpp_GetMethodRetType(MethodInfo* Method) -> Il2CppType* {
        return const_cast<Il2CppType*>(il2cpp_method_get_return_type(Method));
    }

    auto MonoCollector::il2cpp_GetMethodName(MethodInfo* Method) -> std::string {
        return il2cpp_method_get_name(Method);
    }

    auto MonoCollector::il2cpp_GetClassNamespace(Il2CppClass* klass) -> std::string {
        return il2cpp_class_get_namespace(klass);
    }

    auto MonoCollector::il2cpp_GetClassCount(Il2CppImage* Image) -> size_t {
        return il2cpp_image_get_class_count(Image);
    }

    auto MonoCollector::il2cpp_GetFieldType(FieldInfo* field) -> Il2CppType* {
        return const_cast<Il2CppType*>(il2cpp_field_get_type(field));
    }

    auto MonoCollector::il2cpp_GetTypeName(Il2CppType* type) -> std::string { return il2cpp_type_get_name(type); }

    auto MonoCollector::il2cpp_GetFieldName(FieldInfo* field) -> std::string { return il2cpp_field_get_name(field); }

    auto MonoCollector::il2cpp_GetClassName(Il2CppClass* klass) -> std::string { return il2cpp_class_get_name(klass); }

    auto MonoCollector::il2cpp_GetClassFromName(Il2CppImage* image,
                                                std::string  name,
                                                std::string  namespaze) -> Il2CppClass* {
        return il2cpp_class_from_name(image, name.c_str(), namespaze.c_str());
    }

    auto MonoCollector::il2cpp_GetFieldStatic(FieldInfo* field) -> DWORD_PTR {
        void* val;
        il2cpp_field_static_get_value(field, &val);
        return reinterpret_cast<DWORD_PTR>(val);
    }

    auto MonoCollector::il2cpp_GetFieldFromName(Il2CppClass* klass, std::string name) -> FieldInfo* {
        return il2cpp_class_get_field_from_name(klass, name.c_str());
    }

    auto MonoCollector::il2cpp_EnumMethods(Il2CppClass* klass, std::vector<MethodInfo*>& Methods) -> size_t {
        void*       iter = nullptr;
        MethodInfo* method;
        do {
            method = const_cast<MethodInfo*>(il2cpp_class_get_methods(klass, &iter));
            if (!method)
                continue;
            Methods.push_back(method);
        }
        while (method);
        return Methods.size();
    }

    auto MonoCollector::il2cpp_EnumFields(Il2CppClass* klass, std::vector<FieldInfo*>& Fields) -> size_t {
        void*      iter = nullptr;
        FieldInfo* field;
        do {
            field = il2cpp_class_get_fields(klass, &iter);
            if (!field)
                continue;
            Fields.push_back(field);
        }
        while (field);
        return Fields.size();
    }

    auto MonoCollector::il2cpp_EnumClasses(Il2CppImage* Image, std::vector<Il2CppClass*>& classes) -> size_t {
        auto count = il2cpp_image_get_class_count(Image);
        classes.reserve(count);
        for (size_t i = 0; i < count; i++) {
            auto Class = const_cast<Il2CppClass*>(il2cpp_image_get_class(Image, i));
            if (!Class)
                continue;
            classes.push_back(Class);
        }
        return classes.size();
    }

    auto MonoCollector::il2cpp_GetImageName(Il2CppImage* Image) -> std::string { return il2cpp_image_get_name(Image); }

    auto MonoCollector::il2cpp_GetImageFile(Il2CppImage* Image) -> std::string {
        return il2cpp_image_get_filename(Image);
    }

    auto MonoCollector::il2cpp_GetImage(Il2CppAssembly* Assembly) -> Il2CppImage* {
        return const_cast<Il2CppImage*>(il2cpp_assembly_get_image(Assembly));
    }

    auto MonoCollector::il2cpp_EnumDomains(std::vector<Il2CppDomain*>& Domains) -> size_t {
        Domains.push_back(il2cpp_domain_get());
        return Domains.size();
    }

    auto MonoCollector::il2cpp_EnummAssembly(std::vector<Il2CppAssembly*>& Assemblys) -> size_t {
        size_t nrofassemblies = 0;
        auto   assemblies     = (Il2CppAssembly**)il2cpp_domain_get_assemblies(il2cpp_domain_get(), &nrofassemblies);
        for (auto i = 0; i < nrofassemblies; i++)
            Assemblys.push_back(assemblies[i]);
        return Assemblys.size();
    }
}
