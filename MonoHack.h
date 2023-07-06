#include <mfobjects.h>
#include <minwindef.h>
#include <string>
#include <vector>
#define MONO_DATACOLLECTORVERSION 20221207
#define MONOCMD_INITMONO 0
#define MONOCMD_OBJECT_GETCLASS 1
#define MONOCMD_ENUMDOMAINS 2
#define MONOCMD_SETCURRENTDOMAIN 3
#define MONOCMD_ENUMASSEMBLIES 4
#define MONOCMD_GETIMAGEFROMASSEMBLY 5
#define MONOCMD_GETIMAGENAME 6
#define MONOCMD_ENUMCLASSESINIMAGE 7
#define MONOCMD_ENUMFIELDSINCLASS 8
#define MONOCMD_ENUMMETHODSINCLASS 9
#define MONOCMD_COMPILEMETHOD 10
#define MONOCMD_GETMETHODHEADER 11
#define MONOCMD_GETMETHODHEADER_CODE 12
#define MONOCMD_LOOKUPRVA 13
#define MONOCMD_GETJITINFO 14
#define MONOCMD_FINDCLASS 15
#define MONOCMD_FINDMETHOD 16
#define MONOCMD_GETMETHODNAME 17
#define MONOCMD_GETMETHODCLASS 18
#define MONOCMD_GETCLASSNAME 19
#define MONOCMD_GETCLASSNAMESPACE 20
#define MONOCMD_FREEMETHOD 21
#define MONOCMD_TERMINATE 22
#define MONOCMD_DISASSEMBLE 23
#define MONOCMD_GETMETHODSIGNATURE 24
#define MONOCMD_GETPARENTCLASS 25
#define MONOCMD_GETSTATICFIELDADDRESSFROMCLASS 26
#define MONOCMD_GETTYPECLASS 27
#define MONOCMD_GETARRAYELEMENTCLASS 28
#define MONOCMD_FINDMETHODBYDESC 29
#define MONOCMD_INVOKEMETHOD 30
#define MONOCMD_LOADASSEMBLY 31
#define MONOCMD_GETFULLTYPENAME 32
#define MONOCMD_OBJECT_NEW 33
#define MONOCMD_OBJECT_INIT 34
#define MONOCMD_GETVTABLEFROMCLASS 35
#define MONOCMD_GETMETHODPARAMETERS 36
#define MONOCMD_ISCLASSGENERIC 37
#define MONOCMD_ISIL2CPP 38
#define MONOCMD_FILLOPTIONALFUNCTIONLIST 39
#define MONOCMD_GETSTATICFIELDVALUE 40
#define MONOCMD_SETSTATICFIELDVALUE 41
#define MONOCMD_GETCLASSIMAGE 42
#define MONOCMD_FREE 43
#define MONOCMD_GETIMAGEFILENAME 44
#define MONOCMD_GETCLASSNESTINGTYPE 45
#define MONOCMD_LIMITEDCONNECTION 46
#define MONOCMD_GETMONODATACOLLECTORVERSION 47
#define MONOCMD_NEWSTRING 48

