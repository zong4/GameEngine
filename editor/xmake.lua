target("editor")
    set_kind("binary")
    add_files("src/**.cpp")

    add_deps("engine")