package com.example.prac12_1;

import android.content.ContentResolver;
import android.content.ContentUris;
import android.content.pm.PackageManager;
import android.content.pm.ProviderInfo;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class MainActivity extends AppCompatActivity {

    public static final Uri CONTENT_URI = Uri.parse("content://com.example.prac12.provider/books");
    TextView textView;
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


        StringBuilder result = new StringBuilder();
        try {
            ContentResolver resolver = getContentResolver();
            Cursor cursor = resolver.query(CONTENT_URI, new String[] {"_id",
                    "title", "author"}, null, null, "title ASC");

            if (cursor != null && cursor.moveToFirst()) {
                try {
                    int idColumn = cursor.getColumnIndex("_id");
                    int titleColumn = cursor.getColumnIndex("title");
                    int authorColumn = cursor.getColumnIndex("author");
                    do {
                        String id = cursor.getString(idColumn);
                        String title = cursor.getString(titleColumn);
                        String author = cursor.getString(authorColumn);

                        result.append("ID: ").append(id)
                                .append(", Title: ").append(title)
                                .append(", Author: ").append(author)
                                .append("\n");
                    } while (cursor.moveToNext());
                } finally {
                    cursor.close();
                }

            } else {
                result.append("Нет данных или ошибка доступа");
            }
        } catch (Exception e) {
            result.append("Ошибка: ").append(e.getMessage());
        }

        textView.setText(result.toString());
    }

    private boolean isProviderAvailable() {
        PackageManager pm = getPackageManager();
        return pm.resolveContentProvider("com.example.prac12.provider", 0) != null;
    }


}
