cc_binary(
    name="chainOfResponsibility_ex",
    srcs=glob(["app/*.cpp"]),
    copts=["-IchainOfResponsibility_ex/include"],
    deps=[
        ":chainOfResponsibility_ex_lib",
    ],
)

cc_library(
    name="chainOfResponsibility_ex_lib",
    srcs=glob(["lib/*.cpp"]),
    hdrs=glob(["include/*.hpp"]),
    copts=["-IchainOfResponsibility_ex/include"],
    visibility=["//visibility:public"],
)

