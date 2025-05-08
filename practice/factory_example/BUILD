cc_binary(
    name="factory_ex",
    srcs=["factory_ex.cpp"],
    deps=[
        ":factory_ex_lib",
    ],
)

cc_library(
    name="factory_ex_lib",
    srcs=["factory_ex_lib.cpp"],
    hdrs=["factory_ex.hpp"],
    visibility=["//visibility:public"],
)

cc_test(
    name = "factory_ex_test",
    srcs = ["factory_ex_test.cpp"],
    deps = [
        "@googletest//:gtest",
        "@googletest//:gtest_main",
        ":factory_ex_lib",
    ],
)