load("@bazel_skylib//:bzl_library.bzl", "bzl_library")
load("//transpiler/rust:fhe_rs.bzl", "fhe_rust_library")
load("@rules_rust//rust:defs.bzl", "rust_binary", "rust_library", "rust_test")

licenses(["notice"])

fhe_rust_library(
    name = "chickens_rs_fhe_lib",
    lut_size = 0,
    src = "chickens.cc",
    hdrs = ["chickens.h"],
)

rust_library(
    name = "chickens_rs_lib",
    srcs = ["chickens_rs_lib.rs"],
    deps = [
        ":chickens_rs_fhe_lib",
        "@crate_index//:phantom-zone",
    ],
)

rust_binary(
    name = "chickens_rs_main",
    srcs = ["chickens_rs_lib.rs"],
    deps = [
        ":chickens_rs_fhe_lib",
        "@crate_index//:phantom-zone",
    ],
)

exports_files(
    [
        "chickens.h",
        "chickens.cc",
    ],
)
