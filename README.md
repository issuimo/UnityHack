> 2023/11/12 \
> 因难以维护问题已停止更新, 目前已转为UnityResolve.hpp开发 \
> Due to maintenance difficulties, updates have been discontinued. Currently, development has transitioned to UnityResolve.hpp. \
> [UnityResolve.hpp](https://github.com/issuimo/UnityResolve.hpp)

# 类型 (Type)
- [X] Camera
- [X] Transform
- [ ] GameObject
- [X] Component
- [ ] LayerMask
- [ ] Rigidbody
- [X] Vector4
- [X] Quaternion
- [X] Bounds
- [X] Plane
- [X] Ray
- [X] Rect
- [X] Color
- [X] Matrix4x4

# 如何使用 (Use)
> [!NOTE]\
> il2cpp使用的是 崩坏：星穹铁道 (StarRail) GameAssembly.dll导出函数列表，不同版本的Unity不同游戏导出列表略有差异\
> 部分特殊处理过的il2cpp无法使用 如: 原神 (Genshin Impact)

> [!IMPORTANT]\
> 使用示范
> ### Mono 
> - [ravenfield](https://github.com/issuimo/ravenfield)
> ### il2cpp
> - [Phasmophobia](https://github.com/issuimo/PhasmophobiaCheat)

- 引入头文件 (Import)
``` c++
#include "UnityHack.h"
```

- 初始化dll地址 (Initialization)
``` c++
// 初始化Mono
unity::Mono::SetModule(GetModuleHandleA("mono-2.0-bdwgc.dll"));

// 初始化il2cpp
unity::Il2cpp::SetModule(GetModuleHandleA("GameAssembly.dll"));
```

- 获取函数地址 (Obtaining Function Addresses)
``` c++
// Mono
unity::Mono::Method::GetAddress("Actor", "Awake");

// Il2cpp
unity::Il2cpp::Method::GetAddress("Actor", "Awake");
```
