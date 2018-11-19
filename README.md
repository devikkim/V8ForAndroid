# V8ForAndroid
V8 build setting for android (arm, arm64, x86) on Linux (Ubuntu).


### set dependencies (on Linux:ubuntu)

* get depot tools [more](https://www.chromium.org/developers/how-tos/install-depot-tools) :
```
git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git

export PATH=`pwd`/depot_tools:"$PATH"
```  
  
* make sure you have these packages installed (Linux only)
```
sudo apt-get install curl libc6-dev-i386 g++-multilib
```
* install v8 (checkout version)
```
fetch v8
cd v8
git pull
git checkout <v8_version>
```

* download android tools
```
echo "target_os = ['android']" >> ../.gclient && gclient sync
```

* check v8gen.py list
```
tools/dev/v8gen.py list
```
> may be list up `arm.debug, arm.optdebug arm.release, arm64.debug...`

* generate compilation target
```
tools/dev/v8gen.py gen <one_of_list>
```

* change `out.gn/<one_of_list>/args.gn`
```
vi out.gn/<one_of_list>/args.gn
```
