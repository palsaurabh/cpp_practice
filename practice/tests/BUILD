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

cc_test(
    name = "builder_ex_test",
    srcs = ["builder_ex_test.cpp"],
    copts= ["-Ibuilder/include",],
    deps = [
        "@googletest//:gtest",
        "@googletest//:gtest_main",
        "//builder:builder_ex_lib",
    ],
)

cc_test(
    name = "prototype_ex_test",
    srcs = ["prototype_ex_test.cpp"],
    copts= ["-Iprototype/include",],
    deps = [
        "@googletest//:gtest",
        "@googletest//:gtest_main",
        "//prototype:prototype_ex_lib",
    ],
)