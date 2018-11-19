#include <jni.h>
#include <string>

#include <v8.h>
extern "C" JNIEXPORT jstring

JNICALL
Java_com_leibniz55_v8test_MainActivity_getVersion(
        JNIEnv *env,
        jobject /* this */) {
    const char* utfString = v8::V8::GetVersion();
    return env->NewStringUTF(utfString);
}