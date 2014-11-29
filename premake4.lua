--[[
    MouseHide for AltDvb 2.2 in FullScreen Mode

    Copyright (C) 2014 Daniel Rodriguez

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
--]]

--[[
 AltDvb 2.2 does only hide the mouse once after going in Fullscreen mode,
 leaving the mouse on if it's moved afterwards, forcing the user to hide the
 mouse

 The application will move the pointer offscreen if AltDvb is running in
 fullscreen mode
--]]

function newplatform(plf)
    local name = plf.name
    local description = plf.description
 
    -- Register new platform
    premake.platforms[name] = {
        cfgsuffix = "_"..name,
        iscrosscompiler = false
    }
 
    -- Allow use of new platform in --platforms
    table.insert(premake.option.list["platform"].allowed, { name, description })
    table.insert(premake.fields.platforms.allowed, name)
 
    -- Add compiler support
    -- gcc
    premake.gcc.platforms[name] = plf.gcc
    --other compilers (?)
end
 
function newgcctoolchain(toolchain)
    newplatform {
        name = toolchain.name,
        description = toolchain.description,
        gcc = {
            cc = toolchain.prefix .. "gcc",
            cxx = toolchain.prefix .. "g++",
            ar = toolchain.prefix .. "ar",
            -- cppflags = "-MMD " .. toolchain.cppflags
            cppflags = toolchain.cppflags
        }
    }
end

newgcctoolchain {
    name = "w32",
    description = "mingw-w64 32bits",
    prefix = "i686-w64-mingw32-",
    cppflags = ""
}

newgcctoolchain {
    name = "w64",
    description = "mingw-w64 64bits",
    prefix = "x86_64-w64-mingw32-",
    cppflags = ""
}

solution "mousehide"
  language "C++"
  buildoptions { "-std=gnu++11" }
  platforms { "w32" }

  configurations { "debug", "release" }
  targetdir "bin"
  includedirs { "./src/include" }

  project "mousehide"
    kind "SharedLib"
    objdir "obj/lib"

    files {
      "main.cpp",
      "moushide.hpp", "mousehide.cpp",
      "mdextern.hpp", "mdextern.cpp"
    }

    defines { "BUILDING_DLL" }
    flags { "ExtraWarnings" }
