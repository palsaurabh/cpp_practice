cc_binary(
    name="plugin_ex",
    srcs=glob(["main/*.cpp"]),
    deps=["plugin_interface"],
)

cc_library(
    name="plugin_interface",
    hdrs=glob(["include/*.hpp"]),
    includes=["include"],
    visibility=["//visibility:public"],
)

cc_library(
    name="plugin1_lib",
    srcs=glob(["plugin1/*.cpp"]),
    deps=["plugin_interface"],
    visibility=["//visibility:public"],
)
