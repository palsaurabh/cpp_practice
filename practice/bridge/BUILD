cc_binary(
    name="adapter_ex",
    srcs=glob(["app/*.cpp"]),
    copts=["-Iadapter/include"],
    deps=[
        ":adapter_ex_lib",
    ],
)

cc_library(
    name="adapter_ex_lib",
    srcs=glob(["lib/*.cpp"]),
    hdrs=glob(["include/*.hpp"]),
    copts=["-Iadapter/include"],
    visibility=["//visibility:public"],
)

