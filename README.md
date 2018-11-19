# V8ForAndroid
V8 build setting for android (arm, arm64, x86) on Linux (Ubuntu).


### V8 set dependencies (on Linux:ubuntu)

* get depot tools [more](https://www.chromium.org/developers/how-tos/install-depot-tools) :
```
git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git

export PATH=`pwd`/depot_tools:"$PATH"
```  
  
* Make sure you have these packages installed (Linux only)
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

