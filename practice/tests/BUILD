cc_test(
    name = "factory_ex_test",
    srcs = ["factory_ex_test.cpp"],
    copts= ["-Ifactory_example/include",],
    deps = [
        "@googletest//:gtest",
        "@googletest//:gtest_main",
        "//factory_example:factory_ex_lib",
    ],
)