using MonoTypeEnum = enum {
	MONO_TYPE_END = 0x00,
	/* End of List */
	MONO_TYPE_VOID    = 0x01,
	MONO_TYPE_BOOLEAN = 0x02,
	MONO_TYPE_CHAR    = 0x03,
	MONO_TYPE_I1      = 0x04,
	MONO_TYPE_U1      = 0x05,
	MONO_TYPE_I2      = 0x06,
	MONO_TYPE_U2      = 0x07,
	MONO_TYPE_I4      = 0x08,
	MONO_TYPE_U4      = 0x09,
	MONO_TYPE_I8      = 0x0a,
	MONO_TYPE_U8      = 0x0b,
	MONO_TYPE_R4      = 0x0c,
	MONO_TYPE_R8      = 0x0d,
	MONO_TYPE_STRING  = 0x0e,
	MONO_TYPE_PTR     = 0x0f,
	/* arg: <type> token */
	MONO_TYPE_BYREF = 0x10,
	/* arg: <type> token */
	MONO_TYPE_VALUETYPE = 0x11,
	/* arg: <type> token */
	MONO_TYPE_CLASS = 0x12,
	/* arg: <type> token */
	MONO_TYPE_VAR = 0x13,
	/* number */
	MONO_TYPE_ARRAY = 0x14,
	/* type, rank, boundsCount, bound1, loCount, lo1 */
	MONO_TYPE_GENERICINST = 0x15,
	/* <type> <type-arg-count> <type-1> \x{2026} <type-n> */
	MONO_TYPE_TYPEDBYREF = 0x16,
	MONO_TYPE_I          = 0x18,
	MONO_TYPE_U          = 0x19,
	MONO_TYPE_FNPTR      = 0x1b,
	/* arg: full method signature */
	MONO_TYPE_OBJECT  = 0x1c,
	MONO_TYPE_SZARRAY = 0x1d,
	/* 0-based one-dim-array */
	MONO_TYPE_MVAR = 0x1e,
	/* number */
	MONO_TYPE_CMOD_REQD = 0x1f,
	/* arg: typedef or typeref token */
	MONO_TYPE_CMOD_OPT = 0x20,
	/* optional arg: typedef or typref token */
	MONO_TYPE_INTERNAL = 0x21,
	/* CLR internal type */

	MONO_TYPE_MODIFIER = 0x40,
	/* Or with the following types */
	MONO_TYPE_SENTINEL = 0x41,
	/* Sentinel for varargs method signature */
	MONO_TYPE_PINNED = 0x45,
	/* Local var that points to pinned object */

	MONO_TYPE_ENUM = 0x55 /* an enumeration */
};

using MonoMetaTableEnum = enum {
	MONO_TABLE_MODULE,
	MONO_TABLE_TYPEREF,
	MONO_TABLE_TYPEDEF,
	MONO_TABLE_FIELD_POINTER,
	MONO_TABLE_FIELD,
	MONO_TABLE_METHOD_POINTER,
	MONO_TABLE_METHOD,
	MONO_TABLE_PARAM_POINTER,
	MONO_TABLE_PARAM,
	MONO_TABLE_INTERFACEIMPL,
	MONO_TABLE_MEMBERREF,
	/* 0xa */
	MONO_TABLE_CONSTANT,
	MONO_TABLE_CUSTOMATTRIBUTE,
	MONO_TABLE_FIELDMARSHAL,
	MONO_TABLE_DECLSECURITY,
	MONO_TABLE_CLASSLAYOUT,
	MONO_TABLE_FIELDLAYOUT,
	/* 0x10 */
	MONO_TABLE_STANDALONESIG,
	MONO_TABLE_EVENTMAP,
	MONO_TABLE_EVENT_POINTER,
	MONO_TABLE_EVENT,
	MONO_TABLE_PROPERTYMAP,
	MONO_TABLE_PROPERTY_POINTER,
	MONO_TABLE_PROPERTY,
	MONO_TABLE_METHODSEMANTICS,
	MONO_TABLE_METHODIMPL,
	MONO_TABLE_MODULEREF,
	/* 0x1a */
	MONO_TABLE_TYPESPEC,
	MONO_TABLE_IMPLMAP,
	MONO_TABLE_FIELDRVA,
	MONO_TABLE_UNUSED6,
	MONO_TABLE_UNUSED7,
	MONO_TABLE_ASSEMBLY,
	/* 0x20 */
	MONO_TABLE_ASSEMBLYPROCESSOR,
	MONO_TABLE_ASSEMBLYOS,
	MONO_TABLE_ASSEMBLYREF,
	MONO_TABLE_ASSEMBLYREFPROCESSOR,
	MONO_TABLE_ASSEMBLYREFOS,
	MONO_TABLE_FILE,
	MONO_TABLE_EXPORTEDTYPE,
	MONO_TABLE_MANIFESTRESOURCE,
	MONO_TABLE_NESTEDCLASS,
	MONO_TABLE_GENERICPARAM,
	/* 0x2a */
	MONO_TABLE_METHODSPEC,
	MONO_TABLE_GENERICPARAMCONSTRAINT
};

