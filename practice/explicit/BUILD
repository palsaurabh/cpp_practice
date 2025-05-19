cc_binary(
    name="explicit_ex",
    srcs=glob(["app/*.cpp"]),
    copts=["-Iexplicit/include"],
    deps=[
        ":explicit_lib",
    ],
)

cc_library(
    name="explicit_lib",
    srcs=glob(["lib/*.cpp"]),
    hdrs=glob(["include/*.hpp"]),
    copts=["-Iexplicit/include"],
    visibility=["//visibility:public"],
)

