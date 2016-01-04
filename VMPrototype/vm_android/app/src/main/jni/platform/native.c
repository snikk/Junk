//
// Created by Jeffrey Glenn on 8/25/15.
//

#include "../../../../../../common/view_node.h"
#include "../../../../../../common/data_structures.h"
#include "../../../../../../common/platform/native.h"
#include "../vm_functions.h"
#include <android/log.h>
#include <stddef.h>

jobject createViewNode(JNIEnv* env, ViewNode* vn) {
    jclass jViewNode = (*env)->FindClass(env, "com/jiff/androidvm/views/ViewNode");
    jclass jRelationship = (*env)->FindClass(env, "com/jiff/androidvm/views/ViewNode$Relationship");
    jclass jRect = (*env)->FindClass(env, "android/graphics/Rect");

    jmethodID vnConstructor = (*env)->GetMethodID(env, jViewNode, "<init>", "(I[Lcom/jiff/androidvm/views/ViewNode;Landroid/graphics/Rect;IIII[Lcom/jiff/androidvm/views/ViewNode$Relationship;)V");
    jmethodID relConstructor = (*env)->GetMethodID(env, jRelationship, "<init>", "(II)V");
    jmethodID rectConstructor = (*env)->GetMethodID(env, jRect, "<init>", "(IIII)V");

    jobjectArray viewNodes = NULL;
    if (vn->children) {
        viewNodes = (*env)->NewObjectArray(env, llCount(&vn->children), jViewNode, NULL);
        int curr = 0;
        LL* arr = vn->children;
        while (arr) {
            jobject nextNode = createViewNode(env, arr->data);
            (*env)->SetObjectArrayElement(env, viewNodes, curr++, nextNode);
            arr = arr->n;
        }
    }

    jobjectArray relationships = NULL;
    if (vn->relationships) {
        __android_log_print(ANDROID_LOG_DEBUG, "Jiff", "RELATIONSHIPS!!!");
        relationships = (*env)->NewObjectArray(env, llCount(&vn->relationships), jRelationship, NULL);
        int curr = 0;
        LL* arr = vn->relationships;
        while (arr) {
            Relationship* relation = (Relationship*) arr->data;
            jobject relObject = (*env)->NewObject(env, jRelationship, relConstructor, relation->otherID, relation->relationship);
            (*env)->SetObjectArrayElement(env, relationships, curr++, relObject);
            arr = arr->n;
        }
    }

    jobject rect = (*env)->NewObject(env, jRect, rectConstructor, vn->margins.left, vn->margins.top, vn->margins.right, vn->margins.bottom);
    jobject newNode = (*env)->NewObject(env, jViewNode, vnConstructor, vn->id, viewNodes, rect, vn->width, vn->height, vn->bgColor, vn->type, relationships);

    return newNode;
}

void sendViewToNative(ViewNode* vn) {
    JNIEnv* env = getEnv();

    jobject newNode = createViewNode(env, vn);

    jclass jniClass = (*env)->FindClass(env, "com/jiff/androidvm/jni/JNI");
    jclass startClass = (*env)->FindClass(env, "com/jiff/androidvm/SecondActivity");
    jmethodID launchActivity = (*env)->GetStaticMethodID(env, jniClass, "launchActivity", "(Ljava/lang/Class;Lcom/jiff/androidvm/views/ViewNode;)V");
    (*env)->CallStaticVoidMethod(env, jniClass, launchActivity, startClass, newNode);
}