enum {
	MONO_TYPEDEF_FLAGS,
	MONO_TYPEDEF_NAME,
	MONO_TYPEDEF_NAMESPACE,
	MONO_TYPEDEF_EXTENDS,
	MONO_TYPEDEF_FIELD_LIST,
	MONO_TYPEDEF_METHOD_LIST,
	MONO_TYPEDEF_SIZE
};

enum {
	MONO_METHOD_RVA,
	MONO_METHOD_IMPLFLAGS,
	MONO_METHOD_FLAGS,
	MONO_METHOD_NAME,
	MONO_METHOD_SIGNATURE,
	MONO_METHOD_PARAMLIST,
	MONO_METHOD_SIZE
};

using MonoTokenType = enum {
	MONO_TOKEN_MODULE            = 0x00000000,
	MONO_TOKEN_TYPE_REF          = 0x01000000,
	MONO_TOKEN_TYPE_DEF          = 0x02000000,
	MONO_TOKEN_FIELD_DEF         = 0x04000000,
	MONO_TOKEN_METHOD_DEF        = 0x06000000,
	MONO_TOKEN_PARAM_DEF         = 0x08000000,
	MONO_TOKEN_INTERFACE_IMPL    = 0x09000000,
	MONO_TOKEN_MEMBER_REF        = 0x0a000000,
	MONO_TOKEN_CUSTOM_ATTRIBUTE  = 0x0c000000,
	MONO_TOKEN_PERMISSION        = 0x0e000000,
	MONO_TOKEN_SIGNATURE         = 0x11000000,
	MONO_TOKEN_EVENT             = 0x14000000,
	MONO_TOKEN_PROPERTY          = 0x17000000,
	MONO_TOKEN_MODULE_REF        = 0x1a000000,
	MONO_TOKEN_TYPE_SPEC         = 0x1b000000,
	MONO_TOKEN_ASSEMBLY          = 0x20000000,
	MONO_TOKEN_ASSEMBLY_REF      = 0x23000000,
	MONO_TOKEN_FILE              = 0x26000000,
	MONO_TOKEN_EXPORTED_TYPE     = 0x27000000,
	MONO_TOKEN_MANIFEST_RESOURCE = 0x28000000,
	MONO_TOKEN_GENERIC_PARAM     = 0x2a000000,
	MONO_TOKEN_METHOD_SPEC       = 0x2b000000,

	/*
	 * These do not match metadata tables directly
	 */
	MONO_TOKEN_STRING    = 0x70000000,
	MONO_TOKEN_NAME      = 0x71000000,
	MONO_TOKEN_BASE_TYPE = 0x72000000
};

using Il2CppProfileFlags = enum {
	IL2CPP_PROFILE_NONE             = 0,
	IL2CPP_PROFILE_APPDOMAIN_EVENTS = 1 << 0,
	IL2CPP_PROFILE_ASSEMBLY_EVENTS  = 1 << 1,
	IL2CPP_PROFILE_MODULE_EVENTS    = 1 << 2,
	IL2CPP_PROFILE_CLASS_EVENTS     = 1 << 3,
	IL2CPP_PROFILE_JIT_COMPILATION  = 1 << 4,
	IL2CPP_PROFILE_INLINING         = 1 << 5,
	IL2CPP_PROFILE_EXCEPTIONS       = 1 << 6,
	IL2CPP_PROFILE_ALLOCATIONS      = 1 << 7,
	IL2CPP_PROFILE_GC               = 1 << 8,
	IL2CPP_PROFILE_THREADS          = 1 << 9,
	IL2CPP_PROFILE_REMOTING         = 1 << 10,
	IL2CPP_PROFILE_TRANSITIONS      = 1 << 11,
	IL2CPP_PROFILE_ENTER_LEAVE      = 1 << 12,
	IL2CPP_PROFILE_COVERAGE         = 1 << 13,
	IL2CPP_PROFILE_INS_COVERAGE     = 1 << 14,
	IL2CPP_PROFILE_STATISTICAL      = 1 << 15,
	IL2CPP_PROFILE_METHOD_EVENTS    = 1 << 16,
	IL2CPP_PROFILE_MONITOR_EVENTS   = 1 << 17,
	IL2CPP_PROFILE_IOMAP_EVENTS     = 1 << 18,
	/* this should likely be removed, too */
	IL2CPP_PROFILE_GC_MOVES = 1 << 19,
	IL2CPP_PROFILE_FILEIO   = 1 << 20
};

