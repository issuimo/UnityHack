# 如何使用
> [!WARNING]\
> 头文件可能依赖于mkl库 如缺失请手动删除mkl使用的代码片段或者安装intel oneapi c++编译器
> ``` c++
> #include <mkl.h>
> // ...
> inline auto distance(const std::vector<Vector3>& events) const -> std::vector<float> {
>   // ...
> }
> inline auto distance(const std::vector<Vector2>& events) const -> std::vector<float> {
>   // ...
> }
> ```

> [!NOTE]\
> il2cpp使用的是 崩坏：星穹铁道 (StarRail) GameAssembly.dll导出函数列表，不同版本的Unity不同游戏导出列表略有差异

> [!IMPORTANT]\
> 使用示范 [ravenfield](https://github.com/issuimo/ravenfield)

- 引入头文件
``` c++
#include "UnityHack.h"
```

- 初始化dll地址
``` c++
// 初始化Mono
unity::Mono::SetModule(GetModuleHandleA("mono-2.0-bdwgc.dll"));

// 初始化il2cpp
unity::Il2cpp::SetModule(GetModuleHandleA("GameAssembly.dll"));
```

- 获取函数地址
``` c++
// Mono
unity::Mono::Method::GetAddress("Actor", "Awake");

// Il2cpp
unity::Il2cpp::Method::GetAddress("Actor", "Awake");
```
