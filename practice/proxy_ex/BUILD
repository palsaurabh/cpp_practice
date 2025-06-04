cc_binary(
    name="proxy_ex",
    srcs=glob(["app/*.cpp"]),
    copts=["-Iproxy_ex/include"],
    deps=[
        ":proxy_ex_lib",
    ],
)

cc_library(
    name="proxy_ex_lib",
    srcs=glob(["lib/*.cpp"]),
    hdrs=glob(["include/*.hpp"]),
    copts=["-Iproxy_ex/include"],
    visibility=["//visibility:public"],
)