using Il2CppProfileFileIOKind = enum {
	IL2CPP_PROFILE_FILEIO_WRITE = 0,
	IL2CPP_PROFILE_FILEIO_READ
};

using Il2CppGCEvent = enum {
	IL2CPP_GC_EVENT_START,
	IL2CPP_GC_EVENT_MARK_START,
	IL2CPP_GC_EVENT_MARK_END,
	IL2CPP_GC_EVENT_RECLAIM_START,
	IL2CPP_GC_EVENT_RECLAIM_END,
	IL2CPP_GC_EVENT_END,
	IL2CPP_GC_EVENT_PRE_STOP_WORLD,
	IL2CPP_GC_EVENT_POST_STOP_WORLD,
	IL2CPP_GC_EVENT_PRE_START_WORLD,
	IL2CPP_GC_EVENT_POST_START_WORLD
};

using Il2CppStat = enum {
	IL2CPP_STAT_NEW_OBJECT_COUNT,
	IL2CPP_STAT_INITIALIZED_CLASS_COUNT,
	//IL2CPP_STAT_GENERIC_VTABLE_COUNT,
	//IL2CPP_STAT_USED_CLASS_COUNT,
	IL2CPP_STAT_METHOD_COUNT,
	//IL2CPP_STAT_CLASS_VTABLE_SIZE,
	IL2CPP_STAT_CLASS_STATIC_DATA_SIZE,
	IL2CPP_STAT_GENERIC_INSTANCE_COUNT,
	IL2CPP_STAT_GENERIC_CLASS_COUNT,
	IL2CPP_STAT_INFLATED_METHOD_COUNT,
	IL2CPP_STAT_INFLATED_TYPE_COUNT,
	//IL2CPP_STAT_DELEGATE_CREATIONS,
	//IL2CPP_STAT_MINOR_GC_COUNT,
	//IL2CPP_STAT_MAJOR_GC_COUNT,
	//IL2CPP_STAT_MINOR_GC_TIME_USECS,
	//IL2CPP_STAT_MAJOR_GC_TIME_USECS
};

