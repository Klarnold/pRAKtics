package com.example.prac10;

import android.os.Bundle;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
import android.content.SharedPreferences;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    EditText editText;
    TextView textView;
    Button saveButton;
    Button getButton;
    Button deleteButton;

    SharedPreferences sharedPreferences;
    SharedPreferences.Editor editor;

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

        editText = findViewById(R.id.edit_text);
        textView = findViewById(R.id.text_view);

        saveButton = findViewById(R.id.save_name);
        getButton = findViewById(R.id.get_name);
        deleteButton = findViewById(R.id.delete_name);

        sharedPreferences = getSharedPreferences("myPreferences", MODE_PRIVATE);
        editor = sharedPreferences.edit();

        saveButton.setOnClickListener(v -> save_name());
        getButton.setOnClickListener(v -> get_name());
        deleteButton.setOnClickListener(v -> delete_name());
    }

    public void save_name(){
        editor.putString("username", editText.getText().toString());
        editor.apply();
    }

    public void get_name(){
        textView.setText(getString(R.string.name_view) + sharedPreferences.getString("username", "None"));
    }

    public void delete_name(){
        editor.remove("username");
        editor.apply();
    }
}
