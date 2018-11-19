# V8ForAndroid
V8 build setting for android (arm, arm64, x86) on Linux (Ubuntu).


### set dependencies (on Linux:ubuntu)

1. get depot tools [more](https://www.chromium.org/developers/how-tos/install-depot-tools) :
```
git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git

export PATH=`pwd`/depot_tools:"$PATH"
```  
  
2. make sure you have these packages installed (Linux only)
```
sudo apt-get install curl libc6-dev-i386 g++-multilib
```

### build v8

1. install v8 (checkout version)
```
fetch v8
cd v8
git pull
git checkout <v8_version>
```

2. download android tools
```
echo "target_os = ['android']" >> ../.gclient && gclient sync
```

3. check v8gen.py list
```
tools/dev/v8gen.py list
```
> may be list up `arm.debug, arm.optdebug arm.release, arm64.debug...`

6. generate compilation target
```
tools/dev/v8gen.py gen <one_of_list>
```

4. change `out.gn/<one_of_list>/args.gn`
```
vi out.gn/<one_of_list>/args.gn
```
> example :
```
args.gn file

v8_use_snapshot = true
v8_use_external_startup_data = false
is_official_build = true
is_debug = false
symbol_level = 0
target_cpu = "arm"
v8_target_cpu = "arm"
v8_enable_i18n_support = false
target_os = "android"
v8_android_log_stdout = true
```

5. execute ninja command for build
```
ninja -C out.gn/<one_of_list> -j 4
```
