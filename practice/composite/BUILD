cc_binary(
    name="composite_ex",
    srcs=glob(["app/*.cpp"]),
    copts=["-Icomposite/include"],
    deps=[
        ":composite_ex_lib",
    ],
)

cc_library(
    name="composite_ex_lib",
    srcs=glob(["lib/*.cpp"]),
    hdrs=glob(["include/*.hpp"]),
    copts=["-Icomposite/include"],
    visibility=["//visibility:public"],
)

