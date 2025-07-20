cc_binary(
    name="strategy_ex",
    srcs=glob(["app/*.cpp"]),
    copts=["-Istrategy/include"],
    deps=[
        ":strategy_ex_lib",
    ],
)

cc_library(
    name="strategy_ex_lib",
    srcs=glob(["lib/*.cpp"]),
    hdrs=glob(["include/*.hpp"]),
    copts=["-Istrategy/include"],
    visibility=["//visibility:public"],
)

