package tech.oom.opuslibrary.opus;

/**
 * Created by lihang1@yy.com on 2017/8/22.
 */

public class OpusDecoder {
    static {
        System.loadLibrary("native-lib");
    }

    private long decoder;

    private native long init_native(int fs, int channels);

    private native short[] decode_native(long decoder, byte[] in, int frame_size);

    private native void destroy_native(long decoder);

    public void init(int fs, int channels) {
        decoder = init_native(fs, channels);
        System.out.println("decoder = " + decoder);
    }

    public short[] decode(byte[] in, int frameSize) {
        return decode_native(decoder, in, frameSize);
    }

    public void destroy() {
        destroy_native(decoder);
    }
}
