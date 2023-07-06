#include "MonoHack.h"
#include <format>
#include <fstream>
#include <iostream>
#include <sstream>

namespace Unity3D {
	auto vecpush(void* ptr, std::vector<DWORD_PTR>& v) -> void {
		v.push_back((DWORD_PTR)ptr);
	}

	auto MonoCollector::SetModule(HMODULE Module) -> void {
		hModuleMono = Module;

		if (!hModuleMono)
			MessageBox(nullptr, L"Can not find Module", L"error", NULL);
		GetFunc();
	}

	auto MonoCollector::GetFunc() -> void {
		#define DO_API(ret_type, name, args ) \
		name = reinterpret_cast<name##_t>(GetProcAddress(hModuleMono, #name));
		#include "MonoHackAPI.h"
		#undef DO_API
		if (mono_thread_attach)
			if (mono_get_root_domain) {
				auto domain = mono_get_root_domain();
				mono_thread_attach(domain);
			}
		if (il2cpp_thread_attach)
			il2cpp_thread_attach(il2cpp_domain_get());
	}

	template <typename T>
	auto MonoCollector::il2cpp_GetStaticClass(Il2CppClass* klass) -> T* {
		return reinterpret_cast<T*>(il2cpp_class_get_static_field_data(klass));
	}

	auto MonoCollector::Mono_GetClassParent(MonoClass* klass) -> MonoClass* {
		return mono_class_get_parent(klass);
	}

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
				str << std::format("// Namespace: {}\npublic class {}\n", Mono_GetClassNamespace(classes[i_c]),
				                   Mono_GetClassName(classes[i_c])) << "{\n\t// Fields" << std::endl;
				str2 << std::format("struct {}\n", Mono_GetClassName(classes[i_c])) << "{" << std::endl;

