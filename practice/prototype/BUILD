cc_binary(
    name="prototype_ex",
    srcs=glob(["app/*.cpp"]),
    copts=["-Iprototype/include"],
    deps=[
        ":prototype_ex_lib",
    ],
)

cc_library(
    name="prototype_ex_lib",
    srcs=glob(["lib/*.cpp"]),
    hdrs=glob(["include/*.hpp"]),
    copts=["-Iprototype/include"],
    visibility=["//visibility:public"],
)

