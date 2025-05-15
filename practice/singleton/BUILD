cc_binary(
    name="singleton_ex",
    srcs=glob(["app/*.cpp"]),
    copts=["-Isingleton/include"],
    deps=[
        ":singleton_ex_lib",
    ],
)

cc_library(
    name="singleton_ex_lib",
    srcs=glob(["lib/*.cpp"]),
    hdrs=glob(["include/*.hpp"]),
    copts=["-Isingleton/include"],
    visibility=["//visibility:public"],
)

