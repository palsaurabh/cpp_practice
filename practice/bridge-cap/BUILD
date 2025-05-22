cc_binary(
    name="bridge-cap_ex",
    srcs=glob(["app/*.cpp"]),
    copts=["-Ibridge-cap/include"],
    deps=[
        ":bridge-cap_ex_lib",
    ],
)

cc_library(
    name="bridge-cap_ex_lib",
    srcs=glob(["lib/*.cpp"]),
    hdrs=glob(["include/*.hpp"]),
    copts=["-Ibridge-cap/include"],
    visibility=["//visibility:public"],
)

