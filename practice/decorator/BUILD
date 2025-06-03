cc_binary(
    name="decorator_ex",
    srcs=glob(["app/*.cpp"]),
    copts=["-Idecorator/include"],
    deps=[
        ":decorator_ex_lib",
    ],
)

cc_library(
    name="decorator_ex_lib",
    srcs=glob(["lib/*.cpp"]),
    hdrs=glob(["include/*.hpp"]),
    copts=["-Idecorator/include"],
    visibility=["//visibility:public"],
)

