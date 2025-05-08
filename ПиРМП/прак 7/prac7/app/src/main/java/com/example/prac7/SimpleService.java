package com.example.prac7;

import android.app.Service;
import android.content.Intent;
import android.os.Handler;
import android.os.IBinder;
import android.widget.Toast;

import kotlin.OverloadResolutionByLambdaReturnType;

public class SimpleService extends Service {
    public SimpleService() {
    }

    public int onStartCommand(Intent intent, int flags, int startId) {
        Handler handler = new Handler();
        handler.post(() -> {
            Toast.makeText(this, "Сервис начал работу", Toast.LENGTH_LONG).show();
            handler.postDelayed(() -> Toast.makeText(this, "Сервис продолжает работу", Toast.LENGTH_LONG).show(), 2000);
        });

        return START_STICKY;
    }

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        throw new UnsupportedOperationException("Not yet implemented");
    }
}
