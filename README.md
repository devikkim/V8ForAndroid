# V8ForAndroid
V8 build setting for android (arm, arm64, x86) on Linux (Ubuntu).

[Complie V8 for Android](https://github.com/leibniz55/ComplieV8ForAndroid/blob/master/README.md)

[V8](https://github.com/v8/v8

)
### Create android NDK project
It is assumed that you have compiled armeabi-v7a, arm64-v8a, x86.

1. import `include`, `armeabi-v7a`, `arm64-v8a`, `x86`, `include` folder
```
app
-- libs
   -- arm64-v8a
   -- armeabi-v7a
   -- x86
   -- include
```

2. edit CMakeLists.txt file
```
cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

# import libv8_base.a called v8_base
add_library( v8_base STATIC IMPORTED )
set_target_properties( v8_base PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libv8_base.a )

# import libv8_nosnapshot.a called v8_nosnapshot
add_library( v8_nosnapshot STATIC IMPORTED )
set_target_properties( v8_nosnapshot PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libv8_nosnapshot.a )

add_library( native-lib SHARED src/main/cpp/native-lib.cpp )
target_include_directories( native-lib PRIVATE ${CMAKE_SOURCE_DIR}/libs/include )

target_link_libraries( native-lib v8_base v8_nosnapshot log )

```

3. add cmake option in build.gragle
```
cmake {
    cppFlags "-std=c++11 -frtti -fexceptions"
    abiFilters 'x86', 'armeabi-v7a', 'arm64-v8a'
    arguments "-DANDROID_UNIFIED_HEADERS=ON"
}
```

4. add function in native-lib.cpp
```
// return value is version of v8
Java_com_leibniz55_v8test_MainActivity_getVersion(
        JNIEnv *env,
        jobject /* this */) {
    const char* utfString = v8::V8::GetVersion();
    return env->NewStringUTF(utfString);
}
```

5. add native java function in MainActivity
```
public native String getVersion();

```
6. call `getVersion()`
```
TextView tv = (TextView) findViewById(R.id.sample_text);
tv.setText(getVersion());
```

7. run application 
```
version of v8 will appear on the screen.
```

