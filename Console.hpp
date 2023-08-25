#pragma once
#include <Windows.h>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include "./fmt/printf.h"
#define LOG_DEBUG(text, ...) Console::OutConsole(Console::debug,text,__FILE__,__LINE__, __VA_ARGS__)
#define LOG_INFO(text, ...) Console::OutConsole(Console::info,text,__FILE__,__LINE__, __VA_ARGS__)
#define LOG_WARNING(text, ...) Console::OutConsole(Console::warning,text,__FILE__,__LINE__, __VA_ARGS__)
#define LOG_ERROR(text, ...) Console::OutConsole(Console::error,text,__FILE__,__LINE__, __VA_ARGS__)
namespace Console {
	enum OutType : short int {
		info,
		debug,
		warning,
		error
	};
	enum Color : short int {
		black,
		blue,
		green,
		LightGreen,
		red,
		purple,
		yellow,
		white,
		grey,
		LightBlue,
		thinGreen,
		LightLightGreen,
		LightRed,
		lavender,
		canaryYellow,
		BrightWhite
	};
	template<typename... Args>
	void OutConsole(OutType type, const std::string& text, const std::string& file, int line, Args... args) {
		const HANDLE hWnd_ = GetStdHandle(STD_OUTPUT_HANDLE);
		switch (type)
		{
		case OutType::info:
			SetConsoleTextAttribute(hWnd_, BACKGROUND_INTENSITY | green * 16);
			fmt::printf(" ");
			SetConsoleTextAttribute(hWnd_, BACKGROUND_INTENSITY | black);
			SetConsoleTextAttribute(hWnd_, FOREGROUND_INTENSITY | white);
			fmt::printf("[");
			SetConsoleTextAttribute(hWnd_, FOREGROUND_INTENSITY | green);
			fmt::printf("Info ");
			break;
		case OutType::debug:
			SetConsoleTextAttribute(hWnd_, BACKGROUND_INTENSITY | blue * 16);
			fmt::printf(" ");
			SetConsoleTextAttribute(hWnd_, BACKGROUND_INTENSITY | black);
			SetConsoleTextAttribute(hWnd_, FOREGROUND_INTENSITY | white);
			fmt::printf("[");
			SetConsoleTextAttribute(hWnd_, FOREGROUND_INTENSITY | blue);
			fmt::printf("Debug");
			break;
		case OutType::warning:
			SetConsoleTextAttribute(hWnd_, BACKGROUND_INTENSITY | yellow * 16);
			fmt::printf(" ");
			SetConsoleTextAttribute(hWnd_, BACKGROUND_INTENSITY | black);
			SetConsoleTextAttribute(hWnd_, FOREGROUND_INTENSITY | white);
			fmt::printf("[");
			SetConsoleTextAttribute(hWnd_, FOREGROUND_INTENSITY | yellow);
			fmt::printf("Warn ");
			break;
		case OutType::error:
			SetConsoleTextAttribute(hWnd_, BACKGROUND_INTENSITY | red * 16);
			fmt::printf(" ");
			SetConsoleTextAttribute(hWnd_, BACKGROUND_INTENSITY | black);
			SetConsoleTextAttribute(hWnd_, FOREGROUND_INTENSITY | white);
			fmt::printf("[");
			SetConsoleTextAttribute(hWnd_, FOREGROUND_INTENSITY | red);
			fmt::printf("Error");
			break;
		}
		SetConsoleTextAttribute(hWnd_, FOREGROUND_INTENSITY | white);
		fmt::printf("]>[");
		SetConsoleTextAttribute(hWnd_, FOREGROUND_INTENSITY | purple);
		fmt::printf("%s:%i", file.substr(file.find_last_of('\\') + 1).c_str(), line);
		SetConsoleTextAttribute(hWnd_, FOREGROUND_INTENSITY | white);
		fmt::printf("] :%s", fmt::format(text, args...));
	}
	HWND StartConsole(const wchar_t* title, bool close) {
		HWND hWnd_ = nullptr;
		AllocConsole();
		SetConsoleTitle(title);
		while (nullptr == hWnd_) hWnd_ = ::FindWindow(nullptr, title);
		const HMENU menu_ = ::GetSystemMenu(hWnd_, FALSE);
		if (!close) { DeleteMenu(menu_, SC_CLOSE, MF_BYCOMMAND); }
		SetWindowLong(hWnd_, GWL_STYLE, GetWindowLong(hWnd_, GWL_STYLE) & ~WS_MAXIMIZEBOX);
		SetWindowLong(hWnd_, GWL_STYLE, GetWindowLong(hWnd_, GWL_STYLE) & ~WS_THICKFRAME);
		SetWindowPos(hWnd_, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
		freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w+", stdout);
		freopen_s(reinterpret_cast<FILE**>(stderr), "CONOUT$", "w+", stderr);
		freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r+", stderr);
		std::ofstream(stdout) <<
			R"(      ___           ___                       ___           ___                    ___       ___           ___     )"
			R"(     /\  \         /\__\          ___        /\__\         /\  \                  /\__\     /\  \         /\  \    )"
			R"(    /::\  \       /:/  /         /\  \      /::|  |       /::\  \                /:/  /    /::\  \       /::\  \   )"
			R"(   /:/\ \  \     /:/  /          \:\  \    /:|:|  |      /:/\:\  \              /:/  /    /:/\:\  \     /:/\:\  \  )"
			R"(  _\:\~\ \  \   /:/  /  ___      /::\__\  /:/|:|__|__   /:/  \:\  \            /:/  /    /:/  \:\  \   /:/  \:\  \ )"
			R"( /\ \:\ \ \__\ /:/__/  /\__\  __/:/\/__/ /:/ |::::\__\ /:/__/ \:\__\          /:/__/    /:/__/ \:\__\ /:/__/_\:\__\)"
			R"( \:\ \:\ \/__/ \:\  \ /:/  / /\/:/  /    \/__/~~/:/  / \:\  \ /:/  /          \:\  \    \:\  \ /:/  / \:\  /\ \/__/)"
			R"(  \:\ \:\__\    \:\  /:/  /  \::/__/           /:/  /   \:\  /:/  /            \:\  \    \:\  /:/  /   \:\ \:\__\  )"
			R"(   \:\/:/  /     \:\/:/  /    \:\__\          /:/  /     \:\/:/  /              \:\  \    \:\/:/  /     \:\/:/  /  )"
			R"(    \::/  /       \::/  /      \/__/         /:/  /       \::/  /                \:\__\    \::/  /       \::/  /   )"
			R"(     \/__/         \/__/                     \/__/         \/__/                  \/__/     \/__/         \/__/    )"
			R"(                                                                                                                   )"
			R"(===================================================================================================================)";
		return hWnd_;
	}
	void EndConsole() {
		fclose(stdout);
		fclose(stderr);
		fclose(stdin);
		FreeConsole();
	}
}