using Il2CppRuntimeUnhandledExceptionPolicy = enum {
	IL2CPP_UNHANDLED_POLICY_LEGACY,
	IL2CPP_UNHANDLED_POLICY_CURRENT
};
using Il2CppChar = wchar_t;
using Il2CppNativeChar = wchar_t;
using PropertyInfo = struct PropertyInfo;
using MonoClass = struct MonoClass;
using MonoType = struct MonoType;
using MonoTable = struct MonoTable;
using MonoMethodSignature = struct MonoMethodSignature;
using Il2CppAssembly = struct Il2CppAssembly;
using Il2CppArray = struct Il2CppArray;
using Il2CppDelegate = struct Il2CppDelegate;
using Il2CppDomain = struct Il2CppDomain;
using Il2CppImage = struct Il2CppImage;
using Il2CppException = struct Il2CppException;
using Il2CppProfiler = struct Il2CppProfiler;
using Il2CppObject = struct Il2CppObject;
using Il2CppReflectionMethod = struct Il2CppReflectionMethod;
using Il2CppReflectionType = struct Il2CppReflectionType;
using Il2CppString = struct Il2CppString;
using Il2CppThread = struct Il2CppThread;
using Il2CppAsyncResult = struct Il2CppAsyncResult;
using Il2CppManagedMemorySnapshot = struct Il2CppManagedMemorySnapshot;
using Il2CppCustomAttrInfo = struct Il2CppCustomAttrInfo;
using MonoAssembly = struct MonoAssembly;
using MonoArray = struct MonoArray;
using MonoDelegate = struct MonoDelegate;
using MonoDomain = struct MonoDomain;
using MonoImage = struct MonoImage;
using MonoException = struct MonoException;
using MonoProfiler = struct MonoProfiler;
using MonoObject = struct MonoObject;
using MonoReflectionMethod = struct MonoReflectionMethod;
using MonoReflectionType = struct MonoReflectionType;
using MonoString = struct MonoString;
using MonoThread = struct MonoThread;
using MonoAsyncResult = struct MonoAsyncResult;
using MonoManagedMemorySnapshot = struct MonoManagedMemorySnapshot;
using MonoCustomAttrInfo = struct MonoCustomAttrInfo;
using Assembly = struct Assembly;
using ParameterInfo = struct ParameterInfo;
using Il2CppClass = struct Il2CppClass;
using Il2CppType = struct Il2CppType;
using EventInfo = struct EventInfo;
using MethodInfo = struct MethodInfo;
using FieldInfo = struct FieldInfo;
using Type = struct Type;
using TypeInfo = struct TypeInfo;
using Il2CppStackFrameInfo = struct Il2CppStackFrameInfo;
using InvokerMethod = void* (*)(const MethodInfo*, void*, void**);
using il2cpp_register_object_callback = void(*)(Il2CppObject** arr, int size, void* userdata);
using il2cpp_WorldChangedCallback = void(*)();
using Il2CppFrameWalkFunc = void(*)(const Il2CppStackFrameInfo* info, void* user_data);
using Il2CppProfileFunc = void(*)(Il2CppProfiler* prof);
using Il2CppProfileMethodFunc = void(*)(Il2CppProfiler* prof, const MethodInfo* method);
using Il2CppProfileAllocFunc = void(*)(Il2CppProfiler* prof, Il2CppObject* obj, Il2CppClass* klass);
using Il2CppProfileGCFunc = void(*)(Il2CppProfiler* prof, Il2CppGCEvent event, int generation);
using Il2CppProfileGCResizeFunc = void(*)(Il2CppProfiler* prof, int64_t new_size);
using Il2CppProfileFileIOFunc = void(*)(Il2CppProfiler* prof, Il2CppProfileFileIOKind kind, int count);
using Il2CppProfileThreadFunc = void(*)(Il2CppProfiler* prof, unsigned long tid);
using Il2CppSetFindPlugInCallback = const Il2CppNativeChar* (*)(const Il2CppNativeChar*);
using Il2CppLogCallback = void(*)(const char*);
using Il2CppMethodPointer = void(*)();
using il2cpp_array_size_t = uintptr_t;
using GFunc = void(__cdecl*)(void* data, void* user_data);

struct Il2CppGuid {
	uint64_t m_uuid[2];
};

struct TypeInfo {
	const Il2CppGuid*  clsid;              // 类型 ID
	const Il2CppType** typeHierarchy;      // 类型继承层次结构
	int32_t            typeHierarchyDepth; // 继承层次深度
	Il2CppClass*       klass;              // 元数据信息
	MethodInfo**       vtableMethods;      // 虚表方法列表
	FieldInfo*         fields;             // 字段列表
	PropertyInfo*      properties;         // 属性列表
};

struct Type {
	const Il2CppType* type;         // Il2CppType类型
	const char*       name;         // 类型名称
	Assembly*         assembly;     // 所属程序集
	const MethodInfo* klass;        // 类型元数据信息
	const TypeInfo*   elementClass; // 如果该类型为数组，则此项记录数组元素类型
};

struct Assembly {
	const char*    name;       // 程序集名称
	Type**         types;      // 类型列表
	MethodInfo**   methods;    // 方法列表
	FieldInfo**    fields;     // 字段列表
	PropertyInfo** properties; // 属性列表
};

struct ParameterInfo {
	const char*   name;            // 参数名称
	const Type*   parameterType;   // 参数类型
	bool          hasDefaultValue; // 是否有默认值
	Il2CppObject* defaultValue;    // 默认值
	int           position;        // 参数位置
};

