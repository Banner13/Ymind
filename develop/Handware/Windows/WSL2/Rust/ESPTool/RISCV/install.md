```bash
$ rustup toolchain install nightly --component rust-src
info: syncing channel updates for 'nightly-x86_64-unknown-linux-gnu'
740.1 KiB / 740.1 KiB (100 %) 472.6 KiB/s in  1s ETA:  0s
info: latest update on 2024-02-22, rust version 1.78.0-nightly (3406ada96 2024-02-21)
info: downloading component 'cargo'
  8.4 MiB /   8.4 MiB (100 %) 477.5 KiB/s in 19s ETA:  0s
......
info: checking for self-update
```


```bash
$ cargo install espup
......
error: failed to compile `espup v0.11.0`, intermediate artifacts can be found at `/tmp/cargo-installt97Ka6`.
To reuse those artifacts with a future compilation, set the environment variable `CARGO_TARGET_DIR` to that path.
# please see error.md.
```


```bash
$ cargo install espup --locked cargo
......
Installing /home/goodwe/.cargo/bin/espup
   Installed package `espup v0.11.0` (executable `espup`)
     Summary Successfully installed espup! Failed to install cargo (see error(s) above).
error: some crates failed to install
# please see error.md.
```


```bash
$ espup install
[info]: Installing the Espressif Rust ecosystem
......
[info]: Installation successfully completed!

        To get started, you need to set up some environment variables by running: '. /home/goodwe/export-esp.sh'
        This step must be done every time you open a new terminal.
            See other methods for setting the environment in https://esp-rs.github.io/book/installation/riscv-and-xtensa.html#3-set-up-the-environment-variables
```

#### Ref
[[WSL1/Rust/ESPTool/RISCV/error|install error]]
