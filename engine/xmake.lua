add_requires("spdlog")
add_requires("glfw")

target("Engine")
    set_kind("shared")
    add_files("src/**.cpp")

    add_includedirs("include", {public=true})

    -- Core
    add_packages("spdlog", {public=true})
    add_packages("glfw", {public=true})

    -- Renderer
    add_frameworks("Metal")
