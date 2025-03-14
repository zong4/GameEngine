add_requires("spdlog")
add_requires("glfw")

target("Engine")
    set_kind("shared")
    add_files("src/**.cpp")

    -- open engine.hpp
    add_includedirs("include", {public=true})

    add_packages("spdlog", {public=true})
    add_packages("glfw", {public=true})
