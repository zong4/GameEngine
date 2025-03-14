add_requires("spdlog")

target("engine")
    set_kind("shared")
    add_files("src/**.cpp")

    -- open engine.hpp
    add_includedirs("include", {public=true})

    add_packages("spdlog", {public=true})
