//
// Created by Jeffrey Glenn on 8/24/15.
//

#include "com_jiff_androidvm_jni_JNI.h"
#include "vm_functions.h"
#include <stdlib.h>
#include <android/log.h>
#include "../../../../../common/interpreter.h"
#include "../../../../../common/view_node.h"
#include "../../../../../common/platform/native.h"
#include "../../../../../common/commands.h"
#include "../../../../../common/util.h"

JNIEnv *myEnv;

JNIEXPORT jstring JNICALL Java_com_jiff_androidvm_jni_JNI_getString(JNIEnv *env, jclass obj) {
    return (*myEnv)->NewStringUTF(myEnv, "Hey here is my string?  Aren't I great!");
}

char* stiPrintFunc(void* data) {
    return (char*) data;
}

JNIEXPORT void JNICALL Java_com_jiff_androidvm_jni_JNI_startActivity(JNIEnv *env, jclass obj) {
//    jclass jniClass = (*env)->FindClass(env, "com/jiff/androidvm/jni/JNI");
//    if (!jniClass)
//        __android_log_print(ANDROID_LOG_ERROR, "Jiff", "Failed to failed to get JNI Class");
//    jclass startClass = (*env)->FindClass(env, "com/jiff/androidvm/SecondActivity");
//    if (!startClass)
//        __android_log_print(ANDROID_LOG_ERROR, "Jiff", "Failed to get second activity");
//    jmethodID launchActivity = (*env)->GetStaticMethodID(env, jniClass, "launchActivity", "(Ljava/lang/Class;)V");
//    if (!launchActivity)
//        __android_log_print(ANDROID_LOG_ERROR, "Jiff", "Failed to get method");
//    (*env)->CallStaticVoidMethod(env, jniClass, launchActivity, startClass);
    myEnv = env;

    STI* sti;
    char* one = "Hey hey hey | 3";
    sti = stiPut(sti, 3, one);
    char* eight = "Whoops | 111";
    sti = stiPut(sti, 8, eight);
    char* two = "What what | 11";
    sti = stiPut(sti, 11, two);
    char* three = "Another sense | 9";
    sti = stiPut(sti, 9, three);
    char* four = "My String | 1";
    sti = stiPut(sti, 1, four);
    char* five = "Woooo! | 15";
    sti = stiPut(sti, 15, five);
    char* six = "This is | 7";
    sti = stiPut(sti, 7, six);
    char* seven = "Whoops | 8";
    sti = stiPut(sti, 8, seven);

    STI* item = stiFind(sti, 11);
    __android_log_print(ANDROID_LOG_DEBUG, "Jiff", "item[%d] = %s", item->key, (char*) item->data);
    item = stiFind(sti, 7);
    __android_log_print(ANDROID_LOG_DEBUG, "Jiff", "item[%d] = %s", item->key, (char*) item->data);
    item = stiFind(sti, 3);
    __android_log_print(ANDROID_LOG_DEBUG, "Jiff", "item[%d] = %s", item->key, (char*) item->data);

    stiPrint(sti, stiPrintFunc);

    ViewNode *vn = (ViewNode*) malloc(sizeof(ViewNode));
    vn->id = getNewID();
    vn->children = NULL;
    vn->margins.left = 0;
    vn->margins.top = 0;
    vn->margins.right = 0;
    vn->margins.bottom = 0;
    vn->width = -1;
    vn->height = -1;
    vn->bgColor = 0xFF00FF00;
    vn->type = RELATIVE;
    vn->relationships = NULL;

    ViewNode *vn2 = (ViewNode*) malloc(sizeof(ViewNode));
    vn2->id = getNewID();
    vn2->children = NULL;
    vn2->margins.left = 10;
    vn2->margins.top = 10;
    vn2->margins.right = 10;
    vn2->margins.bottom = 10;
    vn2->width = -1;
    vn2->height = 300;
    vn2->bgColor = 0xFFFFFF00;
    vn2->type = RELATIVE;
    vn2->relationships = NULL;

    ViewNode *vn3 = (ViewNode*) malloc(sizeof(ViewNode));
    vn3->id = getNewID();
    vn3->children = NULL;
    vn3->margins.left = 30;
    vn3->margins.top = 100;
    vn3->margins.right = 90;
    vn3->margins.bottom = 10;
    vn3->width = 200;
    vn3->height = 150;
    vn3->bgColor = 0xFFFFFFFF;
    vn3->type = VIEW;
    vn3->relationships = NULL;

    ViewNode *vn4 = (ViewNode*) malloc(sizeof(ViewNode));
    vn4->id = getNewID();
    vn4->children = NULL;
    vn4->margins.left = 100;
    vn4->margins.top = 0;
    vn4->margins.right = 0;
    vn4->margins.bottom = 0;
    vn4->width = 99;
    vn4->height = 15;
    vn4->bgColor = 0xFF00FFFF;
    vn4->type = VIEW;
    vn4->relationships = NULL;

    llAddItem(&vn->children, vn2);
    llAddItem(&vn->children, vn3);

    Relationship *relation = (Relationship*) malloc(sizeof(Relationship));
    relation->otherID = vn2->id;
    relation->relationship = getConstant(C_BELOW);
    llAddItem(&vn3->relationships, relation);

    llAddItem(&vn2->children, vn4);

    sendViewToNative(vn);

    freeViewNode(vn);
    __android_log_print(ANDROID_LOG_DEBUG, "Jiff", "END VM_FUNCTIONS!!!!");
}

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    int status = (*vm)->GetEnv(vm, (void**)&myEnv, JNI_VERSION_1_6);
    return JNI_VERSION_1_6;
}

JNIEnv* getEnv() {
    return myEnv;
}

JNIEXPORT void JNICALL Java_com_jiff_androidvm_jni_JNI_runExecutable(JNIEnv *env, jclass obj, jbyteArray executable, jint size) {
    myEnv = env;

    void* data = (*env)->GetPrimitiveArrayCritical(env, executable, NULL);
    char* copy = (char*) malloc(sizeof(char) * size);
    memcpy(copy, data, size);
    (*env)->ReleasePrimitiveArrayCritical(env, executable, data, 0);

    runProgramCode(copy, size);
    free(copy);
}
