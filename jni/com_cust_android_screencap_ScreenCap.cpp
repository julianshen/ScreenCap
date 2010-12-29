/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include <utils/Log.h>

#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>

#include <binder/IMemory.h>
#include <surfaceflinger/ISurfaceComposer.h>

#include <SkImageEncoder.h>
#include <SkBitmap.h>

#include "com_cust_android_screencap_ScreenCap.h"

using namespace android;
/*
 * Class:     com_cust_android_screencap_ScreenCap
 * Method:    captureScreenToFile
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_cust_android_screencap_ScreenCap_captureScreenToFile
  (JNIEnv *env, jclass clazz, jstring fileName) {

    const String16 name("SurfaceFlinger");
    sp<ISurfaceComposer> composer;
    getService(name, &composer);

    sp<IMemoryHeap> heap;
    uint32_t w, h;
    PixelFormat f;
    status_t err = composer->captureScreen(0, &heap, &w, &h, &f, 0, 0);
    if (err != NO_ERROR) {
        fprintf(stderr, "screen capture failed: %s\n", strerror(-err));
        return;
    }

    LOGD("screen capture success: w=%u, h=%u, pixels=%p\n",
            w, h, heap->getBase());

    SkBitmap b;
    b.setConfig(SkBitmap::kARGB_8888_Config, w, h);
    b.setPixels(heap->getBase());
    SkImageEncoder::EncodeFile(env->GetStringUTFChars(fileName, 0), b,
            SkImageEncoder::kPNG_Type, SkImageEncoder::kDefaultQuality);

}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm, void* reserved) {

}
