target("Editor")
    add_headerfiles("src/**.hpp")
    add_files("src/**.cpp")

    add_includedirs("assets")

    add_deps("Engine")

    if is_plat("windows") then
        add_ldflags("/SUBSYSTEM:CONSOLE")
        add_ldflags("/WHOLEARCHIVE:Engine.lib", {force=true})
    end