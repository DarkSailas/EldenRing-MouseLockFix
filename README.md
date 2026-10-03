# EldenRing-MouseLockFix

![Version](https://img.shields.io/badge/version-1.0.0-blue)
![Platform](https://img.shields.io/badge/platform-Windows%20x64-lightgrey)
![License](https://img.shields.io/badge/license-MIT-green)

[English](#english) | [Русский](#русский)

## English

A DLL mod for Elden Ring that keeps the mouse cursor inside the game window. In borderless and windowed modes the cursor can leave the window during camera movement, and the next click lands on a second monitor or the desktop and takes focus away from the game. This mod prevents that.

A background thread checks ten times a second whether the foreground window belongs to the game. If it does, the thread calls `ClipCursor` with the client area of that window. When you Alt+Tab or minimize the game, the cursor is released. The mod does not hook anything and does not touch game memory, so it does not depend on the game version.

> [!WARNING]
> DLL mods do not load with Easy Anti-Cheat running. Play offline with EAC disabled (Mod Engine and me3 do this for you), or use Seamless Co-op.

### Installation

Take `MouseLockFix.dll` and `MouseLockFix.ini` from the [`release`](release) folder.

**me3**: put both files into the `dll` folder of your mod and add the DLL to the profile:

```toml
[[natives]]
path = './../mod/dll/MouseLockFix.dll'
```

**Mod Engine 2**: add the DLL path to `external_dlls` in `config_eldenring.toml`.

**[Elden Mod Loader](https://www.nexusmods.com/eldenring/mods/117)**: put both files into `ELDEN RING\Game\mods`.

### Configuration

`MouseLockFix.ini` lives next to the DLL and is read once at startup. Without the file the mod is enabled.

| Section | Key | Default | Description |
| --- | --- | --- | --- |
| `[General]` | `Enabled` | `true` | `false` or `0` turns the mod off without removing the DLL |

### Building

MinGW-w64 g++ is required. From the repository root:

```powershell
.\build.ps1
```

The script compiles `src/dllmain.cpp` into a statically linked `MouseLockFix.dll`.

### License

MIT, see [LICENSE](LICENSE). Not affiliated with FromSoftware or Bandai Namco.

## Русский

DLL-мод для Elden Ring, который удерживает курсор мыши внутри окна игры. В режимах «Окно без рамки» и «Окно» курсор при повороте камеры может выйти за границы окна, и следующий клик попадает на второй монитор или рабочий стол — игра теряет фокус. Мод это исключает.

Фоновый поток десять раз в секунду проверяет, принадлежит ли активное окно игре. Если да, он вызывает `ClipCursor` с клиентской областью этого окна. При Alt+Tab или сворачивании игры курсор освобождается. Мод ничего не перехватывает и не трогает память игры, поэтому от версии игры не зависит.

> [!WARNING]
> С включённым Easy Anti-Cheat DLL-моды не загружаются. Играйте офлайн с отключённым EAC (Mod Engine и me3 делают это сами) или через Seamless Co-op.

### Установка

Возьмите `MouseLockFix.dll` и `MouseLockFix.ini` из папки [`release`](release).

**me3**: положите оба файла в папку `dll` вашего мода и добавьте DLL в профиль:

```toml
[[natives]]
path = './../mod/dll/MouseLockFix.dll'
```

**Mod Engine 2**: добавьте путь к DLL в `external_dlls` в `config_eldenring.toml`.

**[Elden Mod Loader](https://www.nexusmods.com/eldenring/mods/117)**: положите оба файла в `ELDEN RING\Game\mods`.

### Настройка

`MouseLockFix.ini` лежит рядом с DLL и читается один раз при запуске. Без файла мод включён.

| Секция | Ключ | По умолчанию | Описание |
| --- | --- | --- | --- |
| `[General]` | `Enabled` | `true` | `false` или `0` отключает мод без удаления DLL |

### Сборка

Нужен MinGW-w64 g++. Из корня репозитория:

```powershell
.\build.ps1
```

Скрипт собирает `src/dllmain.cpp` в статически слинкованный `MouseLockFix.dll`.

### Лицензия

MIT, см. [LICENSE](LICENSE). Проект не связан с FromSoftware и Bandai Namco.
