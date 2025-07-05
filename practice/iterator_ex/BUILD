cc_binary(
    name="iterator_ex",
    srcs=glob(["app/*.cpp"]),
    copts=["-Iiterator_ex/include -g3"],
    deps=[
        ":iterator_ex_lib",
    ],
)

cc_library(
    name="iterator_ex_lib",
    srcs=glob(["lib/*.cpp"]),
    hdrs=glob(["include/*.hpp"]),
    copts=["-Iiterator_ex/include -g3"],
    visibility=["//visibility:public"],
)

