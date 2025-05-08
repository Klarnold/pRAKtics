package com.example.prac8;

import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import java.util.*;

import androidx.activity.EdgeToEdge;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
import androidx.lifecycle.Observer;
import androidx.work.Data;
import androidx.work.OneTimeWorkRequest;
import androidx.work.WorkInfo;
import androidx.work.WorkManager;

import com.squareup.picasso.Picasso;

import org.json.JSONArray;
import org.json.JSONObject;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    public static List<TextView> listTextView = new ArrayList<>() {};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });
        listTextView.add(findViewById(R.id.firstTextView));
        listTextView.add(findViewById(R.id.secondTextView));
        listTextView.add(findViewById(R.id.thirdTextView));

        Button progressiveButton = findViewById(R.id.progressiveThread);
        Button parallelButton = findViewById(R.id.parallelThread);
        Button loadButton = findViewById(R.id.loadButton);

        ImageView loadedImageView = findViewById(R.id.imageView);

        loadButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String url = "";
                try {
                    JSONObject jsonObject = new JSONObject("{\"fileSizeBytes\":2062703,\"url\":\"https://random.dog/1892f3f4-897e-442e-a442-9e53be29e827.gif\"}");
                    url = jsonObject.getString("url");
                } catch (Exception e) {
                    e.printStackTrace();
                }
                if (!url.isEmpty())
                    Picasso.get()
                            .load(url)
                            .into(loadedImageView);
            }
        });

        parallelButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Data data1 = new Data.Builder()
                        .putInt("key1", 0)
                        .putString("key2", "this is this").build();
                Data data2 = new Data.Builder()
                        .putInt("key1", 1)
                        .putString("key2", "and that is that").build();
                OneTimeWorkRequest workRequest1, workRequest2;
                workRequest1 = new OneTimeWorkRequest.Builder(MyWorker.class)
                        .setInputData(data1)
                        .build();
                workRequest2 = new OneTimeWorkRequest.Builder(MyWorker.class)
                        .setInputData(data2)
                        .build();
                List<OneTimeWorkRequest> workRequestsList = new ArrayList<>();
                workRequestsList.add(workRequest1);
                workRequestsList.add(workRequest2);
                WorkManager.getInstance(getApplicationContext()).enqueue(workRequestsList);
            }
        });

        progressiveButton.setOnClickListener(v -> doProgressive(3));
    }

    public void doProgressive(int tasksCount) {
            Handler handler = new Handler(Looper.getMainLooper());

            handler.postDelayed(() -> {
                listTextView.get(tasksCount-3).setText("Did some task №" + (tasksCount-2));

                handler.postDelayed(() -> {
                    listTextView.get(tasksCount-2).setText("Did some task №" + (tasksCount-1));

                    handler.postDelayed(() -> {
                        listTextView.get(tasksCount - 1).setText("Did some task №" + (tasksCount));
                    }, 2000);
                }, 2000);
            }, 2000);
    }

    public void task(int value){
        listTextView.get(value).setText("Did some task №" + (value+1));
    }
}