# Barycentric Coordinates

A demonstration of barycentric coordinates.

## Settings
Several settings can be found in *src/settings.h*.

## Build
1. `cmake -S . -B output-path`
2. `cmake --build output-path`

Requires an C++ compiler, which can be set with `-G`:
* `cmake -S . -B output-path -G "Visual Studio 17 2022"`

The executable can be found at '*output-path/Debug/Computergraphik.exe*'.

## Controls
| Input | Description |
|---|---|
| Left Mouse | Moves the nearest point. |
| Shift + Left Mouse | Changes the rotation. |
| Key 'S' | Toggles the settings menu. |
| Key 'L' | Toggles the isolines. |
| Key 'N' | Toggles the vertex names. |
| Key 'I' | Toggles whether the point can only be inside the triangle. |

## Quellen
* Icon: [A. F. Möbius](https://www.portraitindex.de/documents/obj/33213645)
