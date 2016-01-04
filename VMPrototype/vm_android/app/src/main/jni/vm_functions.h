//
// Created by Jeffrey Glenn on 8/24/15.
//

#ifndef ANDROIDVM_JNI_H
#define ANDROIDVM_JNI_H

#include <jni.h>

jint JNI_OnLoad(JavaVM *vm, void *reserved);
extern JNIEnv* getEnv();

#endif //ANDROIDVM_JNI_H
