load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")
load("@io_bazel_rules_docker//cc:image.bzl", "cc_image")

cmake_external(
    name = "cpprestsdk",
    cache_entries = {
        "CPPREST_EXCLUDE_WEBSOCKETS": "ON",
        "CPPREST_EXCLUDE_COMPRESSION": "ON",
        "BUILD_SHARED_LIBS": "OFF",
    },
    lib_source = "@cpprestsdk//:all",
    static_libraries = ["libcpprest.a"],
    deps = [
        "//third_party/boost:boost_atomic",
        "//third_party/boost:boost_chrono",
        "//third_party/boost:boost_date_time",
        "//third_party/boost:boost_filesystem",
        "//third_party/boost:boost_random",
        "//third_party/boost:boost_regex",
        "//third_party/boost:boost_system",
        "//third_party/boost:boost_thread",
        "//third_party/openssl",
    ],
)

cc_binary(
    name = "example",
    srcs = ["example.cc"],
    linkopts = [
        "-pthread",
        "-ldl",
    ],
    deps = [
        ":cpprestsdk",
    ],
)
