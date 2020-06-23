
Example using bazel  to build cpprestsdk and its dependencies (boost, openssl, etc)

#### Usage
```
bazel run //example-http-client:example
```

The initial build takes ~ 5000 seconds! I use rules_foreign_cc's cmake, boost, and configure_make rules to build openssl,
boost, and cpprestsdk. You do not need cmake installed as that is built from source as well and added to the toolchain.

Note I suspect the boost_build rules are leaking the build host's openssl library into the built target. I had to upgrade my
system's (Ubuntu 18.04) libssl-dev to 1.1.1 to avoid openssl "undefined reference" errors, even though this example builds openssl
as a static library.
