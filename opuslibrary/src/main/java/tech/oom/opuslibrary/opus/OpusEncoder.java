package tech.oom.opuslibrary.opus;

/**
 * Created by lihang1@yy.com on 2017/8/28.
 */

public class OpusEncoder {
    static {
        System.loadLibrary("native-lib");
    }

    private long encoder;

    private native long init_voip_native(int fs, int channels);

    private native long init_audio_native(int fs, int channels);

    private native long init_restricted_low_delay_native(int fs, int channels);

    private native byte[] encode_native(long encoder, short[] pcm, int frameSize);

    private native void destroy_native(long encoder);

    public void initVoip(int fs, int channels) {
        encoder = init_voip_native(fs, channels);
    }

    public void initAudio(int fs, int channels) {
        encoder = init_audio_native(fs, channels);
        System.out.println("encoder = " + encoder);
    }

    public void initRestrictedLowDelay(int fs, int channels) {
        encoder = init_restricted_low_delay_native(fs, channels);

    }

    public byte[] encode(short[] pcm, int frameSize) {
        return encode_native(encoder, pcm, frameSize);
    }

    public void destory() {
        destroy_native(encoder);
    }
}
