package com.example.prac12;

import android.content.ContentResolver;
import android.content.ContentUris;
import android.content.ContentValues;
import android.content.pm.PackageManager;
import android.content.pm.ProviderInfo;
import android.database.Cursor;
import android.os.Bundle;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import com.google.gson.stream.JsonReader;

import android.net.Uri;
import org.json.JSONArray;

import org.json.JSONArray;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.lang.reflect.Type;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    public static final Uri CONTENT_URI = Uri.parse("content://com.prac12.app.provider/books");
    public TextView textView;

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

        textView = findViewById(R.id.textView);

        try {
            JSONObject root = new JSONObject();
            JSONArray users = new JSONArray();

            root.put("name", "Wow");
            root.put("age", "It kinda");
            root.put("email", "Works");
            // Создаем файл
            File file = new File(getFilesDir(), "data.json");
            FileWriter writer = new FileWriter(file);
            writer.write(root.toString());
            writer.close();

        } catch (Exception e) {
            e.printStackTrace();
        }

        String contents = "";
        try (FileInputStream fis = this.openFileInput("data.json")) {
            InputStreamReader inputStreamReader = new
                    InputStreamReader(fis, StandardCharsets.UTF_8);
            StringBuilder stringBuilder = new StringBuilder();
            try (BufferedReader reader = new
                    BufferedReader(inputStreamReader)) {
                String line = reader.readLine();
                while (line != null) {
                    stringBuilder.append(line).append('\n');
                    line = reader.readLine();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
            contents = stringBuilder.toString();
        } catch (IOException e) {
            e.printStackTrace();
        }

        Gson gson = new Gson();

        User user = new User();

        try {
            user = gson.fromJson(contents, User.class);
        } catch (Exception e){
            e.printStackTrace();
        }
        textView.setText(textView.getText() + "Name: " + user.name +
                "\nAge: " + user.age + "\nEmail: " + user.email);

    }
}