using MethodInfo = struct MethodInfo {
	Il2CppMethodPointer  methodPointer;  // 函数指针，用于调用函数
	InvokerMethod        invoker_method; // 调用器方法指针，用于支持跨域调用等功能
	const char*          name;           // 函数名
	Il2CppClass*         klass;          // 函数所属的类的 Il2CppClass 对象
	Il2CppType*          return_type;    // 函数返回值类型
	const ParameterInfo* parameters;     // 函数参数列表
	union {
		const void* methodMetadata; // 函数元数据信息，用于反射操作
		uint32_t    token;          // 函数的元数据标记值，用于反射操作
	};

	uint32_t flags; // 函数的特性标记值，包括是否是 static 函数等
};

using FieldInfo = struct FieldInfo {
	const char*  name;                 // 变量名
	Il2CppType*  type;                 // 变量类型
	Il2CppClass* parent;               // 变量所在的类的 Il2CppClass 对象
	int32_t      offset;               // 变量地址偏移量
	uint32_t     token;                // 变量的元数据标记值，用于反射操作
	int32_t      customAttributeIndex; // 自定义属性索引
	uint32_t     flags;                // 变量的特性标记值，包括是否是 static 属性等
};

using Il2CppStackFrameInfo = struct Il2CppStackFrameInfo {
	const MethodInfo* method;
};

using Il2CppMemoryCallbacks = struct {
	void* (*malloc_func)(size_t size);
	void* (*aligned_malloc_func)(size_t size, size_t alignment);
	void (* free_func)(void* ptr);
	void (* aligned_free_func)(void* ptr);
	void* (*calloc_func)(size_t nmemb, size_t size);
	void* (*realloc_func)(void* ptr, size_t size);
	void* (*aligned_realloc_func)(void* ptr, size_t size, size_t alignment);
};

namespace Unity3D {
	class MonoCollector {
	public:
		static auto SetModule(HMODULE Module) -> void;

		// il2cpp

		// Dump
		static auto il2cpp_Dump2File(std::string file) -> void;

		// Domains (域)
		static auto il2cpp_EnumDomains(std::vector<Il2CppDomain*>& Domains) -> size_t;

		// Assembly (程序集)
		static auto il2cpp_EnummAssembly(std::vector<Il2CppAssembly*>& Assemblys) -> size_t;

		// Type (类型)
		static auto il2cpp_GetTypeName(Il2CppType* type) -> std::string;

		// Image (镜像)
		static auto il2cpp_GetImage(Il2CppAssembly* Assembly) -> Il2CppImage*;
		static auto il2cpp_GetImageName(Il2CppImage* Image) -> std::string;
		static auto il2cpp_GetImageFile(Il2CppImage* Image) -> std::string;

		// Class (类)
		static auto il2cpp_EnumClasses(Il2CppImage* Image, std::vector<Il2CppClass*>& Classes) -> size_t;
		static auto il2cpp_GetClassFromName(Il2CppImage* image, std::string name,
		                                    std::string  namespaze = "") -> Il2CppClass*;
		static auto il2cpp_GetClassName(Il2CppClass* klass) -> std::string;
		static auto il2cpp_GetClassNamespace(Il2CppClass* klass) -> std::string;
		static auto il2cpp_GetClassCount(Il2CppImage* Image) -> size_t;
		static auto il2cpp_GetClassParent(Il2CppClass* klass) -> Il2CppClass*;
		template <typename T>
		static auto il2cpp_GetStaticClass(Il2CppClass* klass) -> T*;

		// Field (变量)
		static auto il2cpp_EnumFields(Il2CppClass* klass, std::vector<FieldInfo*>& Fields) -> size_t;
		static auto il2cpp_GetFieldFromName(Il2CppClass* klass, std::string name) -> FieldInfo*;
		static auto il2cpp_GetFieldStatic(FieldInfo* field) -> DWORD_PTR;
		static auto il2cpp_GetFieldName(FieldInfo* field) -> std::string;
		static auto il2cpp_GetFieldType(FieldInfo* field) -> Il2CppType*;
		static auto il2cpp_GetFieldOffset(FieldInfo* field) -> size_t;

