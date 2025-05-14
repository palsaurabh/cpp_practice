cc_binary(
    name="abstractfactory_ex",
    srcs=glob(["app/*.cpp"]),
    copts=["-Iabstractfactory/include"],
    deps=[
        ":abstractfactory_lib",
    ],
)

cc_library(
    name="abstractfactory_lib",
    srcs=glob(["lib/*.cpp"]),
    hdrs=glob(["include/*.hpp"]),
    copts=["-Iabstractfactory/include"],
    visibility=["//visibility:public"],
)