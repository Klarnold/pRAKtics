package com.example.prac8;

import android.content.Context;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.work.Data;
import androidx.work.Worker;
import androidx.work.WorkerParameters;


public class MyWorker extends Worker {
    public final String TAG = "MY_TAG";
    int textViewIndex;
    String text;
    public MyWorker(@NonNull Context context, @NonNull WorkerParameters
            workerParams) {
        super(context, workerParams);
        textViewIndex = workerParams.getInputData().getInt("key1",-1);
        text = getInputData().getString("key2");
    }
    @NonNull
    @Override
    public Result doWork() {
        if (textViewIndex != -1)
        {
            Handler handler = new android.os.Handler(Looper.getMainLooper());

            handler.postDelayed(() -> {
                MainActivity.listTextView.get(textViewIndex).setText(text);
            }, textViewIndex * 5000);
        }

        return Worker.Result.success();
    }
}