		// Method (函数)
		static auto il2cpp_EnumMethods(Il2CppClass* klass, std::vector<MethodInfo*>& Methods) -> size_t;
		static auto il2cpp_GetMethodFromName(Il2CppClass* klass, std::string name, DWORD argscount = -1) -> MethodInfo*;
		static auto il2cpp_GetMethodName(MethodInfo* Method) -> std::string;
		static auto il2cpp_GetMethodRetType(MethodInfo* Method) -> Il2CppType*;
		static auto il2cpp_GetMethodParamCount(MethodInfo* Method) -> size_t;
		static auto il2cpp_GetMethodParam(MethodInfo* Method, size_t index) -> Il2CppType*;
		static auto il2cpp_GetMethodParamName(MethodInfo* Method, size_t index) -> std::string;
		static auto il2cpp_GetMethodInstance(MethodInfo* method) -> bool;
		static auto il2cpp_GetMethodAddress(MethodInfo* method) -> DWORD_PTR;
		static auto il2cpp_GetMethodAddress(std::string klass, std::string Method, std::string Image = "",
		                                    std::string namespaze                                    = "") -> DWORD_PTR;

		// Mono

		// Dump
		static auto Mono_Dump2File(std::string file) -> void;

		// Domains (域)
		static auto Mono_EnumDomains(std::vector<MonoDomain*>& Domains) -> size_t;

		// Assembly (程序集)
		static auto Mono_EnummAssembly(std::vector<MonoAssembly*>& Assemblys) -> size_t;

		// Type (类型)
		static auto Mono_GetTypeName(MonoType* type) -> std::string;

		// Image (镜像)
		static auto Mono_GetImage(MonoAssembly* Assembly) -> MonoImage*;
		static auto Mono_GetImageName(MonoImage* Image) -> std::string;
		static auto Mono_GetImageFile(MonoImage* Image) -> std::string;

		// Class (类)
		static auto Mono_EnumClasses(MonoImage* Image, std::vector<MonoClass*>& Classes) -> size_t;
		static auto Mono_GetClassFromName(MonoImage* image, std::string name, std::string namespaze = "") -> MonoClass*;
		static auto Mono_GetClassName(MonoClass* klass) -> std::string;
		static auto Mono_GetClassNamespace(MonoClass* klass) -> std::string;
		static auto Mono_GetClassCount(MonoImage* Image) -> size_t;
		static auto Mono_GetClassParent(MonoClass* klass) -> MonoClass*;

		// Field (变量)
		static auto Mono_EnumFields(MonoClass* klass, std::vector<FieldInfo*>& Fields) -> size_t;
		static auto Mono_GetFieldFromName(MonoClass* klass, std::string name) -> FieldInfo*;
		static auto Mono_GetFieldStatic(FieldInfo* field, MonoClass* klass) -> DWORD_PTR;
		static auto Mono_GetFieldName(FieldInfo* field) -> std::string;
		static auto Mono_GetFieldType(FieldInfo* field) -> MonoType*;
		static auto Mono_GetFieldOffset(FieldInfo* field) -> size_t;

		// Method (函数)
		static auto Mono_EnumMethods(MonoClass* klass, std::vector<MethodInfo*>& Methods) -> size_t;
		static auto Mono_GetMethodFromName(MonoClass* klass, std::string name, DWORD argscount = -1) -> MethodInfo*;
		static auto Mono_GetMethodName(MethodInfo* Method) -> std::string;
		static auto Mono_GetMethodRetType(MethodInfo* Method) -> MonoType*;
		static auto Mono_GetMethodParamCount(MethodInfo* Method) -> size_t;
		static auto Mono_GetMethodParam(MethodInfo* Method, size_t index) -> MonoType*;
		static auto Mono_GetMethodParamName(MethodInfo* Method, size_t index) -> std::string;
		static auto Mono_GetMethodAddress(MethodInfo* method) -> DWORD_PTR;
		static auto Mono_GetMethodAddress(std::string klass, std::string Method, std::string Image = "",
		                                  std::string namespaze                                    = "") -> DWORD_PTR;

	private:
		static auto           GetFunc() -> void;
		inline static HMODULE hModuleMono = nullptr;

	public:
#define DO_API(ret_type, name, args) \
using name##_t = ret_type(__cdecl *) args;\
inline static name##_t name = nullptr;
#include "MonoHackAPI.h"
#undef DO_API
	};
}
