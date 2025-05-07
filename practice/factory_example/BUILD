cc_binary(
    name="factory_ex",
    srcs=["factory_ex.cpp"],
)

cc_test(
    name = "factory_ex_test",
    srcs = ["factory_ex_test.cpp"],
    deps = [
        "libgtest.a",
        "libgtest_main.a",
        ":factory_example",
    ],
)