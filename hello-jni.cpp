/*
 * Copyright (C) 2016 The Android Open Source Project
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
 *
 */
#include <string.h>
#include <jni.h>

#include <string>
#include <sstream>
#include <iomanip>

#include <md5/md5.h>

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   hello-jni/app/src/main/java/com/example/hellojni/HelloJni.java
 */
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_hellojni_HelloJni_stringFromJNI(JNIEnv* env, jobject thiz)
{
#if defined(__arm__)
    #if defined(__ARM_ARCH_7A__)
    #if defined(__ARM_NEON__)
      #if defined(__ARM_PCS_VFP)
        #define ABI "armeabi-v7a/NEON (hard-float)"
      #else
        #define ABI "armeabi-v7a/NEON"
      #endif
    #else
      #if defined(__ARM_PCS_VFP)
        #define ABI "armeabi-v7a (hard-float)"
      #else
        #define ABI "armeabi-v7a"
      #endif
    #endif
  #else
   #define ABI "armeabi"
  #endif
#elif defined(__i386__)
#define ABI "x86"
#elif defined(__x86_64__)
#define ABI "x86_64"
#elif defined(__mips64)  /* mips64el-* toolchain defines __mips__ too */
#define ABI "mips64"
#elif defined(__mips__)
#define ABI "mips"
#elif defined(__aarch64__)
#define ABI "arm64-v8a"
#else
#define ABI "unknown"
#endif

  return (*env).NewStringUTF("ABI: " ABI);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_hellojni_HelloJni_calculateMD5(JNIEnv* env, jobject thiz, jstring input) {
  static_assert(sizeof(char) == sizeof(md5_byte_t), "");

  const char* input_str = (*env).GetStringUTFChars(input, JNI_FALSE);

  enum { DIGEST_SIZE = 16 };
  md5_byte_t digest[DIGEST_SIZE];

  md5_state_t s;
  md5_init(&s);
  md5_append(&s, (const md5_byte_t*)input_str, std::strlen(input_str));
  md5_finish(&s, digest);

  (*env).ReleaseStringUTFChars(input, input_str);

  std::ostringstream stream;
  stream << std::hex;
  for (int i=0; i<DIGEST_SIZE; ++i) {
    stream << std::setw(2) << std::setfill('0') << static_cast<unsigned>(digest[i]);
  }

  return (*env).NewStringUTF(stream.str().c_str());
}
