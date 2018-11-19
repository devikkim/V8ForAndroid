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

### compile v8

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

5. compile target
```
ninja -C out.gn/<one_of_list> -j 4
```

6. create lib files
```
cd out.gn/<one_of_list>/obj
mkdir libs
cd libs
ar -rcsD libv8_base.a ../v8_base/*.o
ar -rcsD libv8_base.a ../v8_libbase/*.o
ar -rcsD libv8_base.a ../v8_libsampler/*.o
ar -rcsD libv8_base.a ../v8_libplatform/*.o 
ar -rcsD libv8_base.a ../src/inspector/inspector/*.o
ar -rcsD libv8_snapshot.a ../v8_snapshot/*.o 
ar -rcsD libv8_nosnapshot.a ../v8_nosnapshot/*.o
ar -rcsD libv8_external_snapshot.a ../v8_external_snapshot/*.o
```
> Maybe not all of the above files are created. But it does not matter. Only the `libv8_base.a` and `libv8_nosnapshot.a` files need to be created.

7. source headers, for inspector compilation.
copy v8 compliation header files
```
mkdir -p src/base/platform
cp -R ../../../../src/*.h ./src
cp -R ../../../../src/base/*.h ./src/base
cp -R ../../../../src/base/platform/*.h ./src/base/platform
cp -R ../../../../include ./
```

8. Make sure the file has been created in `path/to/v8/out.gn/<one_of_list>/obj/libs/`
