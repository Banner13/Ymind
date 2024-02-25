```bash
$ cargo install cargo-generate
  ......
run pkg_config fail: Could not run `PKG_CONFIG_ALLOW_SYSTEM_CFLAGS=1 pkg-config --libs --cflags openssl`
  The pkg-config command could not be found.
# please see error.md.

# slove
$ sudo apt install pkg-config

$ cargo install cargo-generate
  ......
  Compiling cargo-generate v0.19.0
      Finished release [optimized] target(s) in 2m 50s
    Installing /home/goodwe/.cargo/bin/cargo-generate
     Installed package `cargo-generate v0.19.0` (executable `cargo-generate`)
```
