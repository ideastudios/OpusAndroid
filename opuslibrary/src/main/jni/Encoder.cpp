//
// Created by Administrator on 2017/8/28.
//

#include <malloc.h>
#include <android/log.h>
#include "Encoder.h"

void Encoder::init(opus_int32 Fs, int channels, int application) {
    int error;
    m_channels = channels;
    opusEncoder = opus_encoder_create(Fs, channels, application, &error);
    if (error != OPUS_OK) {
        __android_log_print(ANDROID_LOG_ERROR, "Encoder", "init_error:%d", error);
    }
}

void Encoder::initAudio(opus_int32 Fs, int channels) {
    init(Fs, channels, OPUS_APPLICATION_AUDIO);
}

void Encoder::initVoip(opus_int32 Fs, int channels) {
    init(Fs, channels, OPUS_APPLICATION_VOIP);
}

void Encoder::initRestrictedLowDelay(opus_int32 Fs, int channels) {
    init(Fs, channels, OPUS_APPLICATION_RESTRICTED_LOWDELAY);
}

int Encoder::encode(const opus_int16 *pcm, int frame_size, unsigned char *data) {
    __android_log_print(ANDROID_LOG_ERROR, "HuyaDecoder", "encode_frame_size:%d", frame_size);
    int size = opus_encode(opusEncoder, pcm, frame_size, data, frame_size * m_channels * sizeof(opus_int16));
    __android_log_print(ANDROID_LOG_ERROR, "Encoder", "encode_size:%d", size);
    if (size < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "Encoder", "encode_error:%s", opus_strerror(size));
    }
    return size;
}

void Encoder::destory() {
    opus_encoder_destroy(opusEncoder);
}


