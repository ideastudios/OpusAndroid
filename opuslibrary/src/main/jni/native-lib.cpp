//
// Created by Administrator on 2017/8/25.
//

#include <malloc.h>
#include <jni.h>
#include <android/log.h>
#include "Decoder.h"
#include "Encoder.h"

extern "C"
JNIEXPORT jlong JNICALL
Java_tech_oom_opuslibrary_opus_OpusDecoder_init_1native(JNIEnv *env, jobject instance, jint fs,
                                                           jint channels) {
    Decoder *mDecoder = new Decoder();
    mDecoder->init(fs, channels);
    return (jlong) mDecoder;

}

extern "C"
JNIEXPORT jshortArray JNICALL
Java_tech_oom_opuslibrary_opus_OpusDecoder_decode_1native(JNIEnv *env, jobject instance,
                                                             jlong decoder, jbyteArray in,
                                                             jint frame_size) {
    jbyte *in_data = env->GetByteArrayElements(in, JNI_FALSE);
    int data_size = env->GetArrayLength(in);

    opus_int16 *out_data = (short *) malloc(frame_size * 2 * sizeof(short));
    int out_len = ((Decoder *) decoder)->decode((unsigned char *) in_data, data_size, out_data,
                                                frame_size);
    jshortArray out = env->NewShortArray(out_len);

    env->ReleaseByteArrayElements(in, in_data, JNI_ABORT);
    env->SetShortArrayRegion(out, 0, out_len, out_data);
    free(out_data);
    return out;
}

extern "C"
JNIEXPORT void JNICALL
Java_tech_oom_opuslibrary_opus_OpusDecoder_destroy_1native(JNIEnv *env, jobject instance,
                                                              jlong decoder) {
    ((Decoder *) decoder)->destory();
    delete ((Decoder *) decoder);


}

extern "C"
JNIEXPORT jlong JNICALL
Java_tech_oom_opuslibrary_opus_OpusEncoder_init_1voip_1native(JNIEnv *env, jobject instance,
                                                                 jint fs, jint channels) {
    Encoder *mEncoder = new Encoder();
    mEncoder->initVoip(fs, channels);
    return (jlong) mEncoder;


}

extern "C"
JNIEXPORT jlong JNICALL
Java_tech_oom_opuslibrary_opus_OpusEncoder_init_1audio_1native(JNIEnv *env, jobject instance,
                                                                  jint fs, jint channels) {
    Encoder *mEncoder = new Encoder();
    mEncoder->initAudio(fs, channels);
    return (jlong) mEncoder;

}

extern "C"
JNIEXPORT jlong JNICALL
Java_tech_oom_opuslibrary_opus_OpusEncoder_init_1restricted_1low_1delay_1native(JNIEnv *env,
                                                                                   jobject instance,
                                                                                   jint fs,
                                                                                   jint channels) {

    Encoder *mEncoder = new Encoder();
    mEncoder->initRestrictedLowDelay(fs, channels);
    return (jlong) mEncoder;

}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_tech_oom_opuslibrary_opus_OpusEncoder_encode_1native(JNIEnv *env, jobject instance,
                                                             jlong encoder, jshortArray pcm,
                                                             jint frameSize) {
    short *pcm_data = env->GetShortArrayElements(pcm, JNI_FALSE);
    int data_len = env->GetArrayLength(pcm);
    __android_log_print(ANDROID_LOG_ERROR, "HuyaEncoder", "pcm_len:%d", data_len);
    unsigned char *data = new unsigned char[data_len * 2];
    int out_len = ((Encoder *) encoder)->encode(pcm_data, frameSize, data);
    jbyteArray out = env->NewByteArray(out_len);

    env->ReleaseShortArrayElements(pcm, pcm_data, JNI_ABORT);
    env->SetByteArrayRegion(out, 0, out_len, (jbyte *) data);
    return out;

}

extern "C"
JNIEXPORT void JNICALL
Java_tech_oom_opuslibrary_opus_OpusEncoder_destroy_1native(JNIEnv *env, jobject instance,
                                                              jlong encoder) {

    ((Encoder *) encoder)->destory();
    delete ((Encoder *) encoder);


}
