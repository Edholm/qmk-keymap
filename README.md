# qmk-keymap
This is my [qmk](https://qmk.fm/) for my [Kinesis Advantage2](https://kinesis-ergo.com/keyboards/advantage2-keyboard/) that has been modded with 
[Stapelberg's kint mod](https://github.com/kinx-project/kint). 

_I used the Teensy 4.1 controller for my mod, which requires changes to the qmk-firmware that hasn't been merged upstream (at the time of writing this)_

## Requirements
* [qmk-firmware](https://github.com/kinx-project/kint)
* `qmk` ([Python CLI tool](https://archlinux.org/packages/community/any/qmk/))
* `teensy_loader_cli` (You will probably need to compile it from [src](https://aur.archlinux.org/packages/teensy-loader-cli-git/). The 2.1 version doesn't support the `TEENSY41` mcu. Check with `teensy_loader_cli --list-mcus`)
* Build requirements:
  * arm-none-eabi-gcc  (`brew install gcc-arm-embedded` on macos, included in `qmk` dependencies on arch)

## How to use
These steps will guide you to building qmk with this keymap and flashing it to a kint modded Advantage2.

### 0. Clone repos
Clone this repo and your qmk-firmware of choice to a convenient location

### 1. Setup keymap
It is probably easiest to hardlink this repo to your qmk-firmware of choice:
```shell
mkdir -p <path-to-qmk-firmware>/keyboards/kinesis/keymaps/<name>
ln ./qmk-keymap/* <path-to-qmk-firmware>/keyboards/kinesis/keymaps/<name>/
```

Replace <name> with whatever you want to call the keymap

### 2. Compile qmk-firmware
```shell
cd <path-to-qmk-firmware>/
git submodule update --init --recursive
qmk compile --clean --keymap <name> --keyboard kinesis/kint41
```

### 3. Flash firmware
Click the reset button either physically on the controller or if you've already flashed qmk, you can press the reset key (if you have mapped it)
```shell
teensy_loader_cli -w -v --mcu=TEENSY41 .build/kinesis_kint41_<name>.hex
```

### Alternative way
You can also use the provided `Makefile`:
```shell
make compile
make flash
```
