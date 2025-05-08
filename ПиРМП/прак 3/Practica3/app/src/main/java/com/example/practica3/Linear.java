package com.example.practica3;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class Linear extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_linear);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        String myObjectInput = (String) getIntent().getSerializableExtra("myObjectName");
        TextView text = findViewById(R.id.textView);
        assert myObjectInput != null;
        text.setText("Добрый день, " + myObjectInput + "!");

        Button nextButton = findViewById(R.id.next);
        Button prevButton = findViewById(R.id.previous);
        nextButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                onNextActivity(v);
            }
        });
        prevButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                onPreviousActivity(v);
            }
        });
    }
    public void onNextActivity(View view){
        EditText edit = findViewById(R.id.edit);
        int age;
        if (!edit.getText().toString().isEmpty()) {
            String n = edit.getText().toString();
            age = Integer.parseInt(edit.getText().toString());

        }
        else
            age = -1;
        MyObject myObject = new MyObject("", age);
        Intent intent = new Intent(this, Relative.class);
        intent.putExtra("myObjectName", myObject.getAge());
        startActivity(intent);
    }
    public void onPreviousActivity(View view){
        Intent intent = new Intent(this, MainActivity.class);
        startActivity(intent);
    }
}