				std::vector<FieldInfo*> Field;
				for (size_t i_f = 0, max_f = Mono_EnumFields(classes[i_c], Field); i_f < max_f; i_f++) {
					auto           Typename          = Mono_GetTypeName(Mono_GetFieldType(Field[i_f]));
					constexpr auto STATIC_FIELD_MASK = 0x00000002; // 第2位代表字段是否静态的掩码
					auto           fieldFlags        = mono_field_get_flags((MonoType*)Field[i_f]);
					str << std::format("\tpublic {} {} {}; // {:#X}",
					                   (fieldFlags & STATIC_FIELD_MASK) != 0 ? "static" : "", Typename,
					                   Mono_GetFieldName(Field[i_f]), Mono_GetFieldOffset(Field[i_f])) << std::endl;
					str2 << std::format("\t{} {}; // {:#X}", Typename, Mono_GetFieldName(Field[i_f]),
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
					str << std::format("\tpublic {} {} {}(", (methodFlags & STATIC_METHOD_MASK) != 0 ? "static" : "",
					                   retTypename, Mono_GetMethodName(Methods[i_m]));
					str3 << std::format("DO_API({}, {}_{}, (", retTypename, Mono_GetClassName(classes[i_c]),
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

	auto MonoCollector::Mono_GetMethodAddress(std::string klass, std::string Method, std::string Image,
	                                          std::string namespaze) -> DWORD_PTR {
		std::vector<MonoAssembly*> Assemblys;
		Mono_EnummAssembly(Assemblys);
		for (size_t i = 0, max = Assemblys.size(); i < max; i++) {
			//判断是否在镜像内
			auto image = Mono_GetImage(Assemblys[i]);
			if (Image != "")
				if (Mono_GetImageName(image) != Image)
					continue;

			//枚举类
			std::vector<MonoClass*> classes;
			Mono_EnumClasses(image, classes);
			for (size_t i_c = 0, max_c = classes.size(); i_c < max_c; i_c++) {
				//判断空间命名是否相等
				if (namespaze != "")
					if (Mono_GetClassNamespace(classes[i_c]) != namespaze)
						continue;

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
		return *reinterpret_cast<DWORD_PTR*>(method);
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

	auto MonoCollector::Mono_GetMethodName(MethodInfo* Method) -> std::string {
		return mono_method_get_name(Method);
	}

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

	auto MonoCollector::Mono_GetFieldOffset(FieldInfo* field) -> size_t {
		return mono_field_get_offset(field);
	}

	auto MonoCollector::Mono_GetFieldType(FieldInfo* field) -> MonoType* {
		return mono_field_get_type(field);
	}

	auto MonoCollector::Mono_GetFieldName(FieldInfo* field) -> std::string {
		return mono_field_get_name(field);
	}

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

	auto MonoCollector::Mono_GetClassName(MonoClass* klass) -> std::string {
		return mono_class_get_name(klass);
	}

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

	auto MonoCollector::Mono_GetImageName(MonoImage* Image) -> std::string {
		return mono_image_get_name(Image);
	}

	auto MonoCollector::Mono_GetImageFile(MonoImage* Image) -> std::string {
		return mono_image_get_filename(Image);
	}

	auto MonoCollector::Mono_GetClassCount(MonoImage* Image) -> size_t {
		auto tdef = mono_image_get_table_info(Image, MONO_TABLE_TYPEDEF);
		return mono_table_info_get_rows(tdef);
	}

	auto MonoCollector::Mono_GetTypeName(MonoType* type) -> std::string {
		return mono_type_get_name(type);
	}

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
				str << std::format("// Namespace: {}\npublic class {}\n", il2cpp_GetClassNamespace(classes[i_c]),
				                   il2cpp_GetClassName(classes[i_c])) << "{\n\t// Fields" << std::endl;
				str2 << std::format("struct {}\n", il2cpp_GetClassName(classes[i_c])) << "{" << std::endl;

				std::vector<FieldInfo*> Field;
				for (size_t i_f = 0, max_f = il2cpp_EnumFields(classes[i_c], Field); i_f < max_f; i_f++) {
					auto           Typename          = il2cpp_GetTypeName(il2cpp_GetFieldType(Field[i_f]));
					constexpr auto STATIC_FIELD_MASK = 0x00000002; // 第2位代表字段是否静态的掩码
					auto           fieldFlags        = il2cpp_field_get_flags(Field[i_f]);
					str << std::format("\tpublic {} {} {}; // {:#X}",
					                   (fieldFlags & STATIC_FIELD_MASK) != 0 ? "static" : "", Typename,
					                   il2cpp_GetFieldName(Field[i_f]), il2cpp_GetFieldOffset(Field[i_f])) << std::endl;
					str2 << std::format("\t{} {}; // {:#X}", Typename, il2cpp_GetFieldName(Field[i_f]),
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
					str << std::format("\tpublic {} {} {}(", (methodFlags & STATIC_METHOD_MASK) != 0 ? "static" : "",
					                   retTypename, il2cpp_GetMethodName(Methods[i_m]));
					str3 << std::format("DO_API({}, {}_{}, (", retTypename, il2cpp_GetClassName(classes[i_c]),
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

	auto MonoCollector::il2cpp_GetFieldOffset(FieldInfo* field) -> size_t {
		return il2cpp_field_get_offset(field);
	}

	auto MonoCollector::il2cpp_GetMethodAddress(std::string klass, std::string Method, std::string Image,
	                                            std::string namespaze) -> DWORD_PTR {
		std::vector<Il2CppAssembly*> Assemblys;
		il2cpp_EnummAssembly(Assemblys);
		for (size_t i = 0, max = Assemblys.size(); i < max; i++) {
			//判断是否在镜像内
			auto image = il2cpp_GetImage(Assemblys[i]);
			if (Image != "")
				if (il2cpp_GetImageName(image) != Image)
					continue;

			//枚举类
			std::vector<Il2CppClass*> classes;
			il2cpp_EnumClasses(image, classes);
			for (size_t i_c = 0, max_c = classes.size(); i_c < max_c; i_c++) {
				//判断空间命名是否相等
				if (namespaze != "")
					if (il2cpp_GetClassNamespace(classes[i_c]) != namespaze)
						continue;

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

	auto MonoCollector::il2cpp_GetTypeName(Il2CppType* type) -> std::string {
		return il2cpp_type_get_name(type);
	}

	auto MonoCollector::il2cpp_GetFieldName(FieldInfo* field) -> std::string {
		return il2cpp_field_get_name(field);
	}

	auto MonoCollector::il2cpp_GetClassName(Il2CppClass* klass) -> std::string {
		return il2cpp_class_get_name(klass);
	}

	auto MonoCollector::il2cpp_GetClassFromName(Il2CppImage* image, std::string name,
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

	auto MonoCollector::il2cpp_GetImageName(Il2CppImage* Image) -> std::string {
		return il2cpp_image_get_name(Image);
	}

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
