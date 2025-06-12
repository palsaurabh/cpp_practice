cc_binary(
    name="command_ex",
    srcs=glob(["app/*.cpp"]),
    copts=["-Icommand_ex/include"],
    deps=[
        ":command_ex_lib",
    ],
)

cc_library(
    name="command_ex_lib",
    srcs=glob(["lib/*.cpp"]),
    hdrs=glob(["include/*.hpp"]),
    copts=["-Icommand_ex/include"],
    visibility=["//visibility:public"],
)

