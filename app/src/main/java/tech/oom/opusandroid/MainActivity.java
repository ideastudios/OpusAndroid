package tech.oom.opusandroid;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

import tech.oom.opuslibrary.opus.OpusDecoder;
import tech.oom.opuslibrary.opus.OpusEncoder;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        OpusDecoder opusDecoder = new OpusDecoder();
        opusDecoder.init(16000, 1);
        OpusEncoder opusEncoder = new OpusEncoder();
        opusEncoder.initAudio(16000, 1);
    }

}
