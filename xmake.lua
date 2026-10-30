-- include subprojects
includes("lib/commonlibsf")

-- set project constants
set_project("StarfieldStrutNative")
set_version("0.0.0")
set_license("GPL-3.0")
set_languages("c++23")
set_warnings("allextra")

-- add common rules
add_rules("mode.debug", "mode.releasedbg")
add_rules("plugin.vsxmake.autoupdate")

-- define targets
target("StarfieldStrutNative")
    add_rules("commonlibsf.plugin", {
        name = "StarfieldStrutNative",
        author = "Orrerium Studios",
        description = "Starfield Strut native support",
        email = "user@site.com"
    })

    -- add src files
    add_files("src/**.cpp")
    add_headerfiles("src/**.h")
    add_includedirs("src")
    set_pcxxheader("src/pch.h")
