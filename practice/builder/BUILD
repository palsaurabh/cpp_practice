cc_binary(
    name="builder_ex",
    srcs=glob(["app/*.cpp"]),
    copts=["-Ibuilder/include"],
    deps=[
        ":builder_ex_lib",
    ],
)

cc_library(
    name="builder_ex_lib",
    srcs=glob(["lib/*.cpp"]),
    hdrs=glob(["include/*.hpp"]),
    copts=["-Ibuilder/include"],
    visibility=["//visibility:public"],
